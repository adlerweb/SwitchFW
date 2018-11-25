<?PHP

    $port='/dev/ttyUSB1';
    //$port='test.sock';
    
    define('ISB_MSG_FLAGS_TOF_UNICAST', 0x00);
    define('ISB_MSG_FLAGS_TOF_MULTICAST', 0x20);

    define('ISB_MSG_FLAGS_DLC_0',0);
    define('ISB_MSG_FLAGS_DLC_1',1);
    define('ISB_MSG_FLAGS_DLC_2',2);
    define('ISB_MSG_FLAGS_DLC_3',3);
    define('ISB_MSG_FLAGS_DLC_4',4);
    define('ISB_MSG_FLAGS_DLC_5',5);
    define('ISB_MSG_FLAGS_DLC_6',6);
    define('ISB_MSG_FLAGS_DLC_7',7);
    define('ISB_MSG_FLAGS_DLC_8',8);


    $fd = dio_open($port, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    dio_tcsetattr($fd, array(
        'baud' => 19200,
        'bits' => 8,
        'stop'  => 1,
        'parity' => 0
    ));
    
    $start=0;
    $stop =0;
    $buffer = array();

    debug2('Init OK');
    $test=0;
    
    while(1) {
        if(!$fd) die('Connection so socket interrupted'."\n");
        
        if($start >= 30000) {
            $newbuf=array();
            for($i=$start; $i<=($stop-1); $i++) {
                $newbuf[]=$buffer[$i];
            }
            $buffer=$newbuf;
            unset($newbuf);
            $start=0;
            $stop=count($buffer);
        }
        
        $tmp = dio_read($fd, 1);
        if($tmp !== false) {
            $buffer[$stop]=$tmp;
            file_put_contents('test.raw', file_get_contents('test.raw').$tmp);
            $stop++;
        }
        
        if(($stop-$start) < 12) continue;
        
        for($i=$start; $i<=($stop-12); $i++) {
            if(isset($buffer[$i]) && $buffer[$i] == '>') {
                debug('Found possible SOT');
                $pkg['raw'] = '';
                for($j=$i; $j<$i+48; $j++) {
                    if(isset($buffer[$j])) {
                        $pkg['raw'].=$buffer[$j];
                        if(($j>($i+12)) && $buffer[$j] == chr(10) && $buffer[($j-1)] == chr(13) && $buffer[($j-2)] == "<") {
                            debug('found EOT');
                            break;
                        }
                    }
                }

                if($j==$i+48) {
                    debug('No EOT found');
                    $test++;
                    if($test >= 48) {
                        
                    }
                    break;
                }else{
                    $test=0;
                }

                if(!preg_match('/>([0-9a-f]{0,2}):([0-9a-f]{0,4}):([0-9a-f]{0,4}):((([0-9a-f]{0,2}):){0,8})([0-9a-f]{0,2})<\s/', $pkg['raw'], $match)) {
                    debug('could not decode packet');
                    break;
                }
            
                $match[4] = explode(':', $match[4]); //Separate data bytes
                unset($match[4][(count($match[4])-1)]); //Last byte is always empty


                /*
                    1 -> Flags
                    2 -> Dest
                    3 -> Source
                    4 -> Databytes (Array)
                    5ff -> bullshit
                    last -> CRC
                */

                $pkg['flags']=hexdec($match[1]);
                debug('Flags are 0x'.dechex($pkg['flags']));
                if($pkg['flags'] & ISB_MSG_FLAGS_TOF_UNICAST) {
                    $pkg['mode'] = 'unicast';
                    debug('Detected Unicast Package');
                }elseif($pkg['flags'] & ISB_MSG_FLAGS_TOF_MULTICAST) {
                    $pkg['mode'] = 'multicast';
                    debug('Detected Multicast Package');
                }else{
                    debug('Unknown Package type - skipping');
                    var_dump($buffer); die();
                    continue;
                }

                $pkg['dlc'] = hexdec($match[1]) & 0x0F;
                debug('Packet contains '.$pkg['dlc'].' data bytes');
                
                $pkg['dest'] = hexdec($match[2]);
                debug('Receiver is 0x'.dechex($pkg['dest']));
                $pkg['src']  = hexdec($match[3]);
                debug('Sender is 0x'.dechex($pkg['src']));
                
                //$pkg['data']=$match[4];
                foreach($match[4] as $d) {
                    $pkg['data'][] = hexdec($d);
                }

                if(count($pkg['data']) != $pkg['dlc']) {
                    debug('Receive counter does not match DLC');
                    var_dump($pkg); die();
                    continue;
                }
                
                $pkg['crc'] = hexdec($match[7]); //ggf letztes ausrechnen
                $pkg['crccalc'] = genrcr8($pkg);
                if($pkg['crc'] != $pkg['crccalc']) {
                    debug2('Got packet with incorrect checksum - skipping');
                    break;
                }
                debug2('CRC is 0x'.dechex($pkg['crc']).' - calculated CRC is 0x'.dechex($pkg['crccalc']));
                

                switch($pkg['data'][0]) {
                    case 0x21:
                        $pkg['type'] = 'Node has booted';
                        debug2('>> The Node 0x'.dechex($pkg['src']).' has booted');
                        break;
                    case 0x50:
                        $pkg['type'] = 'Setting new NodeID';
                        debug2('>> Setting new NodeID 0x'.dechex($pkg['data'][1]).dechex($pkg['data'][2]).' using checksum 0x'.dechex($pkg['data'][2]).' for current temporary node');
                        break;
                    case 0x51:
                        $pkg['type'] = 'Single Byte Message';
                        switch($pkg['data'][1]) {
                            case 0x00:
                                $pkg['switch'] = 'OFF';
                                break;
                            case 0x01:
                                $pkg['switch'] = 'ON';
                                break;
                            default:
                                $pkg['switch'] = 'UNKNOWN';
                        }
                        $pkg['srcport'] = (($pkg['src'] & 0xF000) >> 12);
                        $pkg['src'] = ($pkg['src'] & 0x0FFF);
                        debug2('>> Port '.$pkg['srcport'].' on NodeID 0x'.dechex($pkg['src']).' issued switch to '.$pkg['switch'].' for group 0x'.dechex($pkg['dest']));
                        break;
                    case 0x52:
                        $pkg['type'] = 'Dimmer Message';
                        $pkg['dimmer'] = $pkg['data'][1].'%';
                        debug2('>> NodeID 0x'.dechex($pkg['src']).' issued dim '.$pkg['dimmer'].' for group 0x'.dechex($pkg['dest']));
                        break;
                    case 0x70:
                        $pkg['type'] = 'PING';
                        debug2('>> PING REQUEST from 0x'.dechex($pkg['src']).' to 0x'.dechex($pkg['dest']));
                        break;
                    case 0x71:
                        $pkg['type'] = 'PONG';
                        debug2('>> PONG RESPONSE from 0x'.dechex($pkg['src']).' to 0x'.dechex($pkg['dest']));
                        break;
                    case 0x72:
                        $pkg['type'] = 'Read Config';
                        $pkg['grpid'] = $pkg['data'][1];
                        if($pkg['dlc'] == 2) {
                            debug2('>> Node 0x'.dechex($pkg['src']).' requesting Groupcfg 0x'.dechex($pkg['grpid']).' from Node 0x'.dechex($pkg['dest']));
                        }else{
                            $pkg['grpaddr_h'] = $pkg['data'][2];
                            $pkg['grpaddr_l'] = $pkg['data'][3];
                            $pkg['grpcfg'] = $pkg['data'][4];

                            $pkg['grpaddr'] = (($pkg['grpaddr_h'] << 8) | $pkg['grpaddr_l']);

                            debug2('>> Node 0x'.dechex($pkg['src']).' sending requested Group 0x'.dechex($pkg['grpid']).' to Node 0x'.dechex($pkg['dest']).' - GroupAddr: 0x'.dechex($pkg['grpaddr']).' - Cfg: 0x'.dechex($pkg['grpcfg']));
                        }
                        break;
                    case 0x73:
                        $pkg['type'] = 'Write Config';
                        $pkg['grpid'] = $pkg['data'][1];
                        $pkg['grpaddr_h'] = $pkg['data'][2];
                        $pkg['grpaddr_l'] = $pkg['data'][3];
                        $pkg['grpcfg'] = $pkg['data'][4];

                        $pkg['grpaddr'] = (($pkg['grpaddr_h'] << 8) | $pkg['grpaddr_l']);

                        debug2('>> Node 0x'.dechex($pkg['dest']).' sending new Group 0x'.dechex($pkg['grpid']).' to Node 0x'.dechex($pkg['dest']).' - GroupAddr: 0x'.dechex($pkg['grpaddr']).' - Cfg: 0x'.dechex($pkg['grpcfg']));

                        break;
                }

                if(isset($pkg['type'])) debug('Message is '.$pkg['type']);
                                
                for($k=$start; $k<=$j; $k++)
                    unset($buffer[$k]);
                $start=$j+1;

                //var_dump($pkg);
                unset($pkg,$j,$k,$d,$match);
            }
        }
    }
    
    function debug($str) {
        //echo $str."\n";
    }
    
    function debug2($str) {
        echo $str."\n";
    }

    function genrcr8($pkg) {
        $crc = 0;
        $crc += $pkg['flags'];
        $crc += $pkg['src'] >> 8;
        $crc += $pkg['src'] & 0xFF;
        $crc += $pkg['dest'] >> 8;
        $crc += $pkg['dest'] & 0xFF;
        for($i=0; $i<$pkg['dlc']; $i++) {
            $crc += $pkg['data'][$i];
        }
        $crc ^= 0xFF;
        $crc++;
        $crc &= 0xFF;
        return $crc;
    }
?>

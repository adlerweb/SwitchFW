<?PHP

    /*
    *************************
        EEPROM Generator
    *************************
    Firmware Adlerweb 0.1

    EEPROM-Map:
    0x0000 -> 0x0001    NodeID
    0x0002              InCFG
    0x0003 -> 0x0006    OutCFG
    0x0010              First GroupCFG
    */

    if($nodeid < 0x0010) die('NodeIDs below 0x0010 are reserved'."\n");
    if($nodeid > 0x07FF) die('NodeIDs above 0x07FF can not be used - we got only 11bit adress space'."\n");

    $node_low = $nodeid & 0x00FF;
    $node_high = $nodeid >> 8;

    $eeprom[0] = $node_low;
    $eeprom[1] = $node_high;
    $eeprom[2] = $incfg;

    if(count($outcfg) != 8) die('Oops - expected 7 outputs, got '.count($outcfg)."\n");

    for($i=0; $i<8; $i++) {
        $outee[$i]=0;
        if($outcfg[$i]['active']) $outee[$i] += 8;
        if($outcfg[$i]['invert']) $outee[$i] += 4;
        if($outcfg[$i]['pulse'])  $outee[$i] += 2;
        if($outcfg[$i]['boot'])   $outee[$i] += 1;
        
        if(!($i % 2)) {
            $outee[$i] <<= 4;
        }
    }

    $eeprom[3] = $outee[0] | $outee[1];
    $eeprom[4] = $outee[2] | $outee[3];
    $eeprom[5] = $outee[4] | $outee[5];
    $eeprom[6] = $outee[6] | $outee[7];

    if(count($groups) > floor((EEMEM-10)/3)) die('Oops - not enough EEPROM to save this amount of configuration data'."\n");
    if(count($groups) > 32) die('Oops - Firmware is currently limited to 32 groups'."\n");

    //Fill until we are at 0x0010
    for($i=7; $i<0x0010; $i++) $eeprom[$i] = 0xff;

    foreach($groups as $g) {
        if(!isset($g['msg'])) $g['msg']=0;
        if(!isset($g['trigger'])) $g['trigger']=0;
    
        $eeprom[] = $g['address'] & 0x00FF; //LSN
        $eeprom[] = $g['address'] >> 8;     //MSN
        $temp = $g['msg'] & 0b0000011;
        $temp |= (($g['channel'] & 0b0000111) << 2);
        $temp |= (($g['io'] & 0b0000001) << 5);
        $temp |= (($g['trigger'] & 0b0000011) << 6);
        $eeprom[] = $temp;
    }

    $fs = fopen('eeprom.'.dechex($nodeid).'.raw', 'w');
    for($i=0; $i<EEMEM; $i++) {
        if(isset($eeprom[$i])) {
            fwrite($fs, chr($eeprom[$i]));
        }else{
            fwrite($fs, chr(0xff));
        }
    }
    fclose($fs);
?>

<?PHP

    require_once('config.php');
    require_once('parser.class.php');
    
    $parser = new aw_hausbus_parser();

    $pkg['dest'] = 0x1234;  //Target
    $pkg['data'][0] = 0x51; //Switch
    $pkg['data'][1] = $argv[1]; //On-Off

    $pkg['src'] = 0x00FF;

    $pkg['dlc'] = count($pkg['data']);
    $pkg['flags'] = 0x20 | $pkg['dlc']; // (Multicast)

    $opkg[] = 0x01;                  //Startbyte
    $opkg[] = $pkg['flags'];         //Flags
    $opkg[] = $pkg['dest'] & 0x00FF; //Destination (Lower)
    $opkg[] = $pkg['dest'] >> 8;     //Destination (Higher)
    $opkg[] = $pkg['src'] & 0x00FF;  //Source (Lower)
    $opkg[] = $pkg['src'] >> 8;      //Source (Higher)
    foreach($pkg['data'] as $d) $opkg[] = $d;
    $opkg[] = 0x00; //Separator

    $pkg['crc'] = $parser->gencrc8($pkg);

    $opkg[] = $pkg['crc']; //CRC
    $opkg[] = 0x0D; //Stopbyte
    
    $parser->parse(implode($opkg));
    
    $fd = dio_open($port, O_WRONLY | O_NOCTTY | O_NONBLOCK);
    dio_tcsetattr($fd, array(
        'baud' => 19200,
        'bits' => 8,
        'stop'  => 1,
        'parity' => 0
    ));

    if(!$fd) die('Connection so socket interrupted'."\n");
    
    foreach($opkg as $p) {
        echo '>> 0x'.dechex($p)."\n";
        dio_write($fd, chr($p));
    }

    dio_close($fd);
?>

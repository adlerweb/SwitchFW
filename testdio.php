<?PHP
	$port = '/dev/ttyUSB1';

	$fd = dio_open($port, O_RDWR | O_NOCTTY | O_NONBLOCK);

dio_fcntl($fd, F_SETFL, O_SYNC);

dio_tcsetattr($fd, array(
  'baud' => 19200,
  'bits' => 8,
  'stop'  => 1,
  'parity' => 0
)); 

	while(!file_exists('stop')) {
		echo dio_read($fd);	
		usleep(500);
	}

	dio_close($fd);
?>

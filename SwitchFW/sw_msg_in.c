
void inmsgpwmparser(uint16_t addr, uint8_t level) {
	if(addr == 0xFFFF) {
		return;
	}
	
	for(uint8_t i=0; i<32; i++) {
		if(groupids[i] == addr) {
			//Gruppe ist bei uns bekannt - config lesen
			uint8_t pincfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF + 2 + ( 3 * i ) ));
			
			if(level > 0) {
				groupstate[(uint8_t)(i/8)] |= (1<<i%8);
			}else{
				groupstate[(uint8_t)(i/8)] &= ~(1<<i%8);
			}
			
			if(pincfg & ASB_GRPCFG_IO) {
				//Gruppe ist ein Ausgang
				uint8_t chan;
				chan = pincfg & 0b00011100;
				chan = chan >> 2;
				if(chan == 4) {
					pwm_oc2((uint8_t)level/100*32);
				}
				if(chan == 6) {
					pwm_oc1a((uint8_t)level/100*32);
				}
				if(chan == 7) {
					pwm_oc1b((uint8_t)level/100*32);
				}
			}
		}
	}
}

void inmsgparser(uint16_t addr, uint8_t msg) {	
	if(addr == 0xFFFF) {
		return;
	}
	uint8_t mask;
	mask=0b00000000;
	//1bit IO-Nachrichten
	for(uint8_t i=0; i<32; i++) {
		if(groupids[i] == addr) {
			//Gruppe ist bei uns bekannt - config lesen
			uint8_t pincfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF + 2 + ( 3 * i ) ));
			
			if(msg == ASB_MSG_ON) {
				groupstate[(uint8_t)(i/8)] |= (1<<i%8);
			}else if(msg == ASB_MSG_OFF) {
				groupstate[(uint8_t)(i/8)] &= ~(1<<i%8);
			}
			
			if(pincfg & ASB_GRPCFG_IO) {
				//Gruppe ist ein Ausgang
				uint8_t chan,bchan;
				chan = pincfg & 0b00011100;
				chan = chan >> 2;
				bchan = (1 << chan);
				
				uint8_t portcfg;
				portcfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_OUTCFG+(((uint8_t)chan/2))));
				 
				if((chan % 2) == 0) portcfg = portcfg >> 4;
				portcfg = portcfg & 0b00001111;
				
				if(portcfg & 0b00001000) {
					//Portdefinition ist aktiv
					
					if(portcfg & 0b00000010) {
						//if(msg == ASB_MSG_ON) { //Ignore Mode when in pulse mode
							//Pulsemode
							outstate |= (bchan);
							portout(outstate, bchan);
							//@todo System timeticks?
							_delay_ms(200);
							wdt_reset();
							_delay_ms(200);
							wdt_reset();
							_delay_ms(200);
							wdt_reset();
							outstate &= ~(bchan);
							portout(outstate, bchan);
						//}
					}else{
						if(msg == ASB_MSG_ON) {
							mask |= (bchan);
							if(portcfg & 0b00000100) {
								//Portausgang invertiert
								//Bit löschen
								outstate &= ~(bchan);
							}else{
								//Bit setzen
								outstate |= (bchan);
							}
						}else if(msg == ASB_MSG_OFF) {
							mask |= (bchan);
							if(portcfg & 0b00000100) {
								//Portausgang invertiert
								//Bit setzen
								outstate |= (bchan);
							}else{
								//Bit löschen
								outstate &= ~(bchan);
							}
						}
					}
				}
			}
		}
	}
	portout(outstate, mask);
}
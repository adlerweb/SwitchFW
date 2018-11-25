uint8_t port_bin2dec(uint8_t bin) {
	if(bin == 0b00000001) return 0;
	if(bin == 0b00000010) return 1;
	if(bin == 0b00000100) return 2;
	if(bin == 0b00001000) return 3;
	if(bin == 0b00010000) return 4;
	if(bin == 0b00100000) return 5;
	if(bin == 0b01000000) return 6;
	if(bin == 0b10000000) return 7;
	return 0;
} 

void outmsg(uint16_t addr, uint8_t msg, uint8_t pin)
{
	Isb_Msg_t Isb_Msg;
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_2;
	Isb_Msg.DestId = addr;
	//Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.SourceId = ((uint16_t)(port_bin2dec(pin) << 12) | (Asb_Node_Id & 0x0FFF));
	Isb_Msg.Data[0] = ASB_MSG_TOP_1BIT;
	Isb_Msg.Data[1] = msg;
	
	#ifdef ASB_INTERFACE_CAN
		Isb_SendMsg(&Isb_Msg);
	#endif
	
	#ifdef ASB_INTERFACE_USART0
		Isb_Inf_Usart_Tx(&Isb_Msg);
	#endif
	
	inmsgparser(addr, msg);
}

void inparser(uint8_t pin, uint8_t intrigger) {
	uint8_t pincfg;
	for(uint8_t i=0; i<32; i++) {
		pincfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF + 2 + ( 3 * i ) ));
		if(!(pincfg & ASB_GRPCFG_IO)) {
			//Gruppe ist ein Eingang
			uint8_t chan;
			chan = pincfg & 0b00011100;
			chan = chan >> 2;
			chan = (1 << chan);
			
			if(pin & chan) {
				//Gruppe ist für uns interessant, richtiger Eingang
				uint8_t trigger;
				trigger = pincfg & 0b11000000;
				trigger = trigger >> 6;
				if(trigger & intrigger) {
					//...und der Trigger auch
					uint8_t msg = pincfg & 0b00000011;
					
					//Bei Toggle Nachricht je nach letztem bekannten Status setzen
					if(msg == ASB_MSG_TOGGLE) {
						if(groupstate[(uint8_t)(i/8)] & (1<<i%8)) {
							msg = ASB_MSG_OFF;
						}else{
							msg = ASB_MSG_ON;
						}
					}
					outmsg(groupids[i], msg, pin);
				}
			}
		}
	}
}
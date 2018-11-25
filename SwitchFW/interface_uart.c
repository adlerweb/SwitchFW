/*
 * @author              Patrick Amrhein <trick-at-isysbus-dot-org> 01.05.2010
 * @author				Florian Knodt <adlerweb-at-adlerweb-dot-info> 22.10.2012
 *
 * @note
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses.
 */

#ifndef INF_UART_C
	#define INF_UART_C
	
	#if ASB_INTERFACE_USART0 == 1
		void uart_init(void)
		{			
			UBRRH = UBRR_VAL >> 8;
			UBRRL = UBRR_VAL & 0xFF;
			
			/*Interrupts ein, RX ein, TX ein*/
			UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
			
			UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);  // Asynchron 8N1 
			
			do {
				UDR;
			}while(UCSRA & (1<<RXC));
			
			Inf_Usart_Tx0_Buffer_Head = 0;
			Inf_Usart_Rx0_Buffer_Head = 0;
			Inf_Usart_Rx0_Buffer_Tail = Inf_Usart_Rx0_Buffer_Head;
			Inf_Usart_Tx0_Buffer_Tail = Inf_Usart_Tx0_Buffer_Head;
			
		}

		uint8_t Inf_Usart_Rx(uint8_t * aChar) {
			uint8_t Result = false;
				if (Inf_Usart_Rx0_Buffer_Head != Inf_Usart_Rx0_Buffer_Tail) {
					Inf_Usart_Rx0_Buffer_Tail = (Inf_Usart_Rx0_Buffer_Tail + 1) & INF_USART_RX0_BUFFER_MASK;
					*aChar = Inf_Usart_Rx0_Buffer[Inf_Usart_Rx0_Buffer_Tail];
					Result = true;
				}
			return Result;
		}
		
		ISR (USART_RXC_vect) {
			uint8_t Tmp_Head;
			Tmp_Head = (Inf_Usart_Rx0_Buffer_Head + 1) & INF_USART_RX0_BUFFER_MASK;
			if (Tmp_Head != Inf_Usart_Rx0_Buffer_Tail) {
				Inf_Usart_Rx0_Buffer[Tmp_Head] = UDR;
				Inf_Usart_Rx0_Buffer_Head = Tmp_Head;
			}
		}
		
		uint8_t Inf_Usart_Tx(const uint8_t aChar) {
			uint8_t Result = false;
			uint8_t Tmp_Head;
			
			cli();
			
			Tmp_Head = (Inf_Usart_Tx0_Buffer_Head + 1);
			if(Tmp_Head >= INF_USART_TX0_BUFFER_SIZE) {
				//Buffer voll!
				sei();
				return Result;
			}
			
			Inf_Usart_Tx0_Buffer[Tmp_Head] = aChar;
			Result = true;
			
			Inf_Usart_Tx0_Buffer_Head = Tmp_Head;
			
			if ((Inf_Usart_Tx0_Buffer_Head == Inf_Usart_Tx0_Buffer_Tail) || (!(UCSRB & (1 << UDRIE)))) {
				UCSRB |= (1 << UDRIE);
			}
			sei();
			return Result;
		}
		
		void uart_puts (const char *s) {
			while(*s) {
				Inf_Usart_Tx(*s);
				s++;
			}
		}
		
		void uart_puts_P(const char *s) {
			while(1) {
				unsigned char c = pgm_read_byte(s);
				s++;
				if(c == '\0') break;
				Inf_Usart_Tx(c);
			}
		}
		
		ISR (USART_UDRE_vect) {
			if (Inf_Usart_Tx0_Buffer_Head != Inf_Usart_Tx0_Buffer_Tail) {
				Inf_Usart_Tx0_Buffer_Tail = (Inf_Usart_Tx0_Buffer_Tail + 1) & INF_USART_TX0_BUFFER_MASK;
				UCSRA |= (1 << TXC);
				UDR = Inf_Usart_Tx0_Buffer[Inf_Usart_Tx0_Buffer_Tail];
			}
			else {
				Inf_Usart_Tx0_Buffer_Head=0;
				Inf_Usart_Tx0_Buffer_Tail=0;
				UCSRB &= ~(1 << UDRIE);
			}
		}
		
		/*****MESSAGE RELATED******/
		uint8_t Isb_Inf_Usart_Tx(const Isb_Msg_t * aIsb_Msg) {
			uint8_t Result = false;
			uint8_t Free_Space = 0;
			
			uint8_t aIsb_Msg_Dlc = aIsb_Msg->Flags & ISB_MSG_FLAGS_DLC_MASK;
			
			wdt_reset();
			do {
				cli();
				if (Inf_Usart_Tx0_Buffer_Tail > Inf_Usart_Tx0_Buffer_Head) {
					Free_Space = Inf_Usart_Tx0_Buffer_Tail - Inf_Usart_Tx0_Buffer_Head;
				}
				else {
					Free_Space = (Inf_Usart_Tx0_Buffer_Tail + INF_USART_TX0_BUFFER_SIZE - Inf_Usart_Tx0_Buffer_Head);
				}
				sei();
			}while(Free_Space <= (14+5*aIsb_Msg_Dlc+3));
			
			if (Free_Space > (9 + aIsb_Msg_Dlc)) {
				const char seperator = ':';
				char address[7];
				uart_puts_P(start);
				utoa(aIsb_Msg->Flags, address, 16);
				uart_puts(address);
				Inf_Usart_Tx(seperator);
				utoa(aIsb_Msg->DestId, address, 16);
				uart_puts(address);
				Inf_Usart_Tx(seperator);
				utoa(aIsb_Msg->SourceId, address, 16);
				uart_puts(address);
				Inf_Usart_Tx(seperator);
				for (uint8_t i = 0; i < aIsb_Msg_Dlc; i++) {
					utoa(aIsb_Msg->Data[i], address, 16);
					uart_puts(address);
					Inf_Usart_Tx(seperator);
				}
				utoa(Lib_Crc_Calc8(aIsb_Msg, (5 + aIsb_Msg_Dlc)), address, 16);
				uart_puts(address);
				uart_puts_P(stop);
				
				/*Inf_Usart_Tx(Startbyte);
				Inf_Usart_Tx(aIsb_Msg->Flags);
				Inf_Usart_Tx(0xAA);
				Inf_Usart_Tx((uint8_t)(aIsb_Msg->DestId & 0x00FF));
				Inf_Usart_Tx(0xBB);
				Inf_Usart_Tx((uint8_t)(aIsb_Msg->DestId >> 8));
				Inf_Usart_Tx(0xCC);
				Inf_Usart_Tx((uint8_t)(aIsb_Msg->SourceId & 0x00FF));
				Inf_Usart_Tx(0xDD);
				Inf_Usart_Tx((uint8_t)(aIsb_Msg->SourceId >> 8));
				Inf_Usart_Tx(0xEE);
				for (uint8_t i = 0; i < aIsb_Msg_Dlc; i++) {
					Inf_Usart_Tx(aIsb_Msg->Data[i]);
				}
				Inf_Usart_Tx(0x00);
				Inf_Usart_Tx(Lib_Crc_Calc8(aIsb_Msg, (5 + aIsb_Msg_Dlc)));
				Inf_Usart_Tx(Stopbyte);*/
				Result = true;
			}
			return Result;
		}
		
		uint8_t Isb_Inf_Usart_Rx(Isb_Msg_t * aIsb_Msg) {
			uint8_t Result = false;
			uint8_t Mask;
			static volatile uint8_t * Buffer;
			static volatile uint8_t * Head;
			static volatile uint8_t * Tail;
			uint8_t Startbyte = 0;
			uint8_t Stopbyte = 0;
			
			Mask = INF_USART_RX0_BUFFER_MASK;
			Buffer = Inf_Usart_Rx0_Buffer;
			Head = &Inf_Usart_Rx0_Buffer_Head;
			Tail = &Inf_Usart_Rx0_Buffer_Tail;
			Startbyte = ISB_INF_USART0_STARTBYTE;
			Stopbyte = ISB_INF_USART0_STOPBYTE;
				
			uint8_t Tmp_Tail;
			uint8_t Rel_Pos = 0;
			uint8_t Start_Pos = 0;
			uint8_t Isb_Msg_Dlc = 0;
			Tmp_Tail = (*Tail + 1) & Mask;
			while (Tmp_Tail != ((*Head + 1) & Mask)) {
				if (Rel_Pos == 0) {
					if (Buffer[Tmp_Tail] == Startbyte) {
						Start_Pos = Tmp_Tail;
						Rel_Pos++;
					}
					else {
						*Tail = Tmp_Tail;
						Rel_Pos = 0;
					}
				}
				else if (Rel_Pos == 1) {
					aIsb_Msg->Flags = Buffer[Tmp_Tail];
					Rel_Pos++;
					if (bit_is_clear (aIsb_Msg->Flags, 6)) {
						Isb_Msg_Dlc = aIsb_Msg->Flags & ISB_MSG_FLAGS_DLC_MASK;
					}
				}
				else if (Rel_Pos == 2) {
					aIsb_Msg->DestId = (uint16_t)Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if (Rel_Pos == 3) {
					aIsb_Msg->DestId += (uint16_t)(Buffer[Tmp_Tail] << 8);
					Rel_Pos++;
				}
				else if (Rel_Pos == 4) {
					aIsb_Msg->SourceId = (uint16_t)Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if (Rel_Pos == 5) {
					aIsb_Msg->SourceId += (uint16_t)(Buffer[Tmp_Tail] << 8);
					Rel_Pos++;
				}
				else if ((Rel_Pos == 6) & (Isb_Msg_Dlc >= 1)) {
					aIsb_Msg->Data[0] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 7) & (Isb_Msg_Dlc >= 2)) {
					aIsb_Msg->Data[1] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 8) & (Isb_Msg_Dlc >= 3)) {
					aIsb_Msg->Data[2] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 9) & (Isb_Msg_Dlc >= 4)) {
					aIsb_Msg->Data[3] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 10) & (Isb_Msg_Dlc >= 5)) {
					aIsb_Msg->Data[4] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 11) & (Isb_Msg_Dlc >= 6)) {
					aIsb_Msg->Data[5] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 12) & (Isb_Msg_Dlc >= 7)) {
					aIsb_Msg->Data[6] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if ((Rel_Pos == 13) & (Isb_Msg_Dlc == 8)) {
					aIsb_Msg->Data[7] = Buffer[Tmp_Tail];
					Rel_Pos++;
				}
				else if (Rel_Pos == (6 + Isb_Msg_Dlc)) {
					Rel_Pos++;
				}
				else if (Rel_Pos == (7 + Isb_Msg_Dlc)) {
					if (Buffer[Tmp_Tail] == Lib_Crc_Calc8(aIsb_Msg, (5 + Isb_Msg_Dlc))) {
						Rel_Pos++;
					}
					else {
						*Tail = Start_Pos;
						Rel_Pos = 0;
						continue;
					}
				}
				else if (Rel_Pos == (8 + Isb_Msg_Dlc)) {
					if (Buffer[Tmp_Tail] != Stopbyte) {
						*Tail = Start_Pos;
						Rel_Pos = 0;
						continue;
					}
					else {
						*Tail = Tmp_Tail;
						Result = true;
					}
				}
				Tmp_Tail = (Tmp_Tail + 1) & Mask;
			}
			return Result;
		}
		
		#ifdef BUILD_THRIO_RFID
		    uint64_t Rfid_Inf_Usart_Rx() {
			    uint64_t Result = 0;
			    uint8_t Mask;
			    static volatile uint8_t * Buffer;
			    static volatile uint8_t * Head;
			    static volatile uint8_t * Tail;
			    
			    Mask = INF_USART_RX0_BUFFER_MASK;
			    Buffer = Inf_Usart_Rx0_Buffer;
			    Head = &Inf_Usart_Rx0_Buffer_Head;
			    Tail = &Inf_Usart_Rx0_Buffer_Tail;			    
			    uint8_t Tmp_Tail;
			    uint8_t Rel_Pos = 0;
			    Tmp_Tail = (*Tail + 1) & Mask;
				
			    while (Tmp_Tail != ((*Head + 1) & Mask)) {
				    Result <<= 4;
					if(Buffer[Tmp_Tail] >= 0x30 && Buffer[Tmp_Tail] <= 0x39) Result += (Buffer[Tmp_Tail]-0x30);
					if(Buffer[Tmp_Tail] >= 0x41 && Buffer[Tmp_Tail] <= 0x46) Result += ((Buffer[Tmp_Tail]-0x41)+10);
					Rel_Pos++;
				    Tmp_Tail = (Tmp_Tail + 1) & Mask;
					if(Buffer[Tmp_Tail-1] == 0x10 || Buffer[Tmp_Tail-1] == 0x13) {
						*Tail = Tmp_Tail;
						return Result;
					}
			    }
				
			    return Result;
			}
		#endif
	#endif
#endif

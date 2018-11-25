/*
 * SwitchFW.c
 *
 * This file includes the aSysBus switching-core.
 *
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


#include <avr/io.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined(BUILD_THRIO)
	#define ASB_INTERFACE_CAN0 1
	#include "BRD_3_2_1.h"
#elif defined(BUILD_PROMINI)
	#define ASB_INTERFACE_CAN0 1
	#define ASB_INTERFACE_USART0 1
	#include "BRD_4_0_0.h"
#elif defined(BUILD_THRIO_RFID)
	#define ASB_INTERFACE_CAN0 1
	#define ASB_INTERFACE_USART0 1
	#include "BRD_3_2_1.h"
#elif defined(BUILD_DEVBRD)
	#define ASB_INTERFACE_CAN0 1
	#define ASB_INTERFACE_USART0 1
	#include "BRD_1_3_0.h"
#else
	#error Board not defined
#endif


#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "stubs.h"
#include "asb_eeprom_addr.h"
#include "asb_protocol.h"
#include "eeplib.c"
#include "debounce.c"
#include "pwmlib.c"
#include "asb_typ.h"
#include "pinlib.c"
#include "libspi.h"
#include "libspi.c"
#include "mcp2515.h"
#include "mcp2515.c"


#if defined(BUILD_THRIO_RFID)
	#include "sht11.h"
	int16_t temperature=0;
	uint16_t humidity=0;
#endif

ISR(INT0_vect) {
	return;
}

#ifdef BRD_3_2_1
void portout(uint8_t out, uint8_t mask) {
	if(mask & 0b00000001) {
		if (( out & 0b00000001 )) {
			PORTC |= ((1 << PC7));
			}else{
			PORTC &= ~((1 << PC7));
		}
	}
	if(mask & 0b00000010) {
		if (( out & 0b00000010 )) {
			PORTC |= ((1 << PC6));
			}else{
			PORTC &= ~((1 << PC6));
		}
	}
	if(mask & 0b00000100) {
		if (( out & 0b00000100 )) {
			PORTC |= ((1 << PC1));
			}else{
			PORTC &= ~((1 << PC1));
		}
	}
	if(mask & 0b00001000) {
		if (( out & 0b00001000 )) {
			PORTC |= ((1 << PC0));
			}else{
			PORTC &= ~((1 << PC0));
		}
	}
	if(mask & 0b00010000) {
		if (( out & 0b00010000 )) {
			PORTD |= ((1 << PD7));
			}else{
			PORTD &= ~((1 << PD7));
		}
	}
	if(mask & 0b00100000) {
		if (( out & 0b00100000 )) {
			PORTD |= ((1 << PD6));
			}else{
			PORTD &= ~((1 << PD6));
		}
	}
	if(mask & 0b01000000) {
		if (( out & 0b01000000 )) {
			PORTD |= ((1 << PD5));
			}else{
			PORTD &= ~((1 << PD5));
		}
	}
	if(mask & 0b10000000) {
		if (( out & 0b10000000 )) {
			PORTD |= ((1 << PD4));
			}else{
			PORTD &= ~((1 << PD4));
		}
	}
}
#endif

#ifdef BRD_4_0_0
void portout(uint8_t out, uint8_t mask) {
	if(mask & 0b00000001) {
		if (( out & 0b00000001 )) {
			PORTD |= ((1 << PD2));
			}else{
			PORTD &= ~((1 << PD2));
		}
	}
	if(mask & 0b00000010) {
		if (( out & 0b00000010 )) {
			PORTD |= ((1 << PD3));
			}else{
			PORTD &= ~((1 << PD3));
		}
	}
	if(mask & 0b00000100) {
		if (( out & 0b00000100 )) {
			PORTD |= ((1 << PD4));
			}else{
			PORTD &= ~((1 << PD4));
		}
	}
	if(mask & 0b00001000) {
		if (( out & 0b00001000 )) {
			PORTD |= ((1 << PD5));
			}else{
			PORTD &= ~((1 << PD5));
		}
	}
	if(mask & 0b00010000) {
		if (( out & 0b00010000 )) {
			PORTD |= ((1 << PD6));
			}else{
			PORTD &= ~((1 << PD6));
		}
	}
	if(mask & 0b00100000) {
		if (( out & 0b00100000 )) {
			PORTD |= ((1 << PD7));
			}else{
			PORTD &= ~((1 << PD7));
		}
	}
	if(mask & 0b01000000) {
		if (( out & 0b01000000 )) {
			PORTB |= ((1 << PB0));
			}else{
			PORTB &= ~((1 << PB0));
		}
	}
	if(mask & 0b10000000) {
		if (( out & 0b10000000 )) {
			PORTB |= ((1 << PB1));
			}else{
			PORTB &= ~((1 << PB1));
		}
	}
}
#endif

#ifdef BRD_1_3_0
void portout(uint8_t out, uint8_t mask) {
	if(mask & 0b00000001) {
		if (( out & 0b00000001 )) {
			PORTC |= ((1 << PC7));
			}else{
			PORTC &= ~((1 << PC7));
		}
	}
	if(mask & 0b00000010) {
		if (( out & 0b00000010 )) {
			PORTC |= ((1 << PC6));
			}else{
			PORTC &= ~((1 << PC6));
		}
	}
	if(mask & 0b00000100) {
		if (( out & 0b00000100 )) {
			PORTC |= ((1 << PD5));
			}else{
			PORTC &= ~((1 << PD5));
		}
	}
	if(mask & 0b00001000) {
		if (( out & 0b00001000 )) {
			PORTC |= ((1 << PD4));
			}else{
			PORTC &= ~((1 << PD4));
		}
	}
	if(mask & 0b00010000) {
		if (( out & 0b00010000 )) {
			PORTD |= ((1 << PD3));
			}else{
			PORTD &= ~((1 << PD3));
		}
	}
	if(mask & 0b00100000) {
		if (( out & 0b00100000 )) {
			PORTD |= ((1 << PD2));
			}else{
			PORTD &= ~((1 << PD2));
		}
	}
	if(mask & 0b01000000) {
		if (( out & 0b01000000 )) {
			PORTD |= ((1 << PD1));
			}else{
			PORTD &= ~((1 << PD1));
		}
	}
	if(mask & 0b10000000) {
		if (( out & 0b10000000 )) {
			PORTD |= ((1 << PD0));
			}else{
			PORTD &= ~((1 << PD0));
		}
	}
}
#endif


#include "interface_can.h"
#include "interface_can.c"
#include "interface_uart.h"
#include "interface_uart.c"
#include "hexatoi.c"

static uint16_t Asb_Node_Id = 0;
uint8_t instate=0;
uint8_t inact=0;
uint8_t outstate=0;

uint8_t groupstate[3];
uint16_t groupids[31];

void Node_Reboot(void) {
	while (1);
}

#include "sw_msg_in.c"
#include "sw_msg_out.c"

void incheck(uint8_t pin, uint8_t porttemp, uint8_t instate) {
	if ((porttemp & pin) != (instate & pin)) {
		if(porttemp & pin) {
			inparser(pin, ASB_TRIGGER_UP);
		}else{
			inparser(pin, ASB_TRIGGER_DOWN);
		}
	}
}

void sendbootmsg() { //Benachrichtigt den Bus über unseren (re)Start
	Isb_Msg_t Isb_Msg;
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_1;
	Isb_Msg.DestId = ISB_MSG_MULTICAST_GROUPID_FW_START;
	Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.Data[0] = ISB_MSG_TOP__SERIAL_NUMBER__MODE__ERROR;
	
	#ifdef  ASB_INTERFACE_CAN
		Isb_SendMsg(&Isb_Msg);
	#endif
	
	#ifdef  ASB_INTERFACE_USART0
		Isb_Inf_Usart_Tx(&Isb_Msg);
	#endif
	
}

void pong(uint16_t dest) {
	Isb_Msg_t Isb_Msg;
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_1;
	Isb_Msg.DestId = dest;
	Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.Data[0] = ASB_MSG_TOP_PONG;
	#ifdef  ASB_INTERFACE_CAN
		Isb_SendMsg(&Isb_Msg);
	#endif
	
	#ifdef  ASB_INTERFACE_USART0
		Isb_Inf_Usart_Tx(&Isb_Msg);
	#endif
}

void sendcfg(uint16_t dest, uint8_t grpid) {
	uint16_t grpaddr=0;
	uint8_t grpcfg=0;
	
	grpaddr=lib_eep_read_word((uint16_t *)(EEP__ASB_FIRST_GRPDEF+(3*grpid)));
	grpcfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF + 2 + ( 3 * grpid ) ));
	
	Isb_Msg_t Isb_Msg;
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_5;
	Isb_Msg.DestId = dest;
	Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.Data[0] = ASB_MSG_TOP_CFG_READ;
	Isb_Msg.Data[1] = grpid;
	Isb_Msg.Data[2] = (uint8_t)grpaddr>>8;
	Isb_Msg.Data[3] = (uint8_t)grpaddr & 0x00FF;
	Isb_Msg.Data[4] = grpcfg;

	#ifdef  ASB_INTERFACE_CAN
		Isb_SendMsg(&Isb_Msg);
	#endif
	
	#ifdef  ASB_INTERFACE_USART0
		Isb_Inf_Usart_Tx(&Isb_Msg);
	#endif
}

void readcfg(uint16_t dest, uint8_t grpid, uint8_t grpaddr_h, uint8_t grpaddr_l, uint8_t grpcfg) {
	uint16_t grpaddr = ((grpaddr_h << 8) & grpaddr_l);
	lib_eep_write_word((uint16_t *)(EEP__ASB_FIRST_GRPDEF+(3*grpid)), grpaddr);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF+2+(3*grpid)), grpcfg);
	sendcfg(dest, grpid);
}

void readgroupids() {
	uint16_t grptemp=0;
	
	for(uint8_t i=0; i<32; i++) {
		grptemp=lib_eep_read_word((uint16_t *)(EEP__ASB_FIRST_GRPDEF+(3*i)));
		if(grptemp != 0xFFFF) groupids[i] = grptemp;
	}
}

void debugeeprom() {
	lib_eep_write_word((uint16_t *)(EEP__ASB_NODE_ID_0), 0x0A10);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_INCFG), 0xFF);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_OUTCFG+0), 0x80);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_OUTCFG+1), 0x08);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_OUTCFG+2), 0x00);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_OUTCFG+3), 0x00);
	lib_eep_write_word((uint16_t *)(EEP__ASB_FIRST_GRPDEF), 0xAA11);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF+2), 0xCA);
	lib_eep_write_word((uint16_t *)(EEP__ASB_FIRST_GRPDEF+3), 0xAA11);
	lib_eep_write_byte((uint8_t *)(EEP__ASB_FIRST_GRPDEF+3+2), 0x2C);
}

void parsemsg(Isb_Msg_t Isb_Msg) {
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_4)) && (Isb_Msg.DestId == Asb_Node_Id) && (Isb_Msg.Data[0] == ASB_MSG_TOP_SET_NODEID)) {
		if((Isb_Msg.Data[1] ^ Isb_Msg.Data[2]) == Isb_Msg.Data[3]) {
			lib_eep_write_byte((uint8_t *)(EEP__ASB_NODE_ID_0), Isb_Msg.Data[1]);
			lib_eep_write_byte((uint8_t *)(EEP__ASB_NODE_ID_1), Isb_Msg.Data[2]);
			Node_Reboot();
		}
	}
	
	//Eingehende IO-Nachrichten parsen
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_2)) && (Isb_Msg.Data[0] == ASB_MSG_TOP_1BIT)) {
		inmsgparser(Isb_Msg.DestId, Isb_Msg.Data[1]);
	}
	
	//Eingehende Dimmer-Nachrichten
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_2)) && (Isb_Msg.Data[0] == ASB_MSG_TOP_DIMMER)) {
		inmsgpwmparser(Isb_Msg.DestId, Isb_Msg.Data[1]);
	}
	
	//PINGPING
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_1)) && (Isb_Msg.DestId == Asb_Node_Id) && (Isb_Msg.Data[0] == ASB_MSG_TOP_PING)) {
		pong(Isb_Msg.SourceId);
	}
	
	//Config lesen
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_2)) && (Isb_Msg.DestId == Asb_Node_Id) && (Isb_Msg.Data[0] == ASB_MSG_TOP_CFG_READ)) {
		sendcfg(Isb_Msg.SourceId, Isb_Msg.Data[1]);
	}
	
	//Config schreiben
	if((Isb_Msg.Flags == (ISB_MSG_FLAGS_TOF_UNICAST | ISB_MSG_FLAGS_DLC_5)) && (Isb_Msg.DestId == Asb_Node_Id) && (Isb_Msg.Data[0] == ASB_MSG_TOP_CFG_WRITE)) {
		readcfg(Isb_Msg.SourceId, Isb_Msg.Data[1], Isb_Msg.Data[2], Isb_Msg.Data[3], Isb_Msg.Data[4]);
	}
}

#ifdef BUILD_THRIO_RFID
void sendrfidmsg(uint16_t target) {
	Isb_Msg_t Isb_Msg;
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_5;
	Isb_Msg.DestId = target;
	Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.Data[0] = ISB_MSG_TOP_1BIT;
	Isb_Msg.Data[1] = ASB_MSG_ON;

	#ifdef  ASB_INTERFACE_CAN
	Isb_SendMsg(&Isb_Msg);
	#endif
	parsemsg(Isb_Msg);
}

void sendshtmsg(uint16_t target) {
	Isb_Msg_t Isb_Msg;
	
	Isb_Msg.Flags = ISB_MSG_FLAGS_TOF_MULTICAST | ISB_MSG_FLAGS_DLC_6;
	Isb_Msg.DestId = target;
	Isb_Msg.SourceId = Asb_Node_Id;
	Isb_Msg.Data[0] = ISB_MSG_TOP_4BIT;
	Isb_Msg.Data[1] = (uint8_t) temperature >> 8;
	Isb_Msg.Data[2] = (uint8_t) temperature & 0xFF;
	Isb_Msg.Data[3] = (uint8_t) humidity >> 8;
	Isb_Msg.Data[4] = (uint8_t) humidity & 0xFF;

	#ifdef  ASB_INTERFACE_CAN
	Isb_SendMsg(&Isb_Msg);
	#endif
	parsemsg(Isb_Msg);
}
/////////////////////////////////////////////////////////////////////////////

uint8_t crc_value;

void sht_crc8(uint8_t b) {
	for (uint8_t i = 0; i < 8; ++i) {
		if ((crc_value ^ b) & 0x80) {
			crc_value <<= 1;
			crc_value ^= 0x31;
		} else
		crc_value <<= 1;
		b <<= 1;
	}
}

/////////////////////////////////////////////////////////////////////////////

uint8_t sht_send(uint16_t b) {
	sht_crc8(b);
	
	// data
	for (uint8_t i = 0; i < 8; ++i) {
		if (b & 0x80)
			sda_hi();
		else
			sda_lo();
		
		b <<= 1;
		delay();
		scl_pulse();
	}

	// acknowledge
	sda_hi();
	delay();
	uint8_t ack = sda_val();
	scl_pulse();
	return ack;
}

uint8_t sht_recv_data(void) {
	// data
	uint8_t b = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		// data is transmitted MSB first
		b <<= 1;
		if (sda_val())
			b |= 1;
		scl_pulse();
		delay();
	}

	// lo acknowledge
	sda_lo();
	delay();
	scl_pulse();
	sda_hi();
	delay();

	sht_crc8(b);
	return b;
}

uint8_t sht_recv_crc(void) {
	// data
	uint8_t b = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		// CRC is transmitted LSB first
		b >>= 1;
		if (sda_val())
			b |= 0x80;
		scl_pulse();
		delay();
	}

	// hi acknowledge
	sda_hi();
	delay();
	scl_pulse();
	delay();

	return b;
}

void sht_start(void) {
	clrBits(SHT11_PORT, SHT11_SCL | SHT11_SDA);	// SCK output low, SDA input/high
	setBits(SHT11_DDR,  SHT11_SCL);
	clrBits(SHT11_DDR,  SHT11_SDA);
	delay();

	// reset communication
	for (uint8_t i = 0; i < 10; ++i) {
		scl_pulse();
		delay();
	}

	// "start" sequence
	scl_hi(); delay();
	sda_lo(); delay();
	scl_lo(); delay();
	scl_hi(); delay();
	sda_hi(); delay();
	scl_lo(); delay();
}

/////////////////////////////////////////////////////////////////////////////
// Measurement sequence.

uint8_t sht11_start_temp(void) {
	crc_value = SHT11_LOWRES << 7; // bit-reversed
	sht_start();
	return sht_send(SHT11_CMD_TEMP) == 0;
}

uint8_t sht11_start_humid(void) {
	crc_value = SHT11_LOWRES << 7; // bit-reversed
	sht_start();
	return sht_send(SHT11_CMD_HUMID) == 0;
}

uint8_t
sht11_ready(void)
{
	return sda_val() == 0;
}

int16_t sht_result(void) {
	if (!sht11_ready())
		return SHT11_UNAVAIL;
	int16_t v = sht_recv_data() << 8; v |= sht_recv_data();
	uint8_t crc = sht_recv_crc();
	if (crc != crc_value)
		return SHT11_CRC_FAIL;
	return v;
}

int16_t sht11_result_temp(void) {
	int16_t v = sht_result();
	if (sht11_valid(v)) {
		#if SHT11_LOWRES
			v = v * 4 - 4000;
		#else
			v -= 4000;
		#endif
	}
	return v;
}

int16_t sht11_result_humid(void) {
	int16_t v = sht_result();
	if (sht11_valid(v)) {
		#if SHT11_LOWRES
			// inspired by Werner Hoch, modified for low resolution mode
			const int32_t C1 = (int32_t)(-4.0 * 100);
			const int32_t C2 = (int32_t)(0.648 * 100 * (1L<<24));
			const int32_t C3 = (int32_t)(-7.2e-4 * 100 * (1L<<24));
			v = (int16_t)((((C3 * v + C2) >> 7) * v + (1L<<16)) >> 17) + C1;
		#else
			// inspired by Werner Hoch
			const int32_t C1 = (int32_t)(-4.0 * 100);
			const int32_t C2 = (int32_t)(0.0405 * 100 * (1L<<28));
			const int32_t C3 = (int32_t)(-2.8e-6 * 100 * (1L<<30));
			v =(int16_t)((((((C3 * v) >> 2) + C2) >> 11) * v + (1L<<16)) >> 17) + C1;
		#endif
	}
	return v;
}

/////////////////////////////////////////////////////////////////////////////
// Initialize.

void sht11_init(void) {
	sht_start();
	sht_send(SHT11_CMD_RESET);
	wdt_reset();
	_delay_ms(5);
	wdt_reset();
	_delay_ms(6);
	wdt_reset();

	sht_start();
	sht_send(SHT11_CMD_WSTAT);
	sht_send(SHT11_LOWRES);
}


void sht_scratch_temp(void) {
	sht11_start_temp();
	while (!sht11_ready())
		wdt_reset();
	temperature = sht11_result_temp();
}

void sht_scratch_humid(void) {
	sht11_start_humid();
	while (!sht11_ready())
		wdt_reset();
	humidity = sht11_result_humid();
}
#endif

#ifdef BUILD_THRIO_RFID
	static const uint64_t rfid1 PROGMEM = 0x010B3FC2D3;
	static const uint64_t rfid2 PROGMEM = 0x24003E7693;
#endif

int main(void)
{	
    #ifdef BUILD_THRIO_RFID
        uint64_t rfidchk;
	
	uint8_t rounds=0;
    #endif

	wdt_enable(WDTO_500MS);
	wdt_reset();
	
	//debugeeprom();
	
	//Datenrichtungen (grob) einstellen
	#ifdef BRD_3_2_1
		DDRA = 0x00;
		PORTA = 0xff; //Pullup
		DDRC = 0xff;
		DDRD = 0xff;
	#endif
	
	#ifdef BRD_4_0_0
		DDRB  = 0b11000000;
		PORTB = 0b00111100; //Pullup
		DDRC  = 0b00000000;
		PORTC = 0b00001111; //Pullup
		DDRD  = 0b00111111; //0+1 = RS232
	#endif
	
	#ifdef BRD_1_3_0
		DDRA  = 0x00;
		PORTA = 0xff; //Pullup
		DDRB  = 0b00000000;
		PORTB = 0b00000011;
		DDRC  = 0xff;
		DDRD  = 0xff;
	#endif
	
	//Knoten-ID auslesen
	Asb_Node_Id = lib_eep_read_word((uint16_t *)EEP__ASB_NODE_ID_0);
	
	wdt_reset();
	
	//Wenn keine ID gesetzt ist Dummy-ID schreiben
	if ((Asb_Node_Id == 0x0000) | (Asb_Node_Id > 0x07FF)) {
		lib_eep_write_word((uint16_t *)(EEP__ASB_NODE_ID_0), 0x0001);
		Asb_Node_Id = lib_eep_read_word((uint16_t *)EEP__ASB_NODE_ID_0);
	}
	
	inact = lib_eep_read_byte((uint8_t *)EEP__ASB_INCFG);

	wdt_reset();
	
	//@todo: Inizialisierung der Ausgänge
	readgroupids();
	wdt_reset();
	instate = PORTA ^ 0xFF;
	
	sei();
	
	#ifdef BRD_1_3_0
		//INT0 = CAN - we don't use it but it wakes us if needed ;)
		MCUCR |= (1<<ISC01);
		GICR |= (1<<INT0);
	#endif
	
	pwm_init();
	wdt_reset();
	
	#ifdef  ASB_INTERFACE_CAN
		Isb_Inf_Can_Init(0);
		wdt_reset();
	#endif
	
	#ifdef  ASB_INTERFACE_USART0
		uart_init();
		wdt_reset();
	#endif
	
	sendbootmsg();
	wdt_reset();
	
	Isb_Msg_t Isb_Msg;
	
	//Hauptschleife
	while(1){
		wdt_reset();
		
		#ifdef ASB_INTERFACE_CAN
			//Prüfe ob wir eine neue ID erhalten sollen
			
			if (Isb_Inf_Can_Rx(0, &Isb_Msg) == true) {
				_delay_ms(200);
				#ifdef ASB_INTERFACE_USART0
					Isb_Inf_Usart_Tx(&Isb_Msg);
				#endif
				parsemsg(Isb_Msg);
			}
		#endif
		
		#ifdef ASB_INTERFACE_USART0
			#ifndef BUILD_THRIO_RFID
			    if (Isb_Inf_Usart_Rx(&Isb_Msg) == true) {
				    #ifdef ASB_INTERFACE_CAN
					    Isb_SendMsg(&Isb_Msg);
				    #endif
				    parsemsg(Isb_Msg);
			    }
			#else
			    //UART is used for incoming RFID-IDs
			    rfidchk = Rfid_Inf_Usart_Rx();
			    if(rfidchk > 0) {
			        if(rfidchk == rfid1) {
			            sendrfidmsg(0x1010);
			        }else if(rfidchk == rfid2) {
			            sendrfidmsg(0x1011);
			        }
			    }
			#endif
		#endif
		
		#ifdef BRD_3_2_1
			//Eingänge lesen und bei Änderung verarbeiten
			uint8_t porttemp=0;
			//porttemp = PINA;
			//porttemp ^= 0xff; //invert everything - if input is high the optocoupler pulls low
			porttemp = key_state;
			porttemp &= inact;
			if(instate != porttemp) {
				incheck((1<<PA0), porttemp, instate);
				incheck((1<<PA1), porttemp, instate);
				incheck((1<<PA2), porttemp, instate);
				incheck((1<<PA3), porttemp, instate);
				incheck((1<<PA4), porttemp, instate);
				incheck((1<<PA5), porttemp, instate);
				incheck((1<<PA6), porttemp, instate);
				incheck((1<<PA7), porttemp, instate);
				instate = porttemp;
			}
		#endif
		#ifdef BRD_4_0_0
			//Eingänge lesen und bei Änderung verarbeiten
			uint8_t porttemp=0;
			porttemp = (((PINB & 0b00111100) <<2) | (PINC & 0b00001111));
			porttemp &= inact;
			if(instate != porttemp) {
				incheck((1<<0), porttemp, instate);
				incheck((1<<1), porttemp, instate);
				incheck((1<<2), porttemp, instate);
				incheck((1<<3), porttemp, instate);
				incheck((1<<4), porttemp, instate);
				incheck((1<<5), porttemp, instate);
				incheck((1<<6), porttemp, instate);
				incheck((1<<7), porttemp, instate);
				instate = porttemp;
			}
		#endif
		#ifdef BRD_1_3_0
			//Eingänge lesen und bei Änderung verarbeiten
			uint8_t porttemp=0;
			porttemp = ((PINA & 0b11111100) | (PINB & 0b00000011));
			porttemp &= inact;
			if(instate != porttemp) {
				incheck((1<<PB0), porttemp, instate);
				incheck((1<<PB1), porttemp, instate);
				incheck((1<<PA2), porttemp, instate);
				incheck((1<<PA3), porttemp, instate);
				incheck((1<<PA4), porttemp, instate);
				incheck((1<<PA5), porttemp, instate);
				incheck((1<<PA6), porttemp, instate);
				incheck((1<<PA7), porttemp, instate);
				instate = porttemp;
			}
		#endif
		
		#ifdef BUILD_THRIO_RFID
			if(systicktrigger == true) {
				rounds++;
				if(rounds>20) { //alle 5.12 Sekunden
					rounds=0;
					sht_scratch_temp();
					sht_scratch_humid();
					sendshtmsg(0x1011);
				}
			}
		#endif
		
		systicktrigger = false;

		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
	}	
}

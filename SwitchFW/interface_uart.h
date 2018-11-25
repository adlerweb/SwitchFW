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

#ifndef INF_UART_DEF_H_
	#define INF_UART_DEF_H_
	
	#if ASB_INTERFACE_USART0 == 1
		#define ASB_INTERFACE_USART0_TX
		#define ASB_INTERFACE_USART0_RX

        #ifndef BUILD_THRIO_RFID
		    #define BAUD                                 19200L
		#else   //Pollin RFID-Board
		    #define BAUD                                 9600L
		#endif
		
		#define INF_USART_RX0_BUFFER_SIZE 64
		#define INF_USART_TX0_BUFFER_SIZE 128
		#define INF_USART_RX0_BUFFER_MASK (INF_USART_RX0_BUFFER_SIZE - 1)
		#define INF_USART_TX0_BUFFER_MASK (INF_USART_TX0_BUFFER_SIZE - 1)
		
		static volatile uint8_t Inf_Usart_Rx0_Buffer[INF_USART_RX0_BUFFER_SIZE];
		static volatile uint8_t Inf_Usart_Rx0_Buffer_Tail = 0;
		static volatile uint8_t Inf_Usart_Rx0_Buffer_Head = 0;
		
		static volatile uint8_t Inf_Usart_Tx0_Buffer[INF_USART_TX0_BUFFER_SIZE];
		static volatile uint8_t Inf_Usart_Tx0_Buffer_Tail = 0;
		static volatile uint8_t Inf_Usart_Tx0_Buffer_Head = 0;
		
		#define ISB_INF_USART0_STARTBYTE				0x01
		#define ISB_INF_USART0_STOPBYTE					0x0D
		
		const char start[] PROGMEM = "\r\n>";
		const char stop[] PROGMEM = "<\r\n";
		
		#include "../../lib/asb_def.h"
		//#include "../../hwdefs/cpu/io_usart.h"
		#include "../../lib/lib_crc.h"
		#include "../../lib/lib_crc.c"
		
		#ifndef F_CPU
			#error "F_CPU missing"
		#endif
 
		// Berechnungen
		#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
		#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
		#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
 
		#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
		  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
		#endif 
	#endif
#endif

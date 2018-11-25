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

#ifndef INF_CAN_DEF_H_
	#define INF_CAN_DEF_H_

	#if ASB_INTERFACE_CAN0 == 1
		#define ASB_INTERFACE_CAN
		#define ASB_INTERFACE_CAN0_TX
		#define ASB_INTERFACE_CAN0_RX

		#define ASB_INTERFACE_CAN0                      1
		#define ASB_INTERFACE_CAN0_CLOCK				4000000
		#define ASB_INTERFACE_CAN0_SPEED				125000
		#define ASB_INTERFACE_CAN0_RS					MCP2515_RX1BF
		#define ASB_INTERFACE_CAN0_MODE					LIB_MCP2515_MODE_NORMAL
		
		#ifdef BRD_3_2_1
			#define ASB_INTERFACE_CAN0_INT					INTERRUPT0
			#define ASB_INTERFACE_CAN0_SS					PORTB_PIN4
		#endif
		#ifdef BRD_1_3_0
			#define ASB_INTERFACE_CAN0_INT					INTERRUPT2
			#define ASB_INTERFACE_CAN0_SS					PORTB_PIN4
		#endif

		#include "../../hwdefs/cpu/io_can.h"
		#include "../../hwdefs/cpu/io_spi.h"
		#include "../../lib/lib_mcp2515_def.h"
	#endif /* ASB_INTERFACE */

	#if defined(ASB_INTERFACE_CAN0)
		#if ASB_INTERFACE_CAN0_CLOCK == 2000000 & ASB_INTERFACE_CAN0_SPEED == 50000
		#define ASB_INTERFACE_CAN0_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN0_CNF1							0x00
		#define ASB_INTERFACE_CAN0_CNF2							0xB6
		#define ASB_INTERFACE_CAN0_CNF3							0x04
		#elif ASB_INTERFACE_CAN0_CLOCK == 4000000 & ASB_INTERFACE_CAN0_SPEED == 50000
		//#define ASB_INTERFACE_CAN0_SPICFG						0x03
		//Macht imo keinen sinn - setzt nur die Taktrate aber schaltet SPI nicht ein?!
		#define ASB_INTERFACE_CAN0_SPICFG                       0b01010011
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN0_CNF1							0x01
		#define ASB_INTERFACE_CAN0_CNF2							0xB6
		#define ASB_INTERFACE_CAN0_CNF3							0x04
		#elif ASB_INTERFACE_CAN0_CLOCK == 8000000 & ASB_INTERFACE_CAN0_SPEED == 50000
		#define ASB_INTERFACE_CAN0_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN0_CNF1							0x03
		#define ASB_INTERFACE_CAN0_CNF2							0xB6
		#define ASB_INTERFACE_CAN0_CNF3							0x04
		#elif ASB_INTERFACE_CAN0_CLOCK == 4000000 & ASB_INTERFACE_CAN0_SPEED == 125000
		//#define ASB_INTERFACE_CAN0_SPICFG						0x03
		#define ASB_INTERFACE_CAN0_SPICFG                       0b01010000
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN0_CNF1							0x00
		#define ASB_INTERFACE_CAN0_CNF2							0xAC
		#define ASB_INTERFACE_CAN0_CNF3							0x03
		#elif ASB_INTERFACE_CAN0_CLOCK == 8000000 & ASB_INTERFACE_CAN0_SPEED == 125000
		#define ASB_INTERFACE_CAN0_SPICFG						0x03
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN0_CNF1							0x01
		#define ASB_INTERFACE_CAN0_CNF2							0xAC
		#define ASB_INTERFACE_CAN0_CNF3							0x03
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN0_CLOCK | ASB_INTERFACE_CAN0_SPEED"
		#endif

		#if ASB_INTERFACE_CAN0_SS == PORTB_PIN0
			#define ASB_INTERFACE_CAN0_SSPORT							0x02
			#define ASB_INTERFACE_CAN0_SSPIN							0x00
			#define ASB_INTERFACE_CAN0_SS_INIT							DDRB |= (1 << DDB0)
			#define ASB_INTERFACE_CAN0_SS_LOW							PORTB &= ~(1 << PB0)
			#define ASB_INTERFACE_CAN0_SS_HIGH							PORTB |= (1 << PB0)
		#elif ASB_INTERFACE_CAN0_SS == PORTB_PIN2
			#define ASB_INTERFACE_CAN0_SSPORT							0x02
			#define ASB_INTERFACE_CAN0_SSPIN							0x02
			#define ASB_INTERFACE_CAN0_SS_INIT							DDRB |= (1 << DDB2)
			#define ASB_INTERFACE_CAN0_SS_LOW							PORTB &= ~(1 << PB2)
			#define ASB_INTERFACE_CAN0_SS_HIGH							PORTB |= (1 << PB2)
		#elif ASB_INTERFACE_CAN0_SS == PORTB_PIN4
			#define ASB_INTERFACE_CAN0_SSPORT							0x02
			#define ASB_INTERFACE_CAN0_SSPIN							0x04
			#define ASB_INTERFACE_CAN0_SS_INIT							DDRB |= (1 << DDB4)
			#define ASB_INTERFACE_CAN0_SS_LOW							PORTB &= ~(1 << PB4)
			#define ASB_INTERFACE_CAN0_SS_HIGH							PORTB |= (1 << PB4)
		#else
			#error "inf_can.def.h -> ASB_INTERFACE_CAN0_SS"
		#endif

		#if ASB_INTERFACE_CAN0_RS == NONE
			#define ASB_INTERFACE_CAN0_RSPORT							0x00
			#define ASB_INTERFACE_CAN0_RSPIN							0x00
		#elif ASB_INTERFACE_CAN0_RS == PORTC_PIN2
			#define ASB_INTERFACE_CAN0_RSPORT							0x03
			#define ASB_INTERFACE_CAN0_RSPIN							0x02
			#define ASB_INTERFACE_CAN0_RS_INIT						DDRC |= (1 << DDC2)
			#define ASB_INTERFACE_CAN0_RS_LOW							PORTC &= ~(1 << PC2)
			#define ASB_INTERFACE_CAN0_RS_HIGH						PORTC |= (1 << PC2)
		#elif ASB_INTERFACE_CAN0_RS == MCP2515_RX0BF
			#define ASB_INTERFACE_CAN0_RSPORT							0xFF
			#define ASB_INTERFACE_CAN0_RSPIN							0x02
		#elif ASB_INTERFACE_CAN0_RS == MCP2515_RX1BF
			#define ASB_INTERFACE_CAN0_RSPORT							0xFF
			#define ASB_INTERFACE_CAN0_RSPIN							0x02
		#else
			#error "inf_can.def.h -> ASB_INTERFACE_CAN0_RS"
		#endif

		#if ASB_INTERFACE_CAN0_INT == INTERRUPT0
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT1
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT2
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT3
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT4
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT5
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT6
		#elif ASB_INTERFACE_CAN0_INT == INTERRUPT7
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN0_INT"
		#endif
	#endif /* ASB_INTERFACE_CAN0 */

	#if defined(ASB_INTERFACE_CAN1)
		#if ASB_INTERFACE_CAN1_CLOCK == 2000000 & ASB_INTERFACE_CAN1_SPEED == 50000
		#define ASB_INTERFACE_CAN1_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN1_CNF1							0x00
		#define ASB_INTERFACE_CAN1_CNF2							0xB6
		#define ASB_INTERFACE_CAN1_CNF3							0x04
		#elif ASB_INTERFACE_CAN1_CLOCK == 4000000 & ASB_INTERFACE_CAN1_SPEED == 50000
		#define ASB_INTERFACE_CAN1_SPICFG							0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN1_CNF1							0x01
		#define ASB_INTERFACE_CAN1_CNF2							0xB6
		#define ASB_INTERFACE_CAN1_CNF3							0x04
		#elif ASB_INTERFACE_CAN1_CLOCK == 8000000 & ASB_INTERFACE_CAN1_SPEED == 50000
		#define ASB_INTERFACE_CAN1_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN1_CNF1							0x03
		#define ASB_INTERFACE_CAN1_CNF2							0xB6
		#define ASB_INTERFACE_CAN1_CNF3							0x04
		#elif ASB_INTERFACE_CAN1_CLOCK == 4000000 & ASB_INTERFACE_CAN1_SPEED == 125000
		#define ASB_INTERFACE_CAN1_SPICFG						0x03
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN1_CNF1							0x00
		#define ASB_INTERFACE_CAN1_CNF2							0xAC
		#define ASB_INTERFACE_CAN1_CNF3							0x03
		#elif INF_CAN_CLOCK == 8000000 & INF_CAN_SPEED == 125000
		#define ASB_INTERFACE_CAN1_SPICFG						0x03
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN1_CNF1							0x01
		#define ASB_INTERFACE_CAN1_CNF2							0xAC
		#define ASB_INTERFACE_CAN1_CNF3							0x03
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN1_CLOCK | ASB_INTERFACE_CAN1_SPEED"
		#endif

		#if ASB_INTERFACE_CAN1_SS == PORTB_PIN2
		#define ASB_INTERFACE_CAN1_SSPORT						0x02
		#define ASB_INTERFACE_CAN1_SSPIN						0x02
		#define ASB_INTERFACE_CAN1_SS_INIT						DDRB |= (1 << DDB2)
		#define ASB_INTERFACE_CAN1_SS_LOW						PORTB &= ~(1 << PB2)
		#define ASB_INTERFACE_CAN1_SS_HIGH						PORTB |= (1 << PB2)
		#elif ASB_INTERFACE_CAN1_SS == PORTB_PIN4
		#define ASB_INTERFACE_CAN1_SSPORT						0x02
		#define ASB_INTERFACE_CAN1_SSPIN						0x04
		#define ASB_INTERFACE_CAN1_SS_INIT						DDRB |= (1 << DDB4)
		#define ASB_INTERFACE_CAN1_SS_LOW						PORTB &= ~(1 << PB4)
		#define ASB_INTERFACE_CAN1_SS_HIGH						PORTB |= (1 << PB4)
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN1_SS"
		#endif

		#if ASB_INTERFACE_CAN1_RS == NONE
		#define ASB_INTERFACE_CAN1_RSPORT						0x00
		#define ASB_INTERFACE_CAN1_RSPIN						0x00
		#elif ASB_INTERFACE_CAN1_RS == PORTC_PIN2
		#define ASB_INTERFACE_CAN1_RSPORT						0x03
		#define ASB_INTERFACE_CAN1_RSPIN						0x02
		#define ASB_INTERFACE_CAN1_RS_INIT						DDRC |= (1 << DDC2)
		#define ASB_INTERFACE_CAN1_RS_LOW						PORTC &= ~(1 << PC2)
		#define ASB_INTERFACE_CAN1_RS_HIGH						PORTC |= (1 << PC2)
		#elif ASB_INTERFACE_CAN1_RS == MCP2515_RX0BF
		#define ASB_INTERFACE_CAN1_RSPORT						0xFF
		#define ASB_INTERFACE_CAN1_RSPIN						0x02
		#elif ASB_INTERFACE_CAN1_RS == MCP2515_RX1BF
		#define ASB_INTERFACE_CAN1_RSPORT						0xFF
		#define ASB_INTERFACE_CAN1_RSPIN						0x02
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN1_RS"
		#endif

		#if ASB_INTERFACE_CAN1_INT == INTERRUPT0
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT1
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT2
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT3
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT4
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT5
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT6
		#elif ASB_INTERFACE_CAN1_INT == INTERRUPT7
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN1_INT"
		#endif
	#endif /* ASB_INTERFACE_CAN1 */

	#if defined(ASB_INTERFACE_CAN2)
		#if ASB_INTERFACE_CAN2_CLOCK == 2000000 & ASB_INTERFACE_CAN2_SPEED == 50000
		#define ASB_INTERFACE_CAN2_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN2_CNF1							0x00
		#define ASB_INTERFACE_CAN2_CNF2							0xB6
		#define ASB_INTERFACE_CAN2_CNF3							0x04
		#elif ASB_INTERFACE_CAN2_CLOCK == 4000000 & ASB_INTERFACE_CAN2_SPEED == 50000
		#define ASB_INTERFACE_CAN2_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN2_CNF1							0x01
		#define ASB_INTERFACE_CAN2_CNF2							0xB6
		#define ASB_INTERFACE_CAN2_CNF3							0x04
		#elif ASB_INTERFACE_CAN2_CLOCK == 8000000 & ASB_INTERFACE_CAN2_SPEED == 50000
		#define ASB_INTERFACE_CAN2_SPICFG						0x03
		// T1 15, T2 5 BTQ 20 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN2_CNF1							0x03
		#define ASB_INTERFACE_CAN2_CNF2							0xB6
		#define ASB_INTERFACE_CAN2_CNF3							0x04
		#elif ASB_INTERFACE_CAN2_CLOCK == 4000000 & ASB_INTERFACE_CAN2_SPEED == 125000
		#define ASB_INTERFACE_CAN2_SPICFG						0x03
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN2_CNF1							0x00
		#define ASB_INTERFACE_CAN2_CNF2							0xAC
		#define ASB_INTERFACE_CAN2_CNF3							0x03
		#elif INF_CAN_CLOCK == 8000000 & INF_CAN_SPEED == 125000
		#define ASB_INTERFACE_CAN2_SPICFG						0x03
		// T1 12, T2 4 BTQ 16 SP% 75 SJW 1 Err% 0
		#define ASB_INTERFACE_CAN2_CNF1							0x01
		#define ASB_INTERFACE_CAN2_CNF2							0xAC
		#define ASB_INTERFACE_CAN2_CNF3							0x03
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN2_CLOCK | ASB_INTERFACE_CAN2_SPEED"
		#endif

		#if ASB_INTERFACE_CAN2_SS == PORTB_PIN2
		#define ASB_INTERFACE_CAN2_SSPORT						0x02
		#define ASB_INTERFACE_CAN2_SSPIN						0x02
		#define ASB_INTERFACE_CAN2_SS_INIT						DDRB |= (1 << DDB2)
		#define ASB_INTERFACE_CAN2_SS_LOW						PORTB &= ~(1 << PB2)
		#define ASB_INTERFACE_CAN2_SS_HIGH						PORTB |= (1 << PB2)
		#elif ASB_INTERFACE_CAN2_SS == PORTB_PIN4
		#define ASB_INTERFACE_CAN2_SSPORT						0x02
		#define ASB_INTERFACE_CAN2_SSPIN						0x04
		#define ASB_INTERFACE_CAN2_SS_INIT						DDRB |= (1 << DDB4)
		#define ASB_INTERFACE_CAN2_SS_LOW						PORTB &= ~(1 << PB4)
		#define ASB_INTERFACE_CAN2_SS_HIGH						PORTB |= (1 << PB4)
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN2_SS"
		#endif

		#if ASB_INTERFACE_CAN2_RS == NONE
		#define ASB_INTERFACE_CAN2_RSPORT						0x00
		#define ASB_INTERFACE_CAN2_RSPIN						0x00
		#elif ASB_INTERFACE_CAN2_RS == PORTC_PIN2
		#define ASB_INTERFACE_CAN2_RSPORT						0x03
		#define ASB_INTERFACE_CAN2_RSPIN						0x02
		#define ASB_INTERFACE_CAN2_RS_INIT						DDRC |= (1 << DDC2)
		#define ASB_INTERFACE_CAN2_RS_LOW						PORTC &= ~(1 << PC2)
		#define ASB_INTERFACE_CAN2_RS_HIGH						PORTC |= (1 << PC2)
		#elif ASB_INTERFACE_CAN2_RS == MCP2515_RX0BF
		#define ASB_INTERFACE_CAN2_RSPORT						0xFF
		#define ASB_INTERFACE_CAN2_RSPIN						0x02
		#elif ASB_INTERFACE_CAN2_RS == MCP2515_RX1BF
		#define ASB_INTERFACE_CAN2_RSPORT						0xFF
		#define ASB_INTERFACE_CAN2_RSPIN						0x02
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN2_RS"
		#endif

		#if ASB_INTERFACE_CAN2_INT == INTERRUPT0
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT1
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT2
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT3
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT4
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT5
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT6
		#elif ASB_INTERFACE_CAN2_INT == INTERRUPT7
		#else
		#error "inf_can.def.h -> ASB_INTERFACE_CAN2_INT"
		#endif
	#endif /* ASB_INTERFACE_CAN2 */
#endif /* INF_CAN_DEF_H_ */

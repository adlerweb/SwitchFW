/*
 * asb_eep_def.h
 
 *
 * This file includes the aSysBus EEPROM-Addresses.
 *
 * @author              Patrick Amrhein <trick-at-isysbus-dot-org> 01.05.2010
 * @author				Florian Knodt <adlerweb-at-adlerweb-dot-info> 22.10.2012
 *
 * @note
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version. \n
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details. \n
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http:*www.gnu.org/licenses. \n
 */

#ifndef ASB_EEP_DEF_H_
	#define ASB_EEP_DEF_H_
	
	/*#define EEP__ASB_HARDWARE_CODE_0				0x0000
	#define EEP__ASB_HARDWARE_CODE_1				0x0001
	#define EEP__ASB_HARDWARE_CODE_2				0x0002
	#define EEP__ASB_HARDWARE_CODE_3				0x0003

	#define EEP__ASB_NODE_SERIAL_NUMBER_0			0x0004
	#define EEP__ASB_NODE_SERIAL_NUMBER_1			0x0005
	#define EEP__ASB_NODE_SERIAL_NUMBER_2			0x0006
	#define EEP__ASB_NODE_SERIAL_NUMBER_3			0x0007
*/
	#define EEP__ASB_NODE_ID_0						0x0000
	#define EEP__ASB_NODE_ID_1						0x0001
	
	#define EEP__ASB_INCFG							0x0002
	
	#define EEP__ASB_OUTCFG							0x0003 //bis 0x0006
	
	#define EEP__ASB_FIRST_GRPDEF					0x0010
/*
	#define EEP__ASB_CRC_0							0x000A
	#define EEP__ASB_CRC_1							0x000B
*/
#endif /* ASB_EEP_DEF_H_ */

/*
 * asb_def.h
 *
 * This file includes aSysBus core defines.
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
#ifndef ISB_DEF_H_
#define ISB_DEF_H_

#define USART0									1
#define CAN0									2

#define ERROR__CONFIG_CODE						1

#define ISB_MSG_FLAGS_TOF_MASK					0x30

#define ISB_MSG_FLAGS_TOF_UNICAST				0x00
//	#define ISB_MSG_FLAGS_TOF_RESERVED				0x10
#define ISB_MSG_FLAGS_TOF_MULTICAST				0x20
//	#define ISB_MSG_FLAGS_TOF_BROADCAST				0x30

#define ISB_MSG_FLAGS_RTR_MASK					0x40

#define ISB_MSG_FLAGS_RTR						0x40

#define ISB_MSG_FLAGS_DLC_MASK					0x0F

#define ISB_MSG_FLAGS_DLC_0						0
#define ISB_MSG_FLAGS_DLC_1						1
#define ISB_MSG_FLAGS_DLC_2						2
#define ISB_MSG_FLAGS_DLC_3						3
#define ISB_MSG_FLAGS_DLC_4						4
#define ISB_MSG_FLAGS_DLC_5						5
#define ISB_MSG_FLAGS_DLC_6						6
#define ISB_MSG_FLAGS_DLC_7						7
#define ISB_MSG_FLAGS_DLC_8						8

#define ISB_MSG_UNICAST_NODEID_MASK				0x07FF

#define ISB_MSG_UNICAST_PORT_MASK				0xF800

#define ISB_MSG_UNICAST_PORT_CONFIG				0x0000

#define ISB_MSG_MULTICAST_GROUPID_BL_START		0xF001
#define ISB_MSG_MULTICAST_GROUPID_FW_START		0xF002

#define ISB_MSG_CTRL_CMD_MASK					0x03

#define ISB_MSG_CTRL_CMD_READ					0x00
#define ISB_MSG_CTRL_CMD_ANSWER					0x01
#define ISB_MSG_CTRL_CMD_WRITE					0x02

#define ISB_MSG_TOP_1BIT						0x01
#define ISB_MSG_TOP_4BIT						0x02
#define ISB_MSG_TOP_8BIT						0x03
//	#define ISB_MSG_TOP_							0x04
//	#define ISB_MSG_TOP_							0x05
//	#define ISB_MSG_TOP_							0x06
#define ISB_MSG_TOP_FLOAT						0x07

#define ISB_MSG_TOP__SERIAL_NUMBER__MODE__RESETSOURCE_ERROR	0x20
#define ISB_MSG_TOP__SERIAL_NUMBER__MODE__ERROR			0x21

#define ASB_MSG_TOP_SET_NODEID                  0x50
#define ASB_MSG_TOP_1BIT						0x51
#define ASB_MSG_TOP_DIMMER						0x52

#define ASB_MSG_TOP_PING						0x70
#define ASB_MSG_TOP_PONG						0x71
#define ASB_MSG_TOP_CFG_READ					0x72
#define ASB_MSG_TOP_CFG_WRITE					0x73

#define ISB_MSG_TOP_1BIT_TOV_BOOL			0x01
#define ISB_MSG_TOP_1BIT_TOV_SWITCH			0x02

//	#define ISB_MSG_TOP_FLOAT_TOV_TEMP			0x01

#define ISB_NODE_OPERATING_MODE__MASK					0x0F

#define ISB_NODE_OPERATING_MODE__BL_NORM				0x00
#define ISB_NODE_OPERATING_MODE__BL_FLASH				0x01
#define ISB_NODE_OPERATING_MODE__FW_NORM				0x08
#define ISB_NODE_OPERATING_MODE__FW_CFG					0x09

#define ASB_TRIGGER_INAKTIV 0x00
#define ASB_TRIGGER_DOWN    0x01
#define ASB_TRIGGER_UP      0x02
#define ASB_TRIGGER_BOTH    0x03

#define ASB_MSG_OFF			0x00
#define ASB_MSG_ON			0x01
#define ASB_MSG_TOGGLE		0x02

#define ASB_GRPCFG_TRIGGER  0b11000000
#define ASB_GRPCFG_IO		0b00100000
#define ASB_GRPCFG_CHAN     0b00011100
#define ASB_GRPCFG_MSG      0b00000011

#endif /* ISB_DEF_H_ */

/*
#ifndef ASB_DEF_H_
	#define ASB_DEF_H_

	#define USART0									1
	#define CAN0                                    2

	#define ERROR__CONFIG_CODE                      1

	#define ASB_MSG_FLAGS_TOF_MASK                  0x30

	#define ASB_MSG_FLAGS_TOF_UNICAST               0x00
	//      #define ASB_MSG_FLAGS_TOF_RESERVED      0x10
	#define ASB_MSG_FLAGS_TOF_MULTICAST             0x20
	//      #define ASB_MSG_FLAGS_TOF_BROADCAST     0x30

	#define ASB_MSG_FLAGS_RTR_MASK                  0x40

	#define ASB_MSG_FLAGS_RTR                       0x40

	#define ASB_MSG_FLAGS_DLC_MASK                  0x0F

	#define ASB_MSG_FLAGS_DLC_0                     0
	#define ASB_MSG_FLAGS_DLC_1                     1
	#define ASB_MSG_FLAGS_DLC_2                     2
	#define ASB_MSG_FLAGS_DLC_3                     3
	#define ASB_MSG_FLAGS_DLC_4                     4
	#define ASB_MSG_FLAGS_DLC_5                     5
	#define ASB_MSG_FLAGS_DLC_6                     6
	#define ASB_MSG_FLAGS_DLC_7                     7
	#define ASB_MSG_FLAGS_DLC_8                     8

	#define ASB_MSG_UNICAST_NODEID_MASK             0x07FF

	#define ASB_MSG_UNICAST_PORT_MASK               0xF800

	#define ASB_MSG_UNICAST_PORT_CONFIG             0x0000

	#define ASB_MSG_MULTICAST_GROUPID_BL_START      0xF001
	#define ASB_MSG_MULTICAST_GROUPID_FW_START      0xF002

	#define ASB_MSG_MULTICAST_GROUPID_SETNODEID     0xF011

	#define ASB_MSG_CTRL_CMD_MASK                   0x03

	#define ASB_MSG_CTRL_CMD_READ                   0x00
	#define ASB_MSG_CTRL_CMD_ANSWER                 0x01
	#define ASB_MSG_CTRL_CMD_WRITE                  0x02

	#define ASB_MSG_TOP_1BIT                        0x01
	#define ASB_MSG_TOP_FLOAT                       0x05
	#define ASB_MSG_TOP_TIME                        0x06
	#define ASB_MSG_TOP_DATE                        0x07

	#define ASB_MSG_TOP__SERIAL_NUMBER__MODE__RESETSOURCE_ERROR     0x20
	#define ASB_MSG_TOP__SERIAL_NUMBER__MODE__ERROR                 0x21
	#define ASB_MSG_TOP__SERIAL_NUMBER__NODEID                      0x22

	#define ASB_MSG_TOP_4BIT                        0x02
	#define ASB_MSG_TOP_8BIT                        0x03

	//      #define ASB_MSG_TOP_U8BIT               0x0A
	//      #define ASB_MSG_TOP_U16BIT              0x0B
	//      #define ASB_MSG_TOP_U32BIT              0x0C
	//      #define ASB_MSG_TOP_S8BIT               0x0D
	//      #define ASB_MSG_TOP_S16BIT              0x0E
	//      #define ASB_MSG_TOP_S32BIT              0x0F

	#define ASB_MSG_TOP_1BIT_TOV_BOOL               0x01
	#define ASB_MSG_TOP_1BIT_TOV_SWITCH             0x02

	//      #define ASB_MSG_TOP_FLOAT_TOV_TEMP      0x01

	#define ASB_NODE_OPERATING_MODE__MASK           0x0F

	#define ASB_NODE_OPERATING_MODE__BL_NORM        0x00
	#define ASB_NODE_OPERATING_MODE__BL_FLASH       0x01
	#define ASB_NODE_OPERATING_MODE__FW_NORM        0x08
	#define ASB_NODE_OPERATING_MODE__FW_CFG         0x09
	
	
	typedef struct Asb_Msg_t Asb_Msg_t;
	struct Asb_Msg_t
	{
		uint8_t Flags;
		uint16_t DestId;
		uint16_t SourceId;
		uint8_t Data[8];
	};
	
		#define ASB_CONFIG_CMD_MASK						0x3F

		#define ASB_CONFIG_CMD_NONE						0x00
		#define ASB_CONFIG_CMD_SETNODEID				0x01
		#define ASB_CONFIG_CMD_SETMODE					0x02
		#define ASB_CONFIG_CMD_SETCRC					0x03
		#define ASB_CONFIG_CMD_SETPAGE					0x04
		#define ASB_CONFIG_CMD_WRITEFLASH				0x05
		#define ASB_CONFIG_CMD_INITEEPROM				0x06
		#define ASB_CONFIG_CMD_READEEPROMBLOCK			0x07
		#define ASB_CONFIG_CMD_WRITEEEPROMBLOCK			0x08
		#define ASB_CONFIG_CMD_RESETERRORMEMORY			0x09



		#define ASB_CONFIG_ANSWER_MASK					0xC0

		#define ASB_CONFIG_ANSWER_NONE					0x00
		#define ASB_CONFIG_ANSWER_NACK					0x40
		#define ASB_CONFIG_ANSWER_NOT_ALLOWED			0x80
		#define ASB_CONFIG_ANSWER_ACK					0xC0

#endif ASB_DEF_H_ */
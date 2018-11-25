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

	 	#if defined(ASB_INTERFACE_CAN0_TX) || defined(ASB_INTERFACE_CAN0_RX) || defined(ASB_INTERFACE_CAN1_TX) || defined(ASB_INTERFACE_CAN1_RX) || defined(ASB_INTERFACE_CAN2_TX) || defined(ASB_INTERFACE_CAN2_RX)
	 	uint8_t Inf_Can_Init(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aSpiCfg, const uint8_t aCnf1, const uint8_t aCnf2, const uint8_t aCnf3, const uint8_t aRSPort, const uint8_t aRSPin, const uint8_t aMode) {
		 	//portout(8);
			 Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
			 //portout(9);
		 	Inf_Spi_Init(aSpiCfg);
			 //portout(10);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
			 //portout(11);
		 	Inf_Spi_TxRx(LIB_MCP2515_RESET);
			 //portout(12);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
			 //portout(13);
		 	_delay_ms(2);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_CNF1, aCnf1);
			 //portout(14);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_CNF2, aCnf2);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_CNF3, aCnf3);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_RXB0CTRL, 0x64);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_RXB1CTRL, 0x60);
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_CANINTE, 0x03);
			 //portout(15);
		 	if (aRSPort != 0) {
			 	if (aRSPort < 8) {
				 	Lib_Pin_Set(aRSPort, aRSPin, LIB_PIN_OUTPUT_LOW);
			 	}
			 	//				else if (aRSPort < 16) {
				 	//					Lib_Pin_Set(aRSPort, aRSPin, LIB_PIN_OUTPUT_HIGH);
			 	//				}
			 	else if (aRSPort == 0xFC) {
				 	Lib_Mcp2515_Modify(aSSPort, aSSPin, LIB_MCP2515_BFPCTRL, 0x14, 0x04);
			 	}
			 	else if (aRSPort == 0xFD) {
				 	Lib_Mcp2515_Modify(aSSPort, aSSPin, LIB_MCP2515_BFPCTRL, 0x28, 0x08);
			 	}
			 	//				else if (aRSPort == 0xFE) {
				 	//					Lib_Mcp2515_Modify(aSSPort, aSSPin, LIB_MCP2515_BFPCTRL, 0x14, 0x14);
			 	//				}
			 	//				else if (aRSPort == 0xFF) {
				 	//					Lib_Mcp2515_Modify(aSSPort, aSSPin, LIB_MCP2515_BFPCTRL, 0x28, 0x28);
			 	//				}
		 	}
		 	Lib_Mcp2515_Write(aSSPort, aSSPin, LIB_MCP2515_BFPCTRL, 0x0C);
		 	Lib_Mcp2515_Modify(aSSPort, aSSPin, LIB_MCP2515_CANCTRL, 0xE0, aMode);
		 	if (((Lib_Mcp2515_Read(aSSPort, aSSPin, LIB_MCP2515_CANCTRL)) & 0xE0) == aMode) {
			 	return true;
		 	}
		 	return false;
	 	}
	 	#endif /* ASB_INTERFACE_CAN0_TX || ASB_INTERFACE_CAN0_RX || ASB_INTERFACE_CAN1_TX || ASB_INTERFACE_CAN1_RX || ASB_INTERFACE_CAN2_TX || ASB_INTERFACE_CAN2_RX */



	 	#if defined(ASB_INTERFACE_CAN0_RX) || defined(ASB_INTERFACE_CAN1_RX) || defined(ASB_INTERFACE_CAN2_RX)
	 	uint8_t Inf_Can_Rx(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aSpiCfg, const uint8_t aRSPort, const uint8_t aRSPin, Inf_Can_Msg_t * aInf_Can_Msg) {
		 	uint8_t State = 0;
		 	uint8_t CmdSave = 0;
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
		 	Inf_Spi_Init(aSpiCfg);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
		 	Inf_Spi_Tx(LIB_MCP2515_RX_STATUS);
		 	State = Inf_Spi_TxRx(0xFF);
		 	Inf_Spi_TxRx(0xFF);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
		 	if (bit_is_set(State, LIB_MCP2515_RX_STATUS_INSTRUCTION_CANINTF_RX0IF)) {
			 	CmdSave = LIB_MCP2515_READ_RX_BUFFER0;
		 	}
		 	else if (bit_is_set(State, LIB_MCP2515_RX_STATUS_INSTRUCTION_CANINTF_RX1IF)) {
			 	CmdSave = LIB_MCP2515_READ_RX_BUFFER1;
		 	}
		 	else {
			 	return false;
		 	}
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
		 	Inf_Spi_Tx(CmdSave);
		 	aInf_Can_Msg->SIdH = Inf_Spi_TxRx(0x00);
		 	aInf_Can_Msg->SIdL = Inf_Spi_TxRx(0x00);
		 	aInf_Can_Msg->EIdH = Inf_Spi_TxRx(0x00);
		 	aInf_Can_Msg->EIdL = Inf_Spi_TxRx(0x00);
		 	aInf_Can_Msg->Dlc = Inf_Spi_TxRx(0x00);
		 	if (bit_is_clear(aInf_Can_Msg->Dlc, 6)) {
			 	for (uint8_t i = 0; i < aInf_Can_Msg->Dlc; i++) {
				 	aInf_Can_Msg->Data[i] = Inf_Spi_TxRx(0x00);
			 	}
		 	}
		 	else {
			 	for (uint8_t i = 0; i < 8; i++) {
				 	aInf_Can_Msg->Data[i] = 0x00;
			 	}
		 	}
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
		 	return true;
	 	}
	 	#endif /* ASB_INTERFACE_CAN0_RX || ASB_INTERFACE_CAN1_RX || ASB_INTERFACE_CAN2_RX */



	 	#if defined(ASB_INTERFACE_CAN0_TX) || defined(ASB_INTERFACE_CAN1_TX) || defined(ASB_INTERFACE_CAN2_TX)
	 	uint8_t Inf_Can_Tx(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aSpiCfg, const uint8_t aRSPort, const uint8_t aRSPin, Inf_Can_Msg_t * aInf_Can_Msg) {
		 	uint8_t State = 0;
		 	uint8_t CmdLoad = 0;
		 	uint8_t CmdSend = 0;
			////portout(8);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
		    ////portout(9);
		 	Inf_Spi_Init(aSpiCfg);
		 	////portout(10);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
		 	////portout(11);
		 	Inf_Spi_Tx(LIB_MCP2515_READ_STATUS);
		 	////portout(12);
		 	State = Inf_Spi_TxRx(0xFF);
		 	////portout(13);
		 	Inf_Spi_TxRx(0xFF);
		 	////portout(14);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
			////portout(15);
		 	if (bit_is_clear(State, LIB_MCP2515_READ_STATUS_TXB0CTRL_TXREQ)) {
				////portout(16);
			 	CmdLoad = LIB_MCP2515_LOAD_TX_BUFFER0;
			 	CmdSend = LIB_MCP2515_RTS_TX0;
		 	}
		 	else if (bit_is_clear(State, LIB_MCP2515_READ_STATUS_TXB1CTRL_TXREQ)) {
				////portout(17);
			 	CmdLoad = LIB_MCP2515_LOAD_TX_BUFFER1;
			 	CmdSend = LIB_MCP2515_RTS_TX1;
		 	}
		 	else if (bit_is_clear(State, LIB_MCP2515_READ_STATUS_TXB2CTRL_TXREQ)) {
				////portout(18);
			 	CmdLoad = LIB_MCP2515_LOAD_TX_BUFFER2;
			 	CmdSend = LIB_MCP2515_RTS_TX2;
		 	}
		 	else {
				////portout(19);
			 	return false;
 			}
 			////portout(20);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
			////portout(21);
		 	Inf_Spi_Tx(CmdLoad);
			////portout(22);
		 	Inf_Spi_Tx(aInf_Can_Msg->SIdH);
		 	Inf_Spi_Tx(aInf_Can_Msg->SIdL);
		 	Inf_Spi_Tx(aInf_Can_Msg->EIdH);
		 	Inf_Spi_Tx(aInf_Can_Msg->EIdL);
		 	Inf_Spi_Tx(aInf_Can_Msg->Dlc);
		 	if (bit_is_clear(aInf_Can_Msg->Dlc, 6)) {
			 	for (uint8_t i = 0; i < aInf_Can_Msg->Dlc; i++)
			 	{
				 	Inf_Spi_Tx(aInf_Can_Msg->Data[i]);
			 	}
		 	}
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
		 	asm volatile("nop");
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
		 	Inf_Spi_Tx(CmdSend);
		 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
			////portout(23);
		 	return true;
	 	}
	 	#endif /* ASB_INTERFACE_CAN0_TX || ASB_INTERFACE_CAN1_TX || ASB_INTERFACE_CAN2_TX */
	 	

	 	uint8_t Isb_Inf_Can_Init(const uint8_t aInf) {
		 	uint8_t Result = false;
		 	switch (aInf) {
			 	#if ASB_INTERFACE_CAN0 == 1
			 	case 0:
			 	Result = Inf_Can_Init(ASB_INTERFACE_CAN0_SSPORT, ASB_INTERFACE_CAN0_SSPIN, ASB_INTERFACE_CAN0_SPICFG, ASB_INTERFACE_CAN0_CNF1, ASB_INTERFACE_CAN0_CNF2, ASB_INTERFACE_CAN0_CNF3, ASB_INTERFACE_CAN0_RSPORT, ASB_INTERFACE_CAN0_RSPIN, ASB_INTERFACE_CAN0_MODE);
			 	break;
			 	#endif /* ASB_INTERFACE_CAN0 == 1 */
			 	#if ASB_INTERFACE_CAN1 == 1
			 	case 1:
			 	Result = Inf_Can_Init(ASB_INTERFACE_CAN1_SSPORT, ASB_INTERFACE_CAN1_SSPIN, ASB_INTERFACE_CAN1_SPICFG, ASB_INTERFACE_CAN1_CNF1, ASB_INTERFACE_CAN1_CNF2, ASB_INTERFACE_CAN1_CNF3, ASB_INTERFACE_CAN1_RSPORT, ASB_INTERFACE_CAN1_RSPIN, ASB_INTERFACE_CAN1_MODE);
			 	break;
			 	#endif /* ASB_INTERFACE_CAN1 == 1 */
			 	#if ASB_INTERFACE_CAN2 == 1
			 	case 1:
			 	Result = Inf_Can_Init(ASB_INTERFACE_CAN2_SSPORT, ASB_INTERFACE_CAN2_SSPIN, ASB_INTERFACE_CAN2_SPICFG, ASB_INTERFACE_CAN2_CNF1, ASB_INTERFACE_CAN2_CNF2, ASB_INTERFACE_CAN2_CNF3, ASB_INTERFACE_CAN2_RSPORT, ASB_INTERFACE_CAN2_RSPIN, ASB_INTERFACE_CAN2_MODE);
			 	break;
			 	#endif /* ASB_INTERFACE_CAN2 == 1 */
		 	}
		 	return Result;
	 	}



	 	uint8_t Isb_Inf_Can_Rx(const uint8_t aInf, Isb_Msg_t * aIsb_Msg) {
		 	uint8_t aSSPort;
		 	uint8_t aSSPin;
		 	uint8_t aSpiCfg;
		 	uint8_t aRSPort;
		 	uint8_t aRSPin;
		 	switch (aInf) {
			 	#if ASB_INTERFACE_CAN0 == 1
			 	case 0:
			 	aSSPort = ASB_INTERFACE_CAN0_SSPORT;
			 	aSSPin = ASB_INTERFACE_CAN0_SSPIN;
			 	aSpiCfg = ASB_INTERFACE_CAN0_SPICFG;
			 	aRSPort = ASB_INTERFACE_CAN0_RSPORT;
			 	aRSPin = ASB_INTERFACE_CAN0_RSPIN;
			 	break;
			 	#endif /* ASB_INTERFACE_CAN0 == 1 */
			 	#if ASB_INTERFACE_CAN1 == 1
			 	case 1:
			 	aSSPort = ASB_INTERFACE_CAN1_SSPORT;
			 	aSSPin = ASB_INTERFACE_CAN1_SSPIN;
			 	aSpiCfg = ASB_INTERFACE_CAN1_SPICFG;
			 	aRSPort = ASB_INTERFACE_CAN1_RSPORT;
			 	aRSPin = ASB_INTERFACE_CAN1_RSPIN;
			 	break;
			 	#endif /* ASB_INTERFACE_CAN1 == 1 */
			 	#if ASB_INTERFACE_CAN2 == 1
			 	case 2:
			 	aSSPort = ASB_INTERFACE_CAN2_SSPORT;
			 	aSSPin = ASB_INTERFACE_CAN2_SSPIN;
			 	aSpiCfg = ASB_INTERFACE_CAN2_SPICFG;
			 	aRSPort = ASB_INTERFACE_CAN2_RSPORT;
			 	aRSPin = ASB_INTERFACE_CAN2_RSPIN;
			 	break;
			 	#endif /* ASB_INTERFACE_CAN2 == 1 */
			 	default:
			 	return false;
			 	break;
		 	}
		 	
		 	Inf_Can_Msg_t aCanMsg;

		 	if (Inf_Can_Rx(aSSPort, aSSPin, aSpiCfg, aRSPort, aRSPin, &aCanMsg) == true) {
			 	aIsb_Msg->Flags = ((aCanMsg.SIdH & 0xC0) >> 2) | (aCanMsg.Dlc & ISB_MSG_FLAGS_DLC_MASK);
			 	aIsb_Msg->DestId = (uint16_t)((aCanMsg.EIdH & 0xF8) >> 3) + (uint16_t)((aCanMsg.SIdL & 0x03) << 5) + (uint16_t)((aCanMsg.SIdL & 0xE0) << 2) + (uint16_t)((aCanMsg.SIdH & 0x3F) << 10);
			 	aIsb_Msg->SourceId = (uint16_t)aCanMsg.EIdL + (uint16_t)((aCanMsg.EIdH & 0x07) << 8);
			 	if (bit_is_set(aCanMsg.Dlc, 6)) {
				 	aIsb_Msg->Flags |= 0x40;
			 	}
			 	else {
				 	for (uint8_t i = 0; i < aCanMsg.Dlc; i++) {
					 	aIsb_Msg->Data[i] = aCanMsg.Data[i];
				 	}
			 	}
			 	return true;
		 	}
		 	return false;
	 	}



	 	uint8_t Isb_Inf_Can_Tx(const uint8_t aInf, const Isb_Msg_t * aIsb_Msg) {
		 	uint8_t aSSPort;
		 	uint8_t aSSPin;
		 	uint8_t aSpiCfg;
		 	uint8_t aRSPort;
		 	uint8_t aRSPin;
			 
			 
			 ////portout(6);
		 	switch (aInf) {
			 	case 0:
			 	aSSPort = ASB_INTERFACE_CAN0_SSPORT;
			 	aSSPin = ASB_INTERFACE_CAN0_SSPIN;
			 	aSpiCfg = ASB_INTERFACE_CAN0_SPICFG;
			 	aRSPort = ASB_INTERFACE_CAN0_RSPORT;
			 	aRSPin = ASB_INTERFACE_CAN0_RSPIN;
			 	break;
			 	default:
			 	return false;
			 	break;
		 	}
		 	Inf_Can_Msg_t aCanMsg;
		 	// Write Message to SendBuffer - TXBnSIDH:
		 	//	[7..6] = Type
		 	//	[5..0] = Dest[15..10]
		 	aCanMsg.SIdH = ((aIsb_Msg->Flags << 2) & 0xC0) | (aIsb_Msg->DestId >> 10);
		 	// Write Message to SendBuffer - TXBnSIDL:
		 	//	[7..5] = Dest[9..7]
		 	//	[4] = 0
		 	//	[3] = 1
		 	//	[2] = 0
		 	//	[1..0] = Dest[6..5]
		 	aCanMsg.SIdL = ((uint8_t)(aIsb_Msg->DestId >> 2) & 0xE0) | 0x08 | ((uint8_t)(aIsb_Msg->DestId >> 5) & 0x03);
		 	// Write Message to SendBuffer - TXBnEID8:
		 	//	[7..3] = Dest[4..0]
		 	//	[2..0] = Source[10..8]
		 	aCanMsg.EIdH = ((uint8_t)((aIsb_Msg->DestId << 3) & 0xF8)) | ((uint8_t)((aIsb_Msg->SourceId >> 8) & 0x07));
		 	// Write Message to SendBuffer - TXBnEID0:
		 	//	[7..0] = Source[7..0]
		 	aCanMsg.EIdL = (uint8_t)aIsb_Msg->SourceId;
		 	// Write Message to SendBuffer - DataLength
		 	aCanMsg.Dlc = aIsb_Msg->Flags & ISB_MSG_FLAGS_DLC_MASK;
		 	// RTR
		 	if (bit_is_set(aIsb_Msg->Flags, 6)) {
			 	aCanMsg.Dlc |= 0x40;
		 	}
		 	else {
			 	for (uint8_t i = 0; i < aCanMsg.Dlc; i++) {
				 	aCanMsg.Data[i] = aIsb_Msg->Data[i];
			 	}
		 	}
			 ////portout(7);
		 	if (Inf_Can_Tx(aSSPort, aSSPin, aSpiCfg, aRSPort, aRSPin, &aCanMsg) == true) {
			 	return true;
		 	}
		 	return false;
	 	}
	 	
	 	void Isb_SendMsg(Isb_Msg_t * aMsg) {
		 	Isb_Inf_Can_Tx(0, aMsg);
	 	}

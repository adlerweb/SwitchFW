 	uint8_t Lib_Mcp2515_Read(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aAddr) {
	 	uint8_t aData;
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
	 	Inf_Spi_TxRx(LIB_MCP2515_READ);
	 	Inf_Spi_TxRx(aAddr);
	 	aData = Inf_Spi_TxRx(0xff);
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
	 	return aData;
 	}

 	void Lib_Mcp2515_Write(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aAddr, const uint8_t aData) {
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
	 	Inf_Spi_TxRx(LIB_MCP2515_WRITE);
	 	Inf_Spi_TxRx(aAddr);
	 	Inf_Spi_TxRx(aData);
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
 	}

 	void Lib_Mcp2515_Modify(const uint8_t aSSPort, const uint8_t aSSPin, const uint8_t aAddr, const uint8_t aMask, const uint8_t aData) {
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_LOW);
	 	Inf_Spi_TxRx(LIB_MCP2515_BIT_MODIFY);
	 	Inf_Spi_TxRx(aAddr);
	 	Inf_Spi_TxRx(aMask);
	 	Inf_Spi_TxRx(aData);
	 	Lib_Pin_Set(aSSPort, aSSPin, LIB_PIN_OUTPUT_HIGH);
 	}
 	

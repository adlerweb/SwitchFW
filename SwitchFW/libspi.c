 	void Inf_Spi_Init(const unsigned char aCfg)
 	{

	 	if (bit_is_set(aCfg, SPE))
	 	{
		 	if (bit_is_set(aCfg, MSTR))
		 	{
			 	INF_SPI_DDR |= (1 << INF_SPI_DD_MOSI) | (1 << INF_SPI_DD_SCK);
			 	INF_SPI_DDR &= ~(1 << INF_SPI_DD_MISO);
		 	}
		 	else
		 	{
			 	INF_SPI_DDR |= (1 << INF_SPI_DD_MISO);
			 	INF_SPI_DDR &= ~(1 << INF_SPI_DD_MOSI) & ~(1 << INF_SPI_DD_SCK);
		 	}
	 	}
	 	else
	 	{
		 	INF_SPI_DDR &= ~(1 << INF_SPI_DD_MISO) & ~(1 << INF_SPI_DD_MOSI) & ~(1 << INF_SPI_DD_SCK);
	 	}

	 	SPCR = aCfg;
	 	//SPSR = 0;
		SPSR = ~(1 << SPI2X);

 	}



 	unsigned char Inf_Spi_Rx(void)
 	{

	 	SPDR = 0;
	 	loop_until_bit_is_set(SPSR, SPIF);
	 	return SPDR;

 	}
 	


 	void Inf_Spi_Tx(const unsigned char Data)
 	{

	 	SPDR = Data;
	 	loop_until_bit_is_set(SPSR, SPIF);

 	}



 	unsigned char Inf_Spi_TxRx(const unsigned char Data)
 	{

	 	SPDR = Data;
	 	loop_until_bit_is_set(SPSR, SPIF);
	 	return SPDR;

 	}

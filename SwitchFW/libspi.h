	#if defined(__AVR_ATmega8__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB5
	#define INF_SPI_DD_MISO							PB4
	#define INF_SPI_DD_MOSI							PB3
	#define INF_SPI_DD_SS							PB2
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB5
	#define IF_SPI_PIN_MISO							PB4
	#define IF_SPI_PIN_MOSI							PB3
	#define IF_SPI_PIN_SS							PB2
	#elif defined(__AVR_ATmega16__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB7
	#define INF_SPI_DD_MISO							PB6
	#define INF_SPI_DD_MOSI							PB5
	#define INF_SPI_DD_SS							PB4
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB7
	#define IF_SPI_PIN_MISO							PB6
	#define IF_SPI_PIN_MOSI							PB5
	#define IF_SPI_PIN_SS							PB4
	#elif defined(__AVR_ATmega32__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB7
	#define INF_SPI_DD_MISO							PB6
	#define INF_SPI_DD_MOSI							PB5
	#define INF_SPI_DD_SS							PB4
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB7
	#define IF_SPI_PIN_MISO							PB6
	#define IF_SPI_PIN_MOSI							PB5
	#define IF_SPI_PIN_SS							PB4
	#elif defined(__AVR_ATmega64__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB1
	#define INF_SPI_DD_MISO							PB3
	#define INF_SPI_DD_MOSI							PB2
	#define INF_SPI_DD_SS							PB0
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB1
	#define IF_SPI_PIN_MISO							PB3
	#define IF_SPI_PIN_MOSI							PB2
	#define IF_SPI_PIN_SS							PB0
	#elif defined (__AVR_ATmega128__)
	#define INF_SPI_DDR								DRB
	#define INF_SPI_DD_SCK							PB1
	#define INF_SPI_DD_MISO							PB3
	#define INF_SPI_DD_MOSI							PB2
	#define INF_SPI_DD_SS							PB0
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB1
	#define IF_SPI_PIN_MISO							PB3
	#define IF_SPI_PIN_MOSI							PB2
	#define IF_SPI_PIN_SS							PB0
	#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB5
	#define INF_SPI_DD_MISO							PB4
	#define INF_SPI_DD_MOSI							PB3
	#define INF_SPI_DD_SS							PB2
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB5
	#define IF_SPI_PIN_MISO							PB4
	#define IF_SPI_PIN_MOSI							PB3
	#define IF_SPI_PIN_SS							PB2
	#elif defined(__AVR_ATmega169P__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB1
	#define INF_SPI_DD_MISO							PB3
	#define INF_SPI_DD_MOSI							PB2
	#define INF_SPI_DD_SS							PB0
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB1
	#define IF_SPI_PIN_MISO							PB3
	#define IF_SPI_PIN_MOSI							PB2
	#define IF_SPI_PIN_SS							PB0
	#elif defined(__AVR_ATmega644__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB7
	#define INF_SPI_DD_MISO							PB6
	#define INF_SPI_DD_MOSI							PB5
	#define INF_SPI_DD_SS							PB4
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB7
	#define IF_SPI_PIN_MISO							PB6
	#define IF_SPI_PIN_MOSI							PB5
	#define IF_SPI_PIN_SS							PB4
	#elif defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__)
	#define INF_SPI_DDR								DDRB
	#define INF_SPI_DD_SCK							PB1
	#define INF_SPI_DD_MISO							PB3
	#define INF_SPI_DD_MOSI							PB2
	#define INF_SPI_DD_SS							PB0
	#define IF_SPI_PIN								PINB
	#define IF_SPI_PIN_SCK							PB1
	#define IF_SPI_PIN_MISO							PB3
	#define IF_SPI_PIN_MOSI							PB2
	#define IF_SPI_PIN_SS							PB0
	#else
	#error "No definition for this MCU available."
	#endif
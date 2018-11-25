
#define A									0b00001000
#define B									0b00010000
#define C									0b00011000
#define D									0b00100000
#define E									0b00101000
#define F									0b00110000
#define G									0b00111000

#define PULLUP								0b01000000

#define LIB_PIN_OUTPUT_TRISTATE				0x00
#define LIB_PIN_OUTPUT_LOW					0x01
#define LIB_PIN_OUTPUT_HIGH					0x03

#define LIB_PIN_INPUT						0x00
#define LIB_PIN_INPUT_PULLUP				0x02

	#if defined(__AVR_ATmega8__)
	uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega16__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega32__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega48__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega48V__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega64__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_ATmega88__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega88V__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega128__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_ATmega168__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega168V__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &NUL, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &NUL, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &NUL, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_ATmega169P__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_ATmega169PV__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_ATmega644__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &NUL, &NUL, &NUL};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &NUL, &NUL, &NUL};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &NUL, &NUL, &NUL};
	#elif defined(__AVR_AT90CAN32__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_AT90CAN64__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#elif defined(__AVR_AT90CAN128__)
		uint8_t NUL;
		volatile uint8_t* DDRx[] = {&NUL, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG};
		volatile uint8_t* PORTx[] = {&NUL, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};
		volatile uint8_t* PINx[] = {&NUL, &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING};
	#else
		#error "No definition for this MCU available."
	#endif

	uint8_t Lib_Pin_Get(const uint8_t aPort, const uint8_t aPin) {
		return (*(PINx[aPort]) >> aPin) & 1;
	}

	void __attribute__((noinline)) Lib_Pin_Set(const uint8_t aPort, const uint8_t aPin, const uint8_t aCmd) {
		uint8_t mask;
		uint8_t tmp;
		volatile uint8_t *reg;
		uint8_t Pxx = aPin;
		for (mask = 1; Pxx--; mask <<= 1) ;
		reg = PORTx[aPort];
		tmp = *reg | mask;
		if (! (aCmd & 2)) {
			tmp ^= mask;
		}
		*reg = tmp;
		reg = DDRx[aPort];
		tmp = *reg | mask;

		if (! (aCmd & 1)) {
			tmp ^= mask;
		}
		*reg = tmp;
	}

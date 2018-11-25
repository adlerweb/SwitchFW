/* PWM-Tabelle, 32 Stufen */
const uint16_t pwmtable_8D[32] PROGMEM =
{
	0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23,
	27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255
};
volatile uint8_t systick=0;
volatile bool systicktrigger=false;

void pwm_init() {
	TCCR2  = 0b00000100; //Prescaler 64
	TCCR1A = 0b00000001; //PWM (currently) disabled
	TCCR1B = 0b00000011; //Prescaler 64
	
	TIMSK |= (1<<TOIE1); //Overflow interrupt Timer1 (~1ms)
}

ISR(TIMER1_OVF_vect) {
	systick++;
	if(systick % 10 == 0) debounce_int(); 
	if(systick >= 250) { //Alle 256ms
		systicktrigger = true;
		systick=0;
	}
}

// OC2 aka PD7
void pwm_oc2 (uint8_t level)
{
	uint8_t portcfg;
	portcfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_OUTCFG+(((uint8_t)4/2))));
	
	if((4 % 2) == 0) portcfg = portcfg >> 4;
	portcfg = portcfg & 0b00001111;
		
	if(level == 0) {
		TCCR2 &= ~((1<<WGM20) | (1<<COM21) | (1<<COM20)); //Disable PWM
		PORTD &= ~((1 << PD7));
		return;
	}
	if(level >= 32) {
		TCCR2 &= ~((1<<WGM20) | (1<<COM21) | (1<<COM20)); //Disable PWM
		PORTD |= ((1 << PD7));
		return;
	}
	//TCCR2 = 0x64; //PWM, Inverted, Prescaler 64
					//0x01100100
	              //prescaler 64 -> ~122 Hz PWM frequency
	
	TCCR2 |= ((1<<WGM20) | (1<<COM21)); //Enable PWM
	if(portcfg & 0b00001000) {
		TCCR2 |= (1<<COM20);	
	}
	OCR2 = pgm_read_word (& pwmtable_8D[level]);
}

//OC1A aka PD5
void pwm_oc1a (uint8_t level)
{
	uint8_t portcfg;
	portcfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_OUTCFG+(((uint8_t)6/2))));
	
	if((6 % 2) == 0) portcfg = portcfg >> 4;
	portcfg = portcfg & 0b00001111;
	
	if(level == 0) {
		TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));
		PORTD &= ~((1 << PD5));
		return;
	}
	if(level >= 32) {
		TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));
		PORTD |= ((1 << PD5));
		return;
	}
	TCCR1A |= ((1<<COM1A1)); //Enable PWM
	if(portcfg & 0b00001000) {
		TCCR2 |= (1<<COM1A0);
	}
	OCR1AL = pgm_read_word (& pwmtable_8D[level]);
}

//OC1B aka PD4
void pwm_oc1b (uint8_t level)
{
	uint8_t portcfg;
	portcfg=lib_eep_read_byte((uint8_t *)(EEP__ASB_OUTCFG+(((uint8_t)7/2))));
	
	if((7 % 2) == 0) portcfg = portcfg >> 4;
	portcfg = portcfg & 0b00001111;
	
	if(level == 0) {
		TCCR1A &= ~((1<<COM1B1) | (1<<COM1B0));
		PORTD &= ~((1 << PD4));
		return;
	}
	if(level >= 32) {
		TCCR1A &= ~((1<<COM1B1) | (1<<COM1B0));
		PORTD |= ((1 << PD4));
		return;
	}
	TCCR1A |= ((1<<COM1B1)); //Enable PWM
	if(portcfg & 0b00001000) {
		TCCR2 |= (1<<COM1B0);
	}
	OCR1BL = pgm_read_word (& pwmtable_8D[level]);
}

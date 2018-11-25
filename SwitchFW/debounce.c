/************************************************************************/
/*                                                                      */
/*                      Debouncing 8 Keys                               */
/*                      Sampling 4 Times                                */
/*                      With Repeat Function                            */
/*                                                                      */
/*              Author: Peter Dannegger                                 */
/*                      danni@specs.de                                  */
/*                                                                      */
/************************************************************************/

#define KEY_DDR         DDRA
#define KEY_PORT        PORTA
#define KEY_PIN         PINA

#define REPEAT_MASK     (1<<KEY1 | 1<<KEY2)       // repeat: key1, key2
#define REPEAT_START    50                        // after 500ms
#define REPEAT_NEXT     20                        // every 200ms

volatile uint8_t key_state;                                // debounced and inverted key state:
														   // bit = 1: key pressed
//volatile uint8_t key_press;                                // key press detect
//volatile uint8_t key_rpt;                                  // key long press and repeat

void debounce_int(void) {
	//static uint8_t ct0, ct1, rpt;
	static uint8_t ct0, ct1;
	uint8_t i;
	
	i = key_state ^ ~KEY_PIN;                       // key changed ?
	ct0 = ~( ct0 & i );                             // reset or count ct0
	ct1 = ct0 ^ (ct1 & i);                          // reset or count ct1
	i &= ct0 & ct1;                                 // count until roll over ?
	key_state ^= i;                                 // then toggle debounced state
//	key_press |= key_state & i;                     // 0->1: key press detect
//	
//	if( (key_state & REPEAT_MASK) == 0 )            // check repeat function
//	rpt = REPEAT_START;                             // start delay
//	if( --rpt == 0 ){
//		rpt = REPEAT_NEXT;                          // repeat delay
//		key_rpt |= key_state & REPEAT_MASK;
//	}
}
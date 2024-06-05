#ifndef _x86
	#include <avr/io.h>
	#include <util/delay.h>
#endif // _ATMEGA328P

#ifdef _x86
	#include "x86/io.h"
	#include "x86/delay.h"
#endif // _x86

#define ON_DELAY_MS	1000
#define OFF_DELAY_MS	500

int main(void) {

	DDRB |= _BV(DDB5);

	// PD1 TX, PD0 RX

	while(1) {

		PORTB |= _BV(DDB5);

		_delay_ms(ON_DELAY_MS);

		PORTB &= ~_BV(PORTB5);

		_delay_ms(OFF_DELAY_MS);

	}

}

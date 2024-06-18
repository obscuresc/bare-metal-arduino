#ifndef _x86
	#include <avr/io.h>
	#include <util/delay.h>

	#include "spdlog_interface.h"
	// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#endif // _x86

#ifdef	_x86 
	#include <spdlog/spdlog.h>

	#include "x86/io.hpp"
	#include "x86/delay.hpp"

#endif // _x86


#define ON_DELAY_MS	1000
#define OFF_DELAY_MS	500

int main(void) {

	DDRB |= _BV(DDB5);
	DDRD |= _BV(DDB0);

	// PD1 TX, PD0 RX

	while(1) {

		PORTB |= _BV(DDB5);
		PORTD |= _BV(DDB0);

		SPDLOG_INFO("msg");
		_delay_ms(ON_DELAY_MS);

		PORTB &= ~_BV(PORTB5);
		PORTD &= ~_BV(PORTD5);

		SPDLOG_INFO("msg");
		_delay_ms(OFF_DELAY_MS);

	}

}

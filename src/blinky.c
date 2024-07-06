#ifndef _x86
	#include <avr/io.h>
	#include <util/delay.h>

	#include "clock.h"
	#include "usart.h"
	#include "spdlog_interface.h"
	// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#else
	#include <spdlog/spdlog.h>

	#include "usart.h"

	#include "x86/io.hpp"
	#include "x86/delay.hpp"

#endif // _x86


#define ON_DELAY_MS	1000
#define OFF_DELAY_MS	500


int main(void) {
	
//	Clock_Init();
	uint8_t res = USART_Init(USART_MODE_ASYNC, 0, 12, 1, 8, USART_PARITY_NULL, USART_POLARITY_RX_RISE, USART_STOPBITS_ONE);
	(void) res;

	DDRB |= _BV(DDB5);
	DDRD |= _BV(DDB0);

	while(1) {

		PORTB |= _BV(DDB5);
		PORTD |= _BV(DDB0);

		SPDLOG_INFO("A");
		_delay_ms(ON_DELAY_MS);

		PORTB &= ~_BV(PORTB5);
		PORTD &= ~_BV(PORTD5);

		SPDLOG_INFO("B");
		_delay_ms(OFF_DELAY_MS);

	}

}

#include "usart.h"
#include <stdint.h>


uint8_t USART_Init(uint8_t mode, uint8_t multiprocessComMode, uint8_t ubrr, uint8_t doubleSpeedEnable, uint8_t ndatabits, uint8_t parity, uint8_t polarity, uint8_t nstopbits) {

	#ifdef _x86

	(void) mode;
	return 0;

	#else



	if ((mode >= USART_MODE_NOPTIONS) | (mode == USART_MODE_RESERVED)) {
		return 1;
	}

	#warning "Baud rate does not compensate for clock and fuses"
	#warning "No function guard for baud rate setting"

	if ((ndatabits < 5) | (ndatabits > 9)) {
		return 1;
	}

	/* A register, control and status
	 * rx com, tx com
	 * data register empty, frame error, data overrun, parity error
	 * double speed enable
	 * multiprocess comp mode
	 */

	// UCSR0A |= ((doubleSpeedEnable > 0) << 1) | (multiprocessComMode > 0);
	// B register, baud
	// C register, has 5 fields, UMSEL mode, parity mode, stop bit, character size, polairty

	UCSR0C |= (mode << 6);

	// set the baud rate, 9600b based on 1MHz, U2X0 = 1
	#warning "Ubbr setting overriden to produce 9600b at 1MHz, with double speed enabled"
	#define USART0_CLOCK_HZ 1000000
	#define BAUD_RATE_HZ 9600
	#define UBRR_VALUE (USART0_CLOCK_HZ / BAUD_RATE_HZ)
	ubrr = UBRR_VALUE;
	UBRR0H = (uint8_t) ((ubrr >> 8) & 0x0F);
	UBRR0L = (uint8_t) (ubrr & 0xFF);

	// enable the RX and TX
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// set the frame format
	// UCSR0C |= (ndatabits << 1) | (nstopbits << 3) | (parity > 0);
	UCSR0C = (3 << UCSZ00);

	return 0;

	#endif // _x86
}


uint8_t USART_Receive() {

	return 0;
}


uint8_t USART_Transmit(uint8_t data) {

	// wait for empty tx buffer
	while (!(UCSR0A & (1 << UDRE0)));

	// put data into buffer, send the data 
	UDR0 = data;

	return 0;
}

#ifndef _IO_HPP
#define _IO_HPP

#include <cstdlib>
#include <iostream>

extern uint8_t DDRB;
extern uint8_t DDRC;
extern uint8_t DDRD;

extern uint8_t PORTB;
extern uint8_t PORTC;
extern uint8_t PORTD;

extern uint8_t DDB0;
extern uint8_t DDB1;
extern uint8_t DDB2;
extern uint8_t DDB3;
extern uint8_t DDB4;
extern uint8_t DDB5;
extern uint8_t DDB6;
extern uint8_t DDB7;


extern uint8_t PORTB5;

extern uint8_t PORTD5;

extern uint8_t UDR0;

extern uint8_t UCSR0A;
#define MPCM0 0
#define U2X0 1
#define UPE0 2
#define DOR0 3
#define FE0 4
#define UDRE0 5
#define TXC0 6
#define RXC0 7

extern uint8_t UCSR0B;
#define TXB80 0
#define RXB80 1
#define UCSZ02 2
#define TXEN0 3
#define RXEN0 4
#define UDRIE0 5
#define TXCIE0 6
#define RXCIE0 7

extern uint8_t UCSR0C;
#define UCPOL0 0
#define UCSZ00 1
#define UCPHA0 1
#define UCSZ01 2
#define UDORD0 2
#define USBS0 3
#define UPM00 4
#define UPM01 5
#define UMSEL00 6
#define UMSEL01 7

uint8_t _BV(uint8_t shift);

#endif // _IO_HPP

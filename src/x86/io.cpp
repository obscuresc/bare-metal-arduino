#include "io.hpp"

uint8_t DDRB;
uint8_t DDRC;
uint8_t DDRD;

uint8_t PORTB;
uint8_t PORTC;
uint8_t PORTD;

uint8_t DDB0 = 0;
uint8_t DDB1 = 1;
uint8_t DDB2 = 2;
uint8_t DDB3 = 3;
uint8_t DDB4 = 4;
uint8_t DDB5 = 5;
uint8_t DDB6 = 6;
uint8_t DDB7 = 7;


uint8_t PORTB5 = 5;

uint8_t PORTD5 = 5;

uint8_t UDR0;

uint8_t UCSR0A;
uint8_t UCSR0B;
uint8_t UCSR0C;


uint8_t _BV(uint8_t shift) {
	return (1 << shift);
}

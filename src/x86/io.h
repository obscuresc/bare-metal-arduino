#ifndef _IO_H
#define _IO_H

#include <cstdint>
#include <iostream>

uint8_t DDRB;

uint8_t PORTB;

uint8_t DDB5 = 5;
uint8_t PORTB5 = 5;


uint8_t _BV(uint8_t shift) {
	std::cout << "Making bit high" << std::endl;
	return (1 << shift);
}

#endif // _IO_H

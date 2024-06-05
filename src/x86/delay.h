#ifndef _DELAY_H
#define _DELAY_H

#include <chrono>
#include <cstdint>
#include <thread>


void _delay_ms(uint32_t delay) {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

}

#endif // _DELAY_H

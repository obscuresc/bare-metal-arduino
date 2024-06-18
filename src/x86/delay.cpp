#include "delay.hpp"

void _delay_ms(uint32_t delay) {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

}

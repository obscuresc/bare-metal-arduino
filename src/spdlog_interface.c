#include "spdlog_interface.h"
#include "usart.h"
#include <stdint.h>

/*
void SPDLOG_INFO(char* msg) {

	USART_Transmit(uint8_t data);
}
*/


void _SPDLOG_INFO(char* msg, uint8_t len) {

	for(uint8_t i = 0; i < len; i++) {
		USART_Transmit(msg[i]);
	}

}

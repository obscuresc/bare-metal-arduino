#ifndef USART_H
#define USART_H

#include "avr/io.h"
#include <stdint.h>

#define USART_MODE_ASYNC	0
#define USART_MODE_SYNC		1
#define USART_MODE_RESERVED	2
#define USART_MODE_MSPI		3
#define USART_MODE_NOPTIONS	4

#define USART_PARITY_NULL	0
#define USART_PARITY_RESERVED	1
#define USART_PARITY_EVEN	2
#define USART_PARITY_ODD	3
#define USART_PARITY_NOPTIONS	4

#define USART_STOPBITS_ONE	0
#define USART_STOPBITS_TWO	1
#define USART_STOPBITS_NOPTIONS	2

#define USART_POLARITY_TX_RISE	0
#define USART_POLARITY_RX_RISE	1
#define USART_POLARITY_NOPTIONS	2
/*
 *
 *
 * @param ubbr, baud rate setting
 * @param ndatabits, number of databits used on the wire
 */
uint8_t USART_Init(uint8_t mode, uint8_t multiprocessComMode, uint8_t ubrr, uint8_t doubleSpeedEnable, uint8_t ndatabits, uint8_t parity, uint8_t polarity, uint8_t nstopbits);
/*
 * Clock_Read, read a buffer from uart
 *
 * @return received data
 */
uint8_t USART_Receive();

/*
 * Clock_Write, write a buffer over uart
 *
 * @param data, to write
 * @return 0 if tx occurred successfully
 */
uint8_t USART_Transmit(uint8_t data);

#endif // USART_H

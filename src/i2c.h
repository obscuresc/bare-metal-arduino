#ifndef I2C_H
#define I2C_H

#include <stdint.h>

uint8_t I2C_Init();

uint8_t I2C_Transmit();

uint8_t I2C_Receive();

#endif // I2C_H

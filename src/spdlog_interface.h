#ifndef SPDLOG_INTERFACE_H
#define SPDLOG_INTERFACE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SPDLOG_INFO(x)	_SPDLOG_INFO(x, sizeof(x)/sizeof(x[0]))


void _SPDLOG_INFO(char* msg, uint8_t len);


#endif // SPDLOG_INTERFACE_H

/* This file is basically a wrapper for the Arduino Serial library,
which already contains internal circular transmit and receive buffers. */

#ifndef _DISPATCH_UART_H
#define _DISPATCH_UART_H

#include "HardwareSerial.h"
#include "dispatchSerial.h"

void read(uint8_t * data, uint16_t length);
void write(uint8_t * data, uint16_t length);
uint16_t readable();
uint16_t writeable();

#endif

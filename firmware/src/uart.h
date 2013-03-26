/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file uart.h
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

/**
 * @brief init uart interface to 230400, 8, N, 1
 */
void initUart();

/**
 * @brief put data into the tx ringbuffer
 * @param data data to put in the tx buffer
 */
void sendByte(uint8_t const data);

/**
 * @brief put data into the tx ringbuffer
 * @param data pointer to data array to put in the tx buffer
 * @param size number of elements to put into the tx ringbuffer
 */
void sendByteArray(uint8_t *data, uint8_t const size);

/**
 * @brief reads a data byte from the uart
 * @param data pointer where to save the read data
 */
void readByte(uint8_t *data);

/**
 * @brief checks if data for reading is available
 * @return 0 if false, number of bytes otherwise
 */
uint8_t uartDataAvailable();

#endif

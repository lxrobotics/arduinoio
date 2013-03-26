/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file uart.c
 */

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUF_SIZE (256)

static volatile uint8_t rx_rd_ptr = 0, rx_wr_ptr = 0, rx_cnt = 0;
static volatile uint8_t rx_buf[BUF_SIZE];

static volatile uint8_t tx_rd_ptr = 0, tx_wr_ptr = 0, tx_cnt = 0;
static volatile uint8_t tx_buf[BUF_SIZE];

/**
 * @brief init uart interface to 115200, 8, N, 1
 */
void initUart() {
	// baudrate = 230400, error = -3.5 %
	UBRR0 = 8;
	UCSR0A = (1<<U2X0);
	// enable rx complete interrupt and
	// enable reseiver and transmitter
	UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0); 
}

/**
 * @brief put data into the tx ringbuffer
 * @param data data to put in the tx buffer
 */
void sendByte(uint8_t const data) {
	cli();

	if(tx_cnt < BUF_SIZE) { // buffer not full
		tx_buf[tx_wr_ptr] = data;
		tx_wr_ptr = (tx_wr_ptr + 1) & (BUF_SIZE-1);
		tx_cnt++;
		UCSR0B |= (1<<UDRIE0); // activate uart data register empty interrupt
	}

	sei();
}

/**
 * @brief put data into the tx ringbuffer
 * @param data pointer to data array to put in the tx buffer
 * @param size number of elements to put into the tx ringbuffer
 */
void sendByteArray(uint8_t *data, uint8_t const size) {
	for(uint8_t i=0; i<size; i++) {
		sendByte(data[i]);
	}
}

/**
 * @brief reads a data byte from the uart
 * @param data pointer where to save the read data
 */
void readByte(uint8_t *data) {
	cli();

	if(rx_cnt > 0) { // buffer not empty yet
		*data = rx_buf[rx_rd_ptr];
		rx_rd_ptr = (rx_rd_ptr + 1) & (BUF_SIZE-1);
		rx_cnt--;
	}

	sei();
}

/**
 * @brief checks if data for reading is available
 * @return 0 if false, number of bytes otherwise
 */
uint8_t uartDataAvailable() {
	cli();

	uint8_t tmp = rx_cnt;

	sei();

	return tmp;
}

/**
 * @brief uart receive complete ISR
 */
ISR(USART_RX_vect) {
	if(rx_cnt < BUF_SIZE) { // buffer not full
		rx_buf[rx_wr_ptr] = UDR0;
		rx_wr_ptr = (rx_wr_ptr + 1) & (BUF_SIZE-1);
		rx_cnt++;		
	}
}

/**
 * @brief uart data register empty ISR
 */
ISR(USART_UDRE_vect) {
	if(tx_cnt > 0) { // buffer not empty yet
		UDR0 = tx_buf[tx_rd_ptr];
		tx_rd_ptr = (tx_rd_ptr + 1) & (BUF_SIZE-1);
		tx_cnt--;
		if(tx_cnt == 0) UCSR0B &= ~(1<<UDRIE0); // deactivate that interrupt
	}
}

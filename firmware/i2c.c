/* Copyright (c) 2016, Alexander Entinger / LXRobotics
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of motor-controller-highpower-motorshield nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "i2c.h"
#include "hal.h"
#include "project.h"
#include <avr/io.h>

// TWI Bit Rate register settings for 16 MHz
static uint8_t const TWBR_100 = 72;
static uint8_t const TWBR_400 = 12;

// TWI status codes
#define MT_START 			(0x08)
#define MT_REP_START 		(0x10)
#define MT_SLAVE_ACK		(0x18)
#define MR_SLAVE_ACK		(0x40)
#define MT_DATA_ACK			(0x28)

/**
 * @brief transmits a start condition
 * @param adr address to write to/read from
 * @return 0 in case of failure, 1 in case of success
 */
uint8_t i2c_start(uint8_t const adr) {

	// send start condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for the start condition to be transmitted
	while(!(TWCR & (1<<TWINT)));
	// check status register to indicate that start has been successfuly sent
	if(((TWSR & 0xF8) != MT_START) && ((TWSR & 0xF8) != MT_REP_START)) return 0;
	// load address and issue transmission
	TWDR = adr;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for the address to be transmitted and ack was received
	while(!(TWCR & (1<<TWINT)));
	// check status register to indicate that address has ben successfully sent and ack was received
	if(((TWSR & 0xF8) != MT_SLAVE_ACK) && ((TWSR & 0xF8) != MR_SLAVE_ACK)) return 0;

	return 1;
}

/**
 * @brief transmits a stop condition
 */
void i2c_stop() {
	// send stop condition
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	// wait until stop condition is finished
	while(TWCR & (1<<TWSTO));
}

/**
 * @brief writes byte on the i2c bus
 * @param data data to write on the i2c bus
 * @return 1 in case of success, 0 in case of failure
 */ 
uint8_t i2c_writeByte(uint8_t const data) {
	// load data reg and issue transmissiion
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for the data to be transmitted and ack was received
	while(!(TWCR & (1<<TWINT)));
	// check status register to indicate that data has ben successfully sent and ack was received
	if((TWSR & 0xF8) != MT_DATA_ACK) return 0;
	else return 1;
}

/**
 * @brief configures the i2c module
 * @param speed speed of the i2c bus
 */
void configI2C(i2c_speed const speed) {

	// activate pull ups
	set_bit(SDA_PORT, SDA);
	set_bit(SCL_PORT, SCL);

	// set speed of i2c module
	if(speed == S100K) {
		TWBR = TWBR_100;
	}
	else if(speed == S400K) {
		TWBR = TWBR_400;
	}
}

/**
 * @brief writes data on the i2c bus
 * @param adr address to write to
 * @param offset to the register to write to
 * @param data array of data elements to write to slave
 * @param length number of elements to write to slave
 * @return 0 in case of error, 1 in case of success
 */
uint8_t i2c_write(uint8_t const adr, uint8_t const offset, uint8_t *data, uint8_t const length) {

	if(length == 0) return 0;
	
	// issue start condition
	if(!i2c_start(adr)) return 0;

	// write address
	if(!i2c_writeByte(offset)) return 0;

	// write the data
	for(uint8_t i=0; i<length; i++) {
		if(!i2c_writeByte(data[i])) return 0;
	}

	// issue stop condition
	i2c_stop();


	return 1;
}

/**
 * @brief reads data on the i2c bus
 * @param adr address to read from
 * @param offset to the register to read from
 * @param data array of data elements to read from slave
 * @param length number of elements to read from slave
 * @return 0 in case of error, 1 in case of success
 */
uint8_t i2c_read(int8_t const adr, uint8_t const offset, uint8_t *data, uint8_t const length) {

	if(length == 0) return 0;

	// issue start condition
	if(!i2c_start(adr)) return 0;

	// write address
	if(!i2c_writeByte(offset)) return 0;

	// issue repeated start condition
	if(!i2c_start(adr + 0x01)) return 0;
	
	// receive the data bytes
	for(uint8_t i=0; i<length-1; i++) {
		// request more data from i2c device
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		// read data
		data[i] = TWDR;
	}

	// read last byte
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));    
	data[length-1] = TWDR;

	i2c_stop();

	return 1;
}

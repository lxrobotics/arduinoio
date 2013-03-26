/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, BSc
 * @file parser.h
 */

#include <avr/wdt.h>
#include "parser.h"
#include "gpio.h"
#include "analog.h"
#include "uart.h"
#include "temperature.h"
#include "id.h"
#include "i2c.h"
#include "servo.h"
#include "counter.h"

// prototype section
void parse_misc(uint8_t const data);
void parse_gpio(uint8_t const data);
void parse_analog(uint8_t const data);
void parse_i2c(uint8_t const data);
void parse_servo(uint8_t const data);
void parse_counter(uint8_t const data);

// states of the parser
#define S_CLASS_TAG			(0)
#define S_PARSE_MISC		(1)
#define S_PARSE_GPIO		(2)
#define S_PARSE_ANALOG		(3)
#define S_PARSE_I2C			(4)
#define S_PARSE_SERVO		(5)
#define S_PARSE_COUNTER		(6)

#define CT_MISC				(0x01)
#define CT_GPIO 			(0x02)
#define CT_ANALOG			(0x03)
#define CT_I2C				(0x04)
#define CT_SERVO			(0x05)
#define CT_COUNTER			(0x06)

static volatile uint8_t parse_state = S_CLASS_TAG;

/**
 * @brief parses the incoming uart data according to the agreed protocol
 * @param data uart data to be parsed
 */
void parse(uint8_t const data) {
	
	switch(parse_state) {

		case S_CLASS_TAG: {
			if(data == CT_MISC) {
				parse_state = S_PARSE_MISC;
			}
			else if(data == CT_GPIO) {
				parse_state = S_PARSE_GPIO;
			}
			else if(data == CT_ANALOG) {
				parse_state = S_PARSE_ANALOG;
			}
			else if(data == CT_I2C) {
				parse_state = S_PARSE_I2C;
			}
			else if(data == CT_SERVO) {
				parse_state = S_PARSE_SERVO;
			}
			else if(data == CT_COUNTER) {
				parse_state = S_PARSE_COUNTER;
			}		
		} break;

		case S_PARSE_MISC: {
			parse_misc(data);
		} break;

		case S_PARSE_GPIO: {
			parse_gpio(data);
		} break;

		case S_PARSE_ANALOG: {
			parse_analog(data);
		} break;

		case S_PARSE_I2C: {
			parse_i2c(data);
		} break;

		case S_PARSE_SERVO: {
			parse_servo(data);
		} break;
		
		case S_PARSE_COUNTER: {
			parse_counter(data);
		} break;

		default: {
		} break;
	}
}

// states of the misc parser
#define S_MISC_DT			(0)
#define S_MISC_RESET		(1)
#define S_MISC_ID			(2)
#define S_MISC_TEMP			(3)

#define DT_MISC_RESET		(0x01)
#define DT_MISC_ID			(0x02)
#define DT_MISC_TEMP		(0x03)

static volatile uint8_t misc_parse_state = S_MISC_DT;

#define MISC_NOK			(0)
#define MISC_OK				(1)
#define MISC_RESET_OK		(MISC_OK)
#define MISC_RESET_NOK		(MISC_NOK)
#define MISC_ID_OK			(MISC_OK)
#define MISC_ID_NOK			(MISC_NOK)
#define MISC_TEMP_OK		(MISC_OK)
#define MISC_TEMP_NOK		(MISC_NOK)

#include <util/delay.h>

/**
 * @brief parses the incoming uart data for misc actions
 * @param data uart data to be parsed
 */
void parse_misc(uint8_t const data) {

	switch(misc_parse_state) {

		case S_MISC_DT: {
			if(data == DT_MISC_RESET) {
				misc_parse_state = S_MISC_RESET;
			}
			else if(data == DT_MISC_ID) {
				misc_parse_state = S_MISC_ID;
			}
			else if(data == DT_MISC_TEMP) {
				misc_parse_state = S_MISC_TEMP;
			}

		} break;

		// MISC RESET
		case S_MISC_RESET: {
			uint8_t cs = CT_MISC + DT_MISC_RESET;
			uint8_t reply[4] = {CT_MISC, DT_MISC_RESET, 0, 0};
			if(cs == data) {
				reply[2] = MISC_RESET_OK;
			}
			else {
				reply[2] = MISC_RESET_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			misc_parse_state = S_MISC_DT;
			parse_state = S_CLASS_TAG;
			if(cs == data) { // trigger reset after 1 s (watchdog)
   				while(1) { }
			}
		} break;

		// MISC ID
		case S_MISC_ID: {
			uint8_t cs = CT_MISC + DT_MISC_ID;
			uint8_t reply[6] = {CT_MISC, DT_MISC_ID, 0, 0, 0, 0};
			if(cs == data) {
				reply[2] = MISC_ID_OK;
				uint16_t id = getId();
				reply[3] = (uint8_t)((id >> 8) & 0xFF);
				reply[4] = (uint8_t)(id & 0xFF);
			}
			else {
				reply[2] = MISC_ID_NOK;
			}
			reply[5] = reply[0] + reply[1] + reply[2] + reply[3] + reply[4];
			//_delay_ms(1);
			sendByteArray(reply, 6);
			misc_parse_state = S_MISC_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// MISC TEMP
		case S_MISC_TEMP: {
			uint8_t cs = CT_MISC + DT_MISC_TEMP;
			uint8_t reply[6] = {CT_MISC, DT_MISC_TEMP, 0, 0, 0, 0};
			if(cs == data) {
				reply[2] = MISC_TEMP_OK;
				uint16_t temp = readTemperature();
				reply[3] = (uint8_t)((temp >> 8) & 0xFF);
				reply[4] = (uint8_t)(temp & 0xFF);
			}
			else {
				reply[2] = MISC_TEMP_NOK;
			}
			reply[5] = reply[0] + reply[1] + reply[2] + reply[3] + reply[4];
			sendByteArray(reply, 6);
			misc_parse_state = S_MISC_DT;
			parse_state = S_CLASS_TAG;
		} break;

		default: {
		} break;
	}
}

// states of the gpio parser
#define S_GPIO_DT			(0)
#define S_GPIO_CONFIG_1		(1)
#define S_GPIO_CONFIG_2		(2)
#define S_GPIO_CONFIG_3		(3)
#define S_GPIO_READ_1		(4)
#define S_GPIO_READ_2		(5)
#define S_GPIO_WRITE_1		(6)
#define S_GPIO_WRITE_2		(7)
#define S_GPIO_WRITE_3		(8)

#define DT_GPIO_CONFIG 		(0x01)
#define DT_GPIO_READ 		(0x02)
#define DT_GPIO_WRITE 		(0x03)

static volatile uint8_t gpio_parse_state = S_GPIO_DT;

#define GPIO_CONFIG_OPTIONS_DIR		(0x01)
#define GPIO_CONFIG_OPTIONS_VALUE   (0x02)
#define GPIO_CONFIG_OPTIONS_PULLUP	(0x04)

#define GPIO_NOK					(0)
#define GPIO_OK						(1)
#define GPIO_CONFIG_NOK				(GPIO_NOK)
#define GPIO_CONFIG_OK				(GPIO_OK)
#define GPIO_READ_NOK				(GPIO_NOK)
#define GPIO_READ_OK				(GPIO_OK)
#define GPIO_WRITE_NOK				(GPIO_NOK)
#define GPIO_WRITE_OK				(GPIO_OK)

/**
 * @brief parses the incoming uart data for gpio actions
 * @param data uart data to be parsed
 */
void parse_gpio(uint8_t const data) {

	static uint8_t pinNumber = 0;
	static uint8_t configOptions = 0;
	static uint8_t pinValue = 0;
	
	switch(gpio_parse_state) {
	
		case S_GPIO_DT: {
			if(data == DT_GPIO_CONFIG) {
				gpio_parse_state = S_GPIO_CONFIG_1;
			}
			else if(data == DT_GPIO_READ) {
				gpio_parse_state = S_GPIO_READ_1;
			}
			else if(data == DT_GPIO_WRITE) {
				gpio_parse_state = S_GPIO_WRITE_1;
			}
		} break;

		// GPIO CONFIG
		case S_GPIO_CONFIG_1: {
			pinNumber = data;
			gpio_parse_state = S_GPIO_CONFIG_2;
		} break;

		case S_GPIO_CONFIG_2: {
			configOptions = data;
			gpio_parse_state = S_GPIO_CONFIG_3;
		} break;

		case S_GPIO_CONFIG_3: {
			uint8_t cs = CT_GPIO + DT_GPIO_CONFIG + pinNumber + configOptions;
			uint8_t reply[4] = {CT_GPIO, DT_GPIO_CONFIG, 0, 0};
			if(cs == data && (pinNumber >= 2 && pinNumber <= 13)) { // check if the checksum is correct
				// perform config operation and send answer
				gpio_dir dir = Input;
				if(configOptions & GPIO_CONFIG_OPTIONS_DIR) dir = Output;
				else dir = Input;
				uint8_t const val = ((configOptions & GPIO_CONFIG_OPTIONS_VALUE) >> 1);
				uint8_t const pullUpEnabled = ((configOptions & GPIO_CONFIG_OPTIONS_PULLUP) >> 2);
				configGpio(convertNumberToGpio(pinNumber), dir, val, pullUpEnabled);
				reply[2] = GPIO_CONFIG_OK;
			}
			else {
				reply[2] = GPIO_CONFIG_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			gpio_parse_state = S_GPIO_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// GPIO READ
		case S_GPIO_READ_1: {
			pinNumber = data;
			gpio_parse_state = S_GPIO_READ_2;
		} break;

		case S_GPIO_READ_2: {
			uint8_t cs = CT_GPIO + DT_GPIO_READ + pinNumber;
			uint8_t reply[5] = {CT_GPIO, DT_GPIO_READ, 0, 0, 0};
			if(cs == data  && (pinNumber >= 2 && pinNumber <= 13)) {
				uint8_t val=0, rise=0, fall=0;
				readGpio(convertNumberToGpio(pinNumber), &val, &rise, &fall);
				reply[2] = GPIO_READ_OK;
				reply[3] = (val) | (rise<<1) | (fall<<2);
			}
			else {
				reply[2] = GPIO_READ_NOK;
			}
			reply[4] = reply[0] + reply[1] + reply[2] + reply[3];
			sendByteArray(reply, 5);
			gpio_parse_state = S_GPIO_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// GPIO WRITE
		case S_GPIO_WRITE_1: {
			pinNumber = data;
			gpio_parse_state = S_GPIO_WRITE_2;
		} break;

		case S_GPIO_WRITE_2: {
			pinValue = data;
			gpio_parse_state = S_GPIO_WRITE_3;
		} break;

		case S_GPIO_WRITE_3: {
			uint8_t cs = CT_GPIO + DT_GPIO_WRITE + pinNumber + pinValue;
			uint8_t reply[4] = {CT_GPIO, DT_GPIO_WRITE, 0, 0};
			if(cs == data  && (pinNumber >= 2 && pinNumber <= 13)) {
				writeGpio(convertNumberToGpio(pinNumber), pinValue);
				reply[2] = GPIO_WRITE_OK;
			}
			else {
				reply[2] = GPIO_WRITE_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			gpio_parse_state = S_GPIO_DT;
			parse_state = S_CLASS_TAG;
		} break;
	
		default: {
		} break;
	}
}

// states of the analog parser
#define S_ANALOG_DT			(0)
#define S_ANALOG_READ_1		(1)
#define S_ANALOG_READ_2		(2)
#define S_ANALOG_READ_ALL_1	(3)

#define DT_ANALOG_READ	 	(0x02)
#define DT_ANALOG_READ_ALL	(0x03)

static volatile uint8_t analog_parse_state = S_ANALOG_DT;

#define ANALOG_NOK					(0)
#define ANALOG_OK					(1)
#define ANALOG_READ_OK				(ANALOG_OK)
#define ANALOG_READ_NOK				(ANALOG_NOK)
#define ANALOG_READ_ALL_OK			(ANALOG_OK)
#define ANALOG_READ_ALL_NOK			(ANALOG_NOK)

/**
 * @brief parses the incoming uart data for analog actions
 * @param data uart data to be parsed
 */
void parse_analog(uint8_t const data) {

	static uint8_t pinNumber = 0;

	switch(analog_parse_state) {
		case S_ANALOG_DT: {
			if(data == DT_ANALOG_READ) {
				analog_parse_state = S_ANALOG_READ_1;
			}
			else if(data == DT_ANALOG_READ_ALL) {
				analog_parse_state = S_ANALOG_READ_ALL_1;
			}
		} break;

		// ANALOG READ
		case S_ANALOG_READ_1: {
			pinNumber = data;
			analog_parse_state = S_ANALOG_READ_2;
		} break;

		case S_ANALOG_READ_2: {
			uint8_t cs = CT_ANALOG + DT_ANALOG_READ + pinNumber;
			uint8_t reply[6] = {CT_ANALOG, DT_ANALOG_READ, 0, 0, 0, 0};
			if(cs == data  && (pinNumber >= 0 && pinNumber <= 5)) {
				uint16_t analogValue = readAdc(convertNumberToAnalog(pinNumber));
				reply[2] = ANALOG_READ_OK;
				reply[3] = (uint8_t)((analogValue >> 8) & 0xFF);
				reply[4] = (uint8_t)(analogValue & 0xFF);
			}
			else {
				reply[2] = ANALOG_READ_NOK;
			}
			reply[5] = reply[0] + reply[1] + reply[2] + reply[3] + reply[4];
			sendByteArray(reply, 6);
			analog_parse_state = S_ANALOG_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// ANALOG READ ALL
		case S_ANALOG_READ_ALL_1: {
			uint8_t cs = CT_ANALOG + DT_ANALOG_READ_ALL;
			uint8_t reply[16] = {CT_ANALOG, DT_ANALOG_READ_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0};
			if(cs == data) {
				uint16_t analogValue = 0;
				uint8_t i = 0;
				reply[2] = ANALOG_READ_ALL_OK;

				for(i=0; i<12; i+=2) {
					analogValue = readAdc(convertNumberToAnalog(i>>1));
					reply[i+3] = (uint8_t)((analogValue >> 8) & 0xFF);
					reply[i+4] = (uint8_t)(analogValue & 0xFF); 
				}
			}
			else {
				reply[2] = ANALOG_READ_ALL_NOK;
			}
			// calc cs
			reply[15] = 0;
			{ 
				uint8_t i = 0;
				for(i=0; i<15; i++) {
					reply[15] += reply[i];
				}
			}
			sendByteArray(reply, 16);
			analog_parse_state = S_ANALOG_DT;
			parse_state = S_CLASS_TAG;			
		} break;

		default: {
		} break;
	}
}


// states of the i2c parser
#define S_I2C_DT			(0)
#define S_I2C_CONFIG_1		(1)
#define S_I2C_CONFIG_2		(2)
#define S_I2C_READ_1		(3)
#define S_I2C_READ_2		(4)
#define S_I2C_READ_3		(5)
#define S_I2C_READ_4		(6)
#define S_I2C_WRITE_1		(7)
#define S_I2C_WRITE_2		(8)
#define S_I2C_WRITE_3		(9)
#define S_I2C_WRITE_4		(10)
#define S_I2C_WRITE_5		(11)

#define DT_I2C_CONFIG		(0x01)
#define DT_I2C_READ	 		(0x02)
#define DT_I2C_WRITE		(0x03)

static volatile uint8_t i2c_parse_state = S_I2C_DT;

#define I2C_OK				(1)
#define I2C_NOK				(0)
#define I2C_CONFIG_OK		(I2C_OK)
#define I2C_CONFIG_NOK		(I2C_NOK)
#define I2C_READ_OK			(I2C_OK)
#define I2C_READ_NOK		(I2C_NOK)
#define I2C_WRITE_OK		(I2C_OK)
#define I2C_WRITE_NOK		(I2C_NOK)

/**
 * @brief parses incoming data for i2c communication
 */
void parse_i2c(uint8_t const data) {

	static uint8_t configOptions = 0;
	static uint8_t adr = 0;
	static uint8_t offset = 0;
	static uint8_t length = 0;
	static uint8_t data_arr[8];
	static uint8_t data_cnt = 0;

	switch(i2c_parse_state) {

		case S_I2C_DT: {
			if(data == DT_I2C_CONFIG) {
				i2c_parse_state = S_I2C_CONFIG_1;
			}
			else if(data == DT_I2C_READ) {
				i2c_parse_state = S_I2C_READ_1;
			}
			else if(data == DT_I2C_WRITE) {
				i2c_parse_state = S_I2C_WRITE_1;
			}
		} break;

		// I2C CONFIG
		case S_I2C_CONFIG_1: {
			configOptions = data;
			i2c_parse_state = S_I2C_CONFIG_2;
		} break;

		case S_I2C_CONFIG_2: {
			uint8_t cs = CT_I2C + DT_I2C_CONFIG + configOptions;
			uint8_t reply[4] = {CT_I2C, DT_I2C_CONFIG, 0, 0};
			if(cs == data && (configOptions == 0 || configOptions == 1)) {
				reply[2] = I2C_CONFIG_OK;
				if(configOptions == 0) configI2C(S100K);
				else if(configOptions == 1) configI2C(S400K);
			}
			else {
				reply[2] = I2C_CONFIG_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			i2c_parse_state = S_I2C_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// I2C READ
		case S_I2C_READ_1: {
			adr = data;
			i2c_parse_state = S_I2C_READ_2;
		} break;

		case S_I2C_READ_2: {
			offset = data;
			i2c_parse_state = S_I2C_READ_3;
		} break;		

		case S_I2C_READ_3: {
			length = data;
			i2c_parse_state = S_I2C_READ_4;
		} break;

		case S_I2C_READ_4: {
			uint8_t cs = CT_I2C + DT_I2C_READ + adr + offset + length;
			uint8_t reply[255+4]; // maximum possible response size
			reply[0] = CT_I2C;
			reply[1] = DT_I2C_READ;
			if(cs == data) {
				if(i2c_read(adr, offset, reply+3, length)) reply[2] = I2C_READ_OK;
				else reply[2] = I2C_READ_NOK;
				//reply[2] = i2c_read(adr, offset, reply+3, length);
			}
			else {
				reply[2] = I2C_READ_NOK;
			}
			// calc cs
			reply[length+3] = 0;
			for(uint8_t i=0; i<length+3; i++) {
				reply[length+3] += reply[i];
			}
			sendByteArray(reply, length+4);
			i2c_parse_state = S_I2C_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// I2C write
		case S_I2C_WRITE_1: {
			adr = data;
			i2c_parse_state = S_I2C_WRITE_2;
		} break;

		case S_I2C_WRITE_2: {
			offset = data;
			i2c_parse_state = S_I2C_WRITE_3;
		} break;

		case S_I2C_WRITE_3: {
			length = data;
			data_cnt = 0;
			i2c_parse_state = S_I2C_WRITE_4;
		} break;

		case S_I2C_WRITE_4: {
			data_arr[data_cnt] = data;
			data_cnt++;
			if(data_cnt == length) i2c_parse_state = S_I2C_WRITE_5;
		} break;

		case S_I2C_WRITE_5: {
			uint8_t cs = CT_I2C + DT_I2C_WRITE + adr + offset + length;
			uint8_t reply[4] = {CT_I2C, DT_I2C_WRITE, 0, 0};
			for(uint8_t i=0; i<length; i++) {
				cs += data_arr[i];
			}
			if(cs == data) {
				if(i2c_write(adr, offset, data_arr, length)) reply[2] = I2C_WRITE_OK;
				else reply[2] = I2C_WRITE_NOK;
				//reply[2] = i2c_write(adr, offset, data_arr, length);
			}
			else {
				reply[2] = I2C_WRITE_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			i2c_parse_state = S_I2C_DT;
			parse_state = S_CLASS_TAG;
		} break;

		default: {
		} break;
	}
}


// states for servo parser
#define S_SERVO_DT			(0)
#define S_SERVO_CONFIG_1	(1)
#define S_SERVO_CONFIG_2	(2)
#define S_SERVO_CONFIG_3	(3)
#define S_SERVO_CONFIG_4	(4)
#define S_SERVO_SET_1		(5)
#define S_SERVO_SET_2		(6)
#define S_SERVO_SET_3		(7)
#define S_SERVO_SET_4		(8)

static volatile uint8_t servo_parse_state = S_SERVO_DT;

#define DT_SERVO_CONFIG		(0x01)
#define DT_SERVO_SET 		(0x02)

#define SERVO_OK			(1)
#define SERVO_NOK			(0)
#define SERVO_CONFIG_OK		(SERVO_OK)
#define SERVO_CONFIG_NOK	(SERVO_NOK)
#define SERVO_SET_OK		(SERVO_OK)
#define SERVO_SET_NOK		(SERVO_NOK)

/**
 * @brief parses incoming data for servo communication
 */
void parse_servo(uint8_t const data) {

	static uint8_t servoPin = 0;
	static uint8_t pwmLowByte = 0;
	static uint8_t pwmHighByte = 0;

	switch(servo_parse_state) {

		case S_SERVO_DT: {
			if(data == DT_SERVO_CONFIG) {
				servo_parse_state = S_SERVO_CONFIG_1;
			}
			else if(data == DT_SERVO_SET) {
				servo_parse_state = S_SERVO_SET_1;
			}
		} break;

		// SERVO CONFIG
		case S_SERVO_CONFIG_1: {
			servoPin = data;
			servo_parse_state = S_SERVO_CONFIG_2;
		} break;

		case S_SERVO_CONFIG_2: {
			pwmLowByte = data;
			servo_parse_state = S_SERVO_CONFIG_3;
		} break;

		case S_SERVO_CONFIG_3: {
			pwmHighByte = data;
			servo_parse_state = S_SERVO_CONFIG_4;
		} break;

		case S_SERVO_CONFIG_4: {
			uint8_t cs = CT_SERVO + DT_SERVO_CONFIG + servoPin + pwmLowByte + pwmHighByte;
			uint8_t reply[4] = {CT_SERVO, DT_SERVO_CONFIG, 0, 0};
			if(cs == data && (servoPin == 9 || servoPin == 10 || servoPin == 2  || servoPin == 3 || servoPin == 4 || servoPin == 5 || servoPin == 6 || servoPin == 7)) {
				uint16_t pwm = (((uint16_t)(pwmHighByte)) << 8) + ((uint16_t)(pwmLowByte));
				reply[2] = SERVO_CONFIG_OK;
				if(servoPin == 9) {
					configServo(SERVO_D9, pwm);
				}
				else if(servoPin == 10) {
					configServo(SERVO_D10, pwm);
				}
				else if(servoPin == 2) {
					configServo(SERVO_D2, pwm);
				}
				else if(servoPin == 3) {
					configServo(SERVO_D3, pwm);
				}
				else if(servoPin == 4) {
					configServo(SERVO_D4, pwm);
				}
				else if(servoPin == 5) {
					configServo(SERVO_D5, pwm);
				}
				else if(servoPin == 6) {
					configServo(SERVO_D6, pwm);
				}
				else if(servoPin == 7) {
					configServo(SERVO_D7, pwm);
				}				
			}
			else {
				reply[2] = SERVO_CONFIG_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			servo_parse_state = S_SERVO_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// SERVO SET
		case S_SERVO_SET_1: {
			servoPin = data;
			servo_parse_state = S_SERVO_SET_2;
		} break;

		case S_SERVO_SET_2: {
			pwmLowByte = data;
			servo_parse_state = S_SERVO_SET_3;
		} break;

		case S_SERVO_SET_3: {
			pwmHighByte = data;
			servo_parse_state = S_SERVO_SET_4;
		} break;

		case S_SERVO_SET_4: {
			uint8_t cs = CT_SERVO + DT_SERVO_SET + servoPin + pwmLowByte + pwmHighByte;
			uint8_t reply[4] = {CT_SERVO, DT_SERVO_SET, 0, 0};
			if(cs == data && (servoPin == 9 || servoPin == 10 || servoPin == 2  || servoPin == 3 || servoPin == 4 || servoPin == 5 || servoPin == 6 || servoPin == 7)) {
				uint16_t pwm = (((uint16_t)(pwmHighByte)) << 8) + ((uint16_t)(pwmLowByte));
				reply[2] = SERVO_SET_OK;
				if(servoPin == 9) {
					setServoPwm(SERVO_D9, pwm);
				}
				else if(servoPin == 10) {
					setServoPwm(SERVO_D10, pwm);
				}
				else if(servoPin == 2) {
					setServoPwm(SERVO_D2, pwm);
				}
				else if(servoPin == 3) {
					setServoPwm(SERVO_D3, pwm);
				}
				else if(servoPin == 4) {
					setServoPwm(SERVO_D4, pwm);
				}
				else if(servoPin == 5) {
					setServoPwm(SERVO_D5, pwm);
				}
				else if(servoPin == 6) {
					setServoPwm(SERVO_D6, pwm);
				}
				else if(servoPin == 7) {
					setServoPwm(SERVO_D7, pwm);
				}
			}
			else {
				reply[2] = SERVO_SET_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			servo_parse_state = S_SERVO_DT;
			parse_state = S_CLASS_TAG;
		} break;

		default: {
		} break;
	}
}


// states for servo parser
#define S_COUNTER_DT		(0)
#define S_COUNTER_CONFIG_1	(1)
#define S_COUNTER_CONFIG_2	(2)
#define S_COUNTER_CONFIG_3	(3)
#define S_COUNTER_READ_1	(4)
#define S_COUNTER_READ_2	(5)

static volatile uint8_t counter_parse_state = S_SERVO_DT;

#define DT_COUNTER_CONFIG	(0x01)
#define DT_COUNTER_READ		(0x02)

#define COUNTER_OK			(1)
#define COUNTER_NOK			(0)
#define COUNTER_CONFIG_OK	(SERVO_OK)
#define COUNTER_CONFIG_NOK	(SERVO_NOK)
#define COUNTER_READ_OK		(SERVO_OK)
#define COUNTER_READ_NOK	(SERVO_NOK)

/**
 * @brief parses incoming data for counter configuration
 */
void parse_counter(uint8_t const data) {

	static uint8_t counter_pin = 0;
	static uint8_t counter_options = 0;
	
	switch(counter_parse_state) {
		
		case S_COUNTER_DT: {
			if(data == DT_COUNTER_CONFIG) {
				counter_parse_state = S_COUNTER_CONFIG_1;
			}
			else if(data == DT_COUNTER_READ) {
				counter_parse_state = S_COUNTER_READ_1;
			}
		} break;

		// COUNTER CONFIG
		case S_COUNTER_CONFIG_1: {
			counter_pin = data;
			counter_parse_state = S_COUNTER_CONFIG_2;
		} break;
		
		case S_COUNTER_CONFIG_2: {
			counter_options = data;
			counter_parse_state = S_COUNTER_CONFIG_3;
		} break;

		case S_COUNTER_CONFIG_3: {
			uint8_t cs = CT_COUNTER + DT_COUNTER_CONFIG + counter_pin + counter_options;
			uint8_t reply[4] = {CT_COUNTER, DT_COUNTER_CONFIG, 0, 0};
			if(cs == data && (counter_pin == 2 || counter_pin == 3)) {
				reply[2] = COUNTER_CONFIG_OK;
				cnt_options opt;
				if(counter_options & 0x01) opt = RISE;
				else if(counter_options & 0x02) opt = FALL;
				else if(counter_options & 0x04) opt = BOTH;
				if(counter_pin == 2) {
					configCounter(CNT_D2, opt);
				}
				else if(counter_pin == 3) {
					configCounter(CNT_D3, opt);
				}
			}
			else {
				reply[2] = COUNTER_CONFIG_NOK;
			}
			reply[3] = reply[0] + reply[1] + reply[2];
			sendByteArray(reply, 4);
			counter_parse_state = S_COUNTER_DT;
			parse_state = S_CLASS_TAG;
		} break;

		// COUNTER READ
		case S_COUNTER_READ_1: {
			counter_pin = data;
			counter_parse_state = S_COUNTER_READ_2;
		} break;
		
		case S_COUNTER_READ_2: {
			uint8_t cs = CT_COUNTER + DT_COUNTER_READ + counter_pin;
			uint8_t reply[5] = {CT_COUNTER, DT_COUNTER_READ, 0, 0, 0};
			if(cs == data && (counter_pin == 2 || counter_pin == 3)) {
				reply[2] = COUNTER_READ_OK;
				if(counter_pin == 2) {
					reply[3] = readCounter(CNT_D2);
				}
				else if(counter_pin == 3) {
					reply[3] = readCounter(CNT_D3);
				}
			}
			else {
				reply[2] = COUNTER_READ_NOK;
			}
			reply[4] = reply[0] + reply[1] + reply[2] + reply[3];
			sendByteArray(reply, 5);
			counter_parse_state = S_COUNTER_DT;
			parse_state = S_CLASS_TAG;
		} break;

		default: {
		} break;

	}
}

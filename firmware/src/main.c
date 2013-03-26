/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, BSc
 * @file main.c
 */

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdint.h>
#include "project.h"
#include "gpio.h"
#include "analog.h"
#include "servo.h"
#include "uart.h"
#include "parser.h"

// Prototype section
void initApplication();

int main() {

	initApplication();

	for(;;) {

		wdt_reset();

		while(uartDataAvailable()) {
			uint8_t data;
			readByte(&data);
			parse(data);
		}

	}

	return 0;
}

/**
 * @brief initialises the application
 */
void initApplication() {
	
	wdt_enable(WDTO_500MS); // enable watchdog, set to 0.5 second
	
	initGpio();

	initAnalog();

	initServo();

	initUart();

	sei(); // enable globally interrupts
}

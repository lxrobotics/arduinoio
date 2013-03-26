/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file temperature.c
 */

#include "temperature.h"
#include "analog.h"
#include <avr/io.h>

/**
 * @brief reads the temperature
 * @return temperature as read from the adc 
 */
uint16_t readTemperature() {
	// select internal 1.1 V reference as reference voltage
	ADMUX |= (1<<REFS1) | (1<<REFS0);

	// perform one conversion just in case we need extra initialisation
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)) { } // wait until the conversion is done

	uint16_t temp = readAdc(TEMP);

	// select AVCC as analog voltage reference again (delete REFS1)
	ADMUX &= ~(1<<REFS1);

	return temp;
}

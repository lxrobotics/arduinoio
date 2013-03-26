/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file analog.c
 */

#include <avr/io.h>
#include "analog.h"

/**
 * @brief initializes the adc section
 */
void initAnalog() {
	// disable digital input buffers on A0 to A3 (A4 and A5 are I2C)
	DIDR0 = (1<<ADC0D) | (1<<ADC1D) | (1<<ADC2D) | (1<<ADC3D);
	// select AVCC as analog voltage reference
	ADMUX = (1<<REFS0);
	// activate adc, fSample = 125 kHz, Prescaler = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	// perform a single conversion to initialize the adc
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)) { } // wait until the conversion is done
}

/**
 * @brief reads the value of a analog input pin
 * @return data from the analog sensor
 */
uint16_t readAdc(analog_pin const pin) {
	uint16_t res = 0;

	// select the mux according to the pin
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
	switch(pin) {
		case A0: break;
		case A1: ADMUX |= (1<<MUX0); break;
		case A2: ADMUX |= (1<<MUX1); break;
		case A3: ADMUX |= (1<<MUX1) | (1<<MUX0); break;
		case A4: ADMUX |= (1<<MUX2); break;
		case A5: ADMUX |= (1<<MUX2) | (1<<MUX0); break;
		case TEMP: ADMUX |= (1<<MUX3); break;
		default: return A_ERR; break;
	}

	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)) { } // wait until the conversion is done

	res = ADC;

	return res;
}

/**
 * @brief converts a number to the corresponding analog pin
 * @param pinNumber number of the pin e.g. 3 for A3
 * @return corresponding analog pin
 */
analog_pin convertNumberToAnalog(uint8_t const pinNumber) {
	switch(pinNumber) {
		case 0: return A0; break;
		case 1: return A1; break;
		case 2: return A2; break;
		case 3: return A3; break;
		case 4: return A4; break;
		case 5: return A5; break;
		default: return A_ERR; break;
	}
}

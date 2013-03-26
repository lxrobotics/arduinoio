/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file analog.h
 */

#ifndef ANALOG_H_
#define ANALOG_H_

#include <stdint.h>

typedef enum {A0, A1, A2, A3, A4, A5, TEMP, A_ERR} analog_pin;

/**
 * @brief initializes the adc section
 */
void initAnalog();

/**
 * @brief reads the value of a analog input pin
 * @return data from the analog sensor
 */
uint16_t readAdc(analog_pin const pin);

/**
 * @brief converts a number to the corresponding analog pin
 * @param pinNumber number of the pin e.g. 3 for A3
 * @return corresponding analog pin
 */
analog_pin convertNumberToAnalog(uint8_t const pinNumber);

#endif

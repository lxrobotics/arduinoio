/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file gpio.h
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef enum {D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D_ERR} gpio_pin;
typedef enum {Input, Output} gpio_dir;

typedef union {
  struct {
    uint8_t value : 1;	// value of the pin
	uint8_t rise  : 1;  // 1 = rising edge occured between the last readout and now
	uint8_t fall  : 1;  // 1 = falling edge occured between the last readout and now
  } pin;
} s_pin;

/**
 * @brief initialies the gpio handling
 */
void initGpio();

/**
 * @brief configs the gpio pin
 * @param pin pin tp configure
 * @param dir io direction of the pin, either in or out
 * @param value, initial value of the pin, needs to be set only in case of output
 * @param pullUpEnabled, needs to be set only in case of input
 */
void configGpio(gpio_pin const pin, gpio_dir const dir, uint8_t const value, uint8_t const pullUpEnabled);

/**
 * @brief reads the status of a gpio input pin
 * @param pin pin to read 
 * @param value current value of the pin
 * @param rise signals that a rising edge has occured
 * @param fall signals that a falling edge has occured
 */
void readGpio(gpio_pin const pin, uint8_t *value, uint8_t *rise, uint8_t *fall);

/**
 * @brief writes a value to a port 
 * @param pin pin for writing
 * @param value value to be written at a port pin
 */
void writeGpio(gpio_pin const pin, uint8_t const value);

/**
 * @brief converts a number to the corresponding gpio pin
 * @param pinNumber number of the pin e.g. 3 for D3
 * @return corresponding gpio pin
 */
gpio_pin convertNumberToGpio(uint8_t const pinNumber);

#endif

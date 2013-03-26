/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file i2c.h
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

typedef enum {S100K, S400K} i2c_speed;

/**
 * @brief configures the i2c module
 * @param speed speed of the i2c bus
 */
void configI2C(i2c_speed const speed);

/**
 * @brief writes data on the i2c bus
 * @param adr address to write to
 * @param offset to the register to write to
 * @param data array of data elements to write to slave
 * @param length number of elements to write to slave
 * @return 0 in case of error, 1 in case of success
 */
uint8_t i2c_write(uint8_t const adr, uint8_t const offset, uint8_t *data, uint8_t const length);

/**
 * @brief reads data on the i2c bus
 * @param adr address to read from
 * @param offset to the register to read from
 * @param data array of data elements to read from slave
 * @param length number of elements to read from slave
 * @return 0 in case of error, 1 in case of success
 */
uint8_t i2c_read(int8_t const adr, uint8_t const offset, uint8_t *data, uint8_t const length);

#endif

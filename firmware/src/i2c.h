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

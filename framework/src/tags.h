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

#ifndef TAGS_H_
#define TAGS_H_

namespace arduinoio {

// class tags
#define CT_MISC				(0x01)
#define CT_GPIO 			(0x02)
#define CT_ANALOG			(0x03)
#define CT_I2C				(0x04)
#define CT_SERVO			(0x05)
#define CT_COUNTER			(0x06)

// descriptor tags
#define DT_MISC_RESET		(0x01)
#define DT_MISC_ID			(0x02)
#define DT_MISC_TEMP		(0x03)
#define DT_GPIO_CONFIG 		(0x01)
#define DT_GPIO_READ 		(0x02)
#define DT_GPIO_WRITE 		(0x03)
#define DT_ANALOG_READ	 	(0x02)
#define DT_ANALOG_READ_ALL	(0x03)
#define DT_I2C_CONFIG		(0x01)
#define DT_I2C_READ			(0x02)
#define DT_I2C_WRITE		(0x03)
#define DT_SERVO_CONFIG		(0x01)
#define DT_SERVO_SET		(0x02)
#define DT_COUNTER_CONFIG	(0x01)
#define DT_COUNTER_READ		(0x02)

// status answers
#define MISC_NOK			(0)
#define MISC_OK				(1)
#define GPIO_NOK			(0)
#define GPIO_OK				(1)
#define ANALOG_NOK			(0)
#define ANALOG_OK			(1)
#define I2C_NOK				(0)
#define I2C_OK				(1)
#define SERVO_NOK			(0)
#define SERVO_OK			(1)
#define COUNTER_NOK			(0)
#define COUNTER_OK			(1)

/**
 * @brief checks if the checksum in the message is okay
 * @param pMsg pointer to the message
 * @param length length of the message
 * @return true if checksum is okay, false otherwise
 */
bool isChecksumOk(unsigned char *pMsg, int const length);

} // end of namespace arduinoio

#endif /* TAGS_H_ */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file tags.h
 * @author Alexander Entinger, BSc
 * @brief tags for the communication between pc and arduino board
 * @license MPL2.0
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


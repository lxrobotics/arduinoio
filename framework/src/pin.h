/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file pin.h
 * @author Alexander Entinger, BSc
 * @brief this file implements the pin class
 * @license MPL2.0
 */

#ifndef PIN_H_
#define PIN_H_

namespace arduinoio {

enum E_PIN {
	A0 = 0,
	A1 = 1,
	A2 = 2,
	A3 = 3,
	A4 = 4,
	A5 = 5,
	D2 = 6,
	D3 = 7,
	D4 = 8,
	D5 = 9,
	D6 = 10,
	D7 = 11,
	D8 = 12,
	D9 = 13,
	D10 = 14,
	D11 = 15,
	D12 = 16,
	D13 = 17
};

static E_PIN const CNT_PIN_1 = D2;
static E_PIN const CNT_PIN_2 = D3;

static E_PIN const SW_SERVO_PIN_1 = D2;
static E_PIN const SW_SERVO_PIN_2 = D3;
static E_PIN const SW_SERVO_PIN_3 = D4;
static E_PIN const SW_SERVO_PIN_4 = D5;
static E_PIN const SW_SERVO_PIN_5 = D6;
static E_PIN const SW_SERVO_PIN_6 = D7;

static E_PIN const HW_SERVO_PIN_1 = D9;
static E_PIN const HW_SERVO_PIN_2 = D10;

static E_PIN const I2C_SDA_PIN = A4;
static E_PIN const I2C_SCL_PIN = A5;

/**
 * @class pin
 * @brief represents a pin on the arduino io board
 */
class pin {
public:
	/**
	 * @brief Constructor
	 * @param p pin number
	 */
	pin(E_PIN const p);

	/**
	 * @brief Destructor
	 */
	~pin();

	/**
	 * @brief returns the pin designator
	 * @return pin designator
	 */
	inline E_PIN getPin() const {
		return m_pin;
	}

	/**
	 * @brief returns the pin number required for the serial communication
	 * @return required pin number for serial communication
	 */
	unsigned char getPinNumber() const;

	/**
	 * @brief operator ==
	 */
	inline bool operator ==(const pin &other) const {
		return (this->getPin() == other.getPin());
	}

private:
	E_PIN m_pin;
};

} // end of namespace arduinoio

#endif

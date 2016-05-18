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

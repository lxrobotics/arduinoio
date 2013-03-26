/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file gpioOutputPin.h
 * @author Alexander Entinger, BSc
 * @brief this file implements a digital output pin as an io entity
 * @license MPL2.0
 */

#ifndef GPIOOUTPUTPIN_H_
#define GPIOOUTPUTPIN_H_

#include "pin.h"
#include "ioentity.h"

namespace arduinoio {

/**
 * @class gpioOutputPin
 * @brief represents a digital output pin
 */
class gpioOutputPin: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer to the serial communication device
	 * @param p pin number
	 * @param pinValue initial value of the digital output pin
	 */
	gpioOutputPin(boost::shared_ptr<serial> const &serial, E_PIN const p, bool const pinValue);

	/**
	 * @brief Destructor
	 */
	virtual ~gpioOutputPin();

	/**
	 * @brief performs the requested configuration for the ioentity in question
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 * @brief returns the value of the pin
	 * @return true = 1, false = 0
	 */
	bool getPinValue() {
		return m_pinValue;
	}

	/**
	 * @brief sets the value of the output pin
	 * @param val true = 1, false = 0
	 * @return true in case of success, false in case of error
	 */
	bool setPinValue(bool const val);

private:
	bool m_pinValue;
};

} // end of namespace arduinoio

#endif /* GPIOOUTPUTPIN_H_ */

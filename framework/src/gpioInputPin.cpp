/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file gpioInputPin.cpp
 * @author Alexander Entinger, BSc
 * @brief this file implements a digital input pin as an io entity
 * @license MPL2.0
 */

#include "gpioInputPin.h"
#include <assert.h>
#include <iostream>
#include "tags.h"

namespace arduinoio {

/**
 * @brief Constructor
 * @param pComSerial pointer th the serial com module
 * @param p pin number
 * @param pullUpEnabled the pull up is enabled if this param is true
 */
gpioInputPin::gpioInputPin(boost::shared_ptr<serial> const &serial, E_PIN const p,
		bool const pullUpEnabled) :
	ioentity(serial), m_pullUpEnabled(pullUpEnabled) {

	m_pinVect.push_back(p);
}

/**
 * @brief Destructor
 */
gpioInputPin::~gpioInputPin() {

}

/**
 * @brief returns the value of the pin
 * @param val current value of the digital input pin
 * @param rise true, if a rising edge occured since the last readout, false otherwise
 * @param fall true, if a falling edge occured since the last readout, false otherwise
 * @return true in case of success, false in case of failure
 */
bool gpioInputPin::getPinValue(bool &val, bool &rise, bool &fall) {

	if(!isConfigured()) return false;

	// send request string
	int const msgSize = 4;
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	unsigned char msg[msgSize] = { CT_GPIO, DT_GPIO_READ, pinNumber, CT_GPIO
			+ DT_GPIO_READ + pinNumber };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 5;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_GPIO || reply.get()[1] != DT_GPIO_READ) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in request gpio input pin read message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == GPIO_NOK) {
		return false;
	}

	if (reply.get()[3] & 0x01)
		val = true;
	else
		val = false;
	if (reply.get()[3] & 0x02)
		rise = true;
	else
		rise = false;
	if (reply.get()[3] & 0x04)
		fall = true;
	else
		fall = false;

	return true;
}

/**
 * @brief configures the selected io pin as a input
 * @return true in case of sucess, false in case of error
 */
bool gpioInputPin::config() {
	// send request string
	int const msgSize = 5;
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	unsigned char configOptions = 0x00;
	if (m_pullUpEnabled) {
		configOptions = 0x04;
	}
	unsigned char msg[msgSize] =
			{ CT_GPIO, DT_GPIO_CONFIG, pinNumber, configOptions, CT_GPIO
					+ DT_GPIO_CONFIG + pinNumber + configOptions };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_GPIO || reply.get()[1] != DT_GPIO_CONFIG) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in request gpio input pin config message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == GPIO_NOK) {
		return false;
	}

	setIsConfiguredFlag();

	return true;
}

} // end of namespace arduinoio

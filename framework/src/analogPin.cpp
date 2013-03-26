/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file analogPin.cpp
 * @author Alexander Entinger, BSc
 * @brief this file implements a analog input pin as an io entity
 * @license MPL2.0
 */

#include "analogPin.h"
#include "tags.h"
#include <assert.h>
#include <iostream>
#include <cstring>

namespace arduinoio {

/**
 * @brief Constructor
 * @param p pin number
 */
analogPin::analogPin(boost::shared_ptr<serial> const &serial, E_PIN const p) :
		ioentity(serial) {

	m_pinVect.push_back(p);
}

/**
 * @brief Destructor
 */
analogPin::~analogPin() {

}

/**
 * @brief configures the ea hardware depending on the specific needs of the derived ioentity
 * @return true in case of success, false in case of failure
 */
bool analogPin::config() { // needs no configuration
	setIsConfiguredFlag();
	return true;
}

/**
 *  @brief returns the voltage measured at the ADC Pin in V
 *  @param voltage voltage at the adc pin in V
 *  @return true in case of success, false in case of failure
 */
bool analogPin::getPinVoltage(float &voltage) {

	if (!isConfigured())
		return false;

	// send request string
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	int const msgSize = 4;
	unsigned char msg[msgSize] = { CT_ANALOG, DT_ANALOG_READ, pinNumber,
			CT_ANALOG + DT_ANALOG_READ + pinNumber };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 6;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);
	if (reply.get()[0] != CT_ANALOG || reply.get()[1] != DT_ANALOG_READ) {
		std::cerr << __FILE__ << ":" << __LINE__
		<< " Error in request reply message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == ANALOG_NOK) {
		return false;
	}

	// write id into the the result variable
	unsigned int tmp = 0;
	unsigned char const tmpArray[2] = { reply.get()[4], reply.get()[3] };
	memcpy(&tmp, tmpArray, 2);
	// voltage measured at the adc pin
	voltage = ((float) (tmp)) * lsb;

	return true;
}

} // end of namespace arduinoio

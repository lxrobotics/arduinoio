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

#include "gpioOutputPin.h"
#include "tags.h"
#include <assert.h>
#include <iostream>

namespace arduinoio {

/**
 * @brief Constructor
 * @param pComSerial pointer to the serial communication device
 * @param p pin number
 * @param pinValue initial value of the digital output pin
 */
gpioOutputPin::gpioOutputPin(boost::shared_ptr<serial> const &serial, E_PIN const p,
		bool const pinValue) :
	ioentity(serial), m_pinValue(pinValue) {

	m_pinVect.push_back(p);
}

/**
 * @brief Destructor
 */
gpioOutputPin::~gpioOutputPin() {

}

/**
 * @brief performs the requested configuration for the ioentity in question
 * @return true in case of success, false in case of failure
 */
bool gpioOutputPin::config() {
	// send request string
	int const msgSize = 5;
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	unsigned char configOptions = 0x01;
	if (m_pinValue) {
		configOptions |= 0x02;
	}
	unsigned char msg[msgSize] =
			{ CT_GPIO, DT_GPIO_CONFIG, pinNumber, configOptions, CT_GPIO
					+DT_GPIO_CONFIG + pinNumber + configOptions };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_GPIO || reply.get()[1] != DT_GPIO_CONFIG) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in request gpio output pin config message."
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

/**
 * @brief sets the value of the output pin
 * @param val true = 1, false = 0
 * @return true in case of success, false in case of error
 */
bool gpioOutputPin::setPinValue(bool const val) {

	if(!isConfigured()) return false;

	// send request string
	int const msgSize = 5;
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	unsigned char pinValue = 0x00;
	if (val) {
		pinValue = 0x01;
	} else {
		pinValue = 0x00;
	}
	unsigned char msg[msgSize] = { CT_GPIO, DT_GPIO_WRITE, pinNumber, pinValue,
			CT_GPIO + DT_GPIO_WRITE + pinNumber + pinValue };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_GPIO || reply.get()[1] != DT_GPIO_WRITE) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in request gpio output pin setPinValue message."
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

	m_pinValue = val;

	return true;
}

} // end of namespace arduinoio

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

#include "counterPin.h"
#include "tags.h"
#include <cassert>

namespace arduinoio {

/**
 * @brief Constructor
 * @param pComSerial pointer to the serial com module
 * @param p pin number
 */
counterPin::counterPin(boost::shared_ptr<serial> const &serial, E_PIN const p,
		E_COUNTER_OPTIONS const opt) :
		ioentity(serial), m_options(opt) {

	assert(p == CNT_PIN_1 || p == CNT_PIN_2);

	m_pinVect.push_back(p);
}

/**
 * @brief Destructor
 */
counterPin::~counterPin() {

}

/**
 * @brief configures the ea hardware depending on the specific needs of the derived ioentity
 * @return true in case of success, false in case of failure
 */
bool counterPin::config() {

	// send request string
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	int const msgSize = 5;

	unsigned char options = 0x00;
	if (m_options == RISE)
		options = 0x01;
	else if (m_options == FALL)
		options = 0x02;
	else if (m_options == BOTH)
		options = 0x04;

	unsigned char msg[msgSize] = { CT_COUNTER, DT_COUNTER_CONFIG, pinNumber,
			options, CT_COUNTER + DT_COUNTER_CONFIG + pinNumber + options };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);

	if (reply.get()[0] != CT_COUNTER || reply.get()[1] != DT_COUNTER_CONFIG) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in request reply message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == COUNTER_NOK) {
		return false;
	}

	setIsConfiguredFlag();

	return true;
}

/**
 * @brief reads the value of the counter
 * @param val value of the counter
 * @return true in case of success, false in case of failure
 */
bool counterPin::readCounter(unsigned int &val) {

	if (!isConfigured())
		return false;

	// send request string
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	int const msgSize = 4;

	unsigned char msg[msgSize] = { CT_COUNTER, DT_COUNTER_READ, pinNumber,
			CT_COUNTER + DT_COUNTER_READ + pinNumber };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 5;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);

	if (reply.get()[0] != CT_COUNTER || reply.get()[1] != DT_COUNTER_READ) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in request reply message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == COUNTER_NOK) {
		return false;
	}

	val = static_cast<unsigned int>(reply.get()[3]);

	return true;
}

} // end of namespace arduinoio

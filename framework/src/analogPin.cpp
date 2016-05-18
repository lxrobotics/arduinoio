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

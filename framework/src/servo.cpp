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

#include "servo.h"
#include "tags.h"
#include <assert.h>
#include <iostream>

namespace arduinoio {

/**
 * @brief Constructor
 * @param pComSerial pointer to the serial com module
 * @param p pin of the servo io entity
 * @param pulseWidth_us pulse width of the servo pulse in us (should be between 1000 and 2000 us)
 */
servo::servo(boost::shared_ptr<serial> const &serial, E_PIN const p,
		unsigned int const pulseWidth_us) :
		ioentity(serial), m_pulseWidth_us(pulseWidth_us) {

	assert(m_pulseWidth_us <= maxPulseWidth);
	assert(m_pulseWidth_us >= minPulseWidth);
	assert(
			p == SW_SERVO_PIN_1 || p == SW_SERVO_PIN_2 || p == SW_SERVO_PIN_3 || p == SW_SERVO_PIN_4 || p == SW_SERVO_PIN_5 || p == SW_SERVO_PIN_6 || p == HW_SERVO_PIN_1 || p == HW_SERVO_PIN_2);

	m_pinVect.push_back(p);
}

/**
 * @brief Destructor
 */
servo::~servo() {

}

/**
 * @brief configures the servo
 * @return true in case of success, false in case of failure
 */
bool servo::config() {
	// in case of SERVO_PIN_1 and 2 we need to take special care, since its based on a 8bit timer
	if (m_pinVect[0] == SW_SERVO_PIN_1 || m_pinVect[0] == SW_SERVO_PIN_2
			|| m_pinVect[0] == SW_SERVO_PIN_3 || m_pinVect[0] == SW_SERVO_PIN_4
			|| m_pinVect[0] == SW_SERVO_PIN_5
			|| m_pinVect[0] == SW_SERVO_PIN_6) {
		m_pulseWidth_us = m_pulseWidth_us / 100;
	}

	// send request string
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	int const msgSize = 6;
	unsigned char const lowByte = (unsigned char) (m_pulseWidth_us & 0xFF);
	unsigned char const highByte = (unsigned char) ((m_pulseWidth_us >> 8)
			& 0xFF);

	unsigned char msg[msgSize] = { CT_SERVO, DT_SERVO_CONFIG, pinNumber,
			lowByte, highByte, CT_SERVO + DT_SERVO_CONFIG + pinNumber + lowByte
					+ highByte };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);

	if (reply.get()[0] != CT_SERVO || reply.get()[1] != DT_SERVO_CONFIG) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in request reply message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == SERVO_NOK) {
		return false;
	}

	setIsConfiguredFlag();

	return true;
}

/**
 * @brief sets the width of the servo pwm pulse
 * @param pulseWidth_us pulse width of the servo pulse in us (should be between 1000 and 2000 us)
 */
bool servo::setPwm(unsigned int const pulseWidth_us) {

	if (!isConfigured())
		return false;

	unsigned int tmpPulseWidth = 0;

	if (pulseWidth_us > maxPulseWidth)
		tmpPulseWidth = maxPulseWidth;
	else if (pulseWidth_us < minPulseWidth)
		tmpPulseWidth = minPulseWidth;
	else
		tmpPulseWidth = pulseWidth_us;

	// in case of SERVO_PIN_1 and 2 we need to take special care, since its based on a 8bit timer
	if (m_pinVect[0] == SW_SERVO_PIN_1 || m_pinVect[0] == SW_SERVO_PIN_2
			|| m_pinVect[0] == SW_SERVO_PIN_3 || m_pinVect[0] == SW_SERVO_PIN_4
			|| m_pinVect[0] == SW_SERVO_PIN_5
			|| m_pinVect[0] == SW_SERVO_PIN_6) {
		tmpPulseWidth = tmpPulseWidth / 100;
	}

	// send request string
	unsigned char pinNumber = m_pinVect[0].getPinNumber();
	int const msgSize = 6;
	unsigned char const lowByte = (unsigned char) (tmpPulseWidth & 0xFF);
	unsigned char const highByte = (unsigned char) ((tmpPulseWidth >> 8) & 0xFF);

	unsigned char msg[msgSize] = { CT_SERVO, DT_SERVO_SET, pinNumber, lowByte,
			highByte, CT_SERVO + DT_SERVO_SET + pinNumber + lowByte + highByte };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);

	if (reply.get()[0] != CT_SERVO || reply.get()[1] != DT_SERVO_SET) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in request reply message."
				<< std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == SERVO_NOK) {
		return false;
	}

	m_pulseWidth_us = tmpPulseWidth;

	return true;
}

/**
 * @brief returns the current pwm pulse widht setting
 * @return pulsewidth in us
 */
unsigned int servo::getPwm() const {
	if (m_pinVect[0] == SW_SERVO_PIN_1 || m_pinVect[0] == SW_SERVO_PIN_2
			|| m_pinVect[0] == SW_SERVO_PIN_3 || m_pinVect[0] == SW_SERVO_PIN_4
			|| m_pinVect[0] == SW_SERVO_PIN_5 || m_pinVect[0] == SW_SERVO_PIN_6)
		return (m_pulseWidth_us * 100);
	else
		return m_pulseWidth_us;
}

} // end of namespace arduinoio

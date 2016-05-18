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

#include "ioboard.h"
#include <assert.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include "ioentity_factory.h"

namespace arduinoio {

/**
 * @brief Constructor
 * @param devNode string designating the used device node for communication
 */
ioboard::ioboard(std::string const &devNode, unsigned int const baudRate) {

	m_serial = boost::shared_ptr<serial>(new serial(devNode, baudRate));

	sleep(1); // delay one second to allow serial device to be fully initialized

	if (!reset()) {
		std::cerr << __FILE__ << ":" << __LINE__
		<< " Error, couldnt reset board at startup." << std::endl;
	}

}

/**
 * @brief Destructor
 */
ioboard::~ioboard() {
	m_pinVect.clear();
}

boost::shared_ptr<analogPin> ioboard::createAnalogPin(E_PIN const p) {
	boost::shared_ptr<analogPin> ioent = ioentity_factory::createAnalogPin(
			m_serial, p);

	if (!isPinInVect(p)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure analog pin." << std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;
}

boost::shared_ptr<servo> ioboard::createServoPin(E_PIN const p,
		unsigned int const pulseWidth_us) {
	boost::shared_ptr<servo> ioent = ioentity_factory::createServoPin(m_serial,
			p, pulseWidth_us);

	if (!isPinInVect(p)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure servo pin." << std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;
}
boost::shared_ptr<i2cBridge> ioboard::createI2CBridge(
		unsigned int const baudRate) {
	boost::shared_ptr<i2cBridge> ioent = ioentity_factory::createI2CBridge(
			m_serial, baudRate);

	if (!isPinInVect(I2C_SDA_PIN) && !isPinInVect(I2C_SCL_PIN)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure I2C Bridge."
					<< std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;
}

boost::shared_ptr<gpioInputPin> ioboard::createGpioInputPin(E_PIN const p,
		bool const pullUpEnabled) {
	boost::shared_ptr<gpioInputPin> ioent =
			ioentity_factory::createGpioInputPin(m_serial, p, pullUpEnabled);

	if (!isPinInVect(p)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure gpio input pin."
					<< std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;
}

boost::shared_ptr<gpioOutputPin> ioboard::createGpioOutputPin(E_PIN const p,
		bool const pinValue) {
	boost::shared_ptr<gpioOutputPin> ioent =
			ioentity_factory::createGpioOutputPin(m_serial, p, pinValue);

	if (!isPinInVect(p)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure gpio output pin."
					<< std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;
}

boost::shared_ptr<counterPin> ioboard::createCounterPin(E_PIN const p,
		E_COUNTER_OPTIONS const opt) {
	boost::shared_ptr<counterPin> ioent =
			ioentity_factory::createCounterPin(m_serial, p, opt);

	if (!isPinInVect(p)) {
		if (!ioent->config()) {
			std::cerr << "Error, could not configure counter pin."
					<< std::endl;
		}
	} else {
		ioent.reset();
	}

	return ioent;

}

/**
 * @brief resets the ioboard
 * @return true if successful, false otherwise
 */
bool ioboard::reset() {
	// send request string
	int const msgSize = 3;
	unsigned char msg[msgSize] = { CT_MISC, DT_MISC_RESET, CT_MISC
			+ DT_MISC_RESET };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);
	if (reply.get()[0] != CT_MISC || reply.get()[1] != DT_MISC_RESET) {
		std::cerr << __FILE__ << ":" << __LINE__
		<< " Error in request reply message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == MISC_NOK) {
		return false;
	}

	sleep(1); // sleep 1 second to enable io board to perform a full reset

	m_pinVect.clear(); // now we can start reassigning functionality

	return true;
}

/**
 * @brief retrieves the id from the io board
 * @param id read from the board
 * @return true if successful, false otherwise
 */
bool ioboard::getId(unsigned int &id) {
	// send request string
	int const msgSize = 3;
	unsigned char msg[msgSize] = { CT_MISC, DT_MISC_ID, CT_MISC + DT_MISC_ID };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 6;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);
	if (reply.get()[0] != CT_MISC || reply.get()[1] != DT_MISC_ID) {
		std::cerr << __FILE__ << ":" << __LINE__
		<< " Error in request reply message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == MISC_NOK) {
		return false;
	}

	// write id into the the result variable
	unsigned char const tmp[2] = { reply.get()[4], reply.get()[3] };
	memcpy(&id, tmp, 2);

	return true;
}

/**
 * @brief retrieves the temperature from the boards cpu
 * @param temp temperature of the cpu of the io board
 * @return true if succesful, false otherwise
 */
bool ioboard::getTemperature(float &temp) {
	// send request string
	int const msgSize = 3;
	unsigned char msg[msgSize] =
			{ CT_MISC, DT_MISC_TEMP, CT_MISC + DT_MISC_TEMP };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 6;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);
	if (reply.get()[0] != CT_MISC || reply.get()[1] != DT_MISC_TEMP) {
		std::cerr << __FILE__ << ":" << __LINE__
		<< " Error in request reply message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == MISC_NOK) {
		return false;
	}

	// write id into the the result variable
	unsigned int tmp = 0;
	unsigned char const tmpArray[2] = { reply.get()[4], reply.get()[3] };
	memcpy(&tmp, tmpArray, 2);
	// voltage measured at the adc pin
	float resVoltage = ((float) (tmp)) * (1.1 / 1024.0);

	//printf("voltage res (tmp) = %d\n", tmp);

	temp = resVoltage; // TODO implement correct temperature by taking offset into consideration

	return true;
}

/**
 * @brief reads the analog value of all 6 analog input pins at once
 * @param ax voltage of ax, x = 0 to 5
 * @return true if successful, false otherwise
 */
bool ioboard::getAllAnalog(float &a0, float &a1, float &a2, float &a3,
		float &a4, float &a5) {

	// send request string
	int const msgSize = 3;
	unsigned char msg[msgSize] = { CT_ANALOG, DT_ANALOG_READ_ALL, CT_ANALOG
			+ DT_ANALOG_READ_ALL };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 16;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(
			replySize);
	if (reply.get()[0] != CT_ANALOG || reply.get()[1] != DT_ANALOG_READ_ALL) {
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

	{
		unsigned int tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[4], reply.get()[3] };
		memcpy(&tmp, tmpArray, 2);
		a0 = ((float) (tmp)) * lsb;
	}

	{
		unsigned tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[6], reply.get()[5] };
		memcpy(&tmp, tmpArray, 2);
		a1 = ((float) (tmp)) * lsb;
	}

	{
		unsigned int tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[8], reply.get()[7] };
		memcpy(&tmp, tmpArray, 2);
		a2 = ((float) (tmp)) * lsb;
	}

	{
		unsigned int tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[10], reply.get()[9] };
		memcpy(&tmp, tmpArray, 2);
		a3 = ((float) (tmp)) * lsb;
	}

	{
		unsigned int tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[12], reply.get()[11] };
		memcpy(&tmp, tmpArray, 2);
		a4 = ((float) (tmp)) * lsb;
	}

	{
		unsigned int tmp = 0;
		unsigned char const tmpArray[2] = { reply.get()[14], reply.get()[13] };
		memcpy(&tmp, tmpArray, 2);
		a5 = ((float) (tmp)) * lsb;
	}

	return true;
}

} // end of namespace arduinoio

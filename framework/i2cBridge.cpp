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

#include "i2cBridge.h"
#include "tags.h"
#include <assert.h>
#include <iostream>

namespace arduinoio {

/**
 * @brief Constructor
 * @param p pin number
 * @param baudRate Baudrate of the i2c bus
 */
i2cBridge::i2cBridge(boost::shared_ptr<serial> const &serial, unsigned int const baudRate) :
	ioentity(serial), m_baudRate(baudRate) {

	m_pinVect.push_back(I2C_SDA_PIN);
	m_pinVect.push_back(I2C_SCL_PIN);
}

/**
 * @brief Destructor
 */
i2cBridge::~i2cBridge() {

}

/**
 * @brief performs the requested configuration for the ioentity in question
 * @return true in case of success, false in case of failure
 */
bool i2cBridge::config() {

	// send request string
	int const msgSize = 4;
	unsigned char baudRate = 0x00;
	if (m_baudRate == i2cBaudRate100k)
		baudRate = 0x00;
	else if (m_baudRate == i2cBaudRate400k)
		baudRate = 0x01;
	unsigned char msg[msgSize] = { CT_I2C, DT_I2C_CONFIG, baudRate, CT_I2C
			+ DT_I2C_CONFIG + baudRate };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_I2C || reply.get()[1] != DT_I2C_CONFIG) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in reply i2c config read message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == I2C_NOK) {
		return false;
	}

	setIsConfiguredFlag();

	return true;
}

/**
 * @brief reads from the i2c slave with the address adr from the reg offset length bytes
 * @param adr address of the slave to read from
 * @param offset register to read from at the slave with the address adr
 * @param data pointer to the array, where the read data should be stored
 * @param length number of bytes to be read from the slave
 * @return true in case of success, false in case of error
 */
bool i2cBridge::read(unsigned char const adr, unsigned char const offset,
		unsigned char *data, unsigned char const length) {

	if(!isConfigured()) return false;

	// send request string
	int const msgSize = 6;
	unsigned char msg[msgSize] = { CT_I2C, DT_I2C_READ, adr, offset, length,
			CT_I2C + DT_I2C_READ + adr + offset + length };
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4 + length;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_I2C || reply.get()[1] != DT_I2C_READ) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in reply i2c read read message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == I2C_NOK) {
		return false;
	}

	// copy data
	for (unsigned int i = 0; i < length; i++) {
		data[i] = reply.get()[i + 3];
	}

	return true;
}

/**
 * @brief writes to the i2c slave with the address adr at the reg offset length bytes
 * @param adr address of the slave to write too
 * @param offset register to write to at the slave with the address adr
 * @param data pointer to the data array which content should be written to the slave device
 * @param length number of bytes to be written to the slave
 * @return true in case of success, false in case of error
 */
bool i2cBridge::write(unsigned char const adr, unsigned char const offset,
		unsigned char const *data, unsigned char const length) {

	if(!isConfigured()) return false;

	if (length < 1 || length > 8)
		return false;

	// send request string
	int const msgSize = 6 + length;
	unsigned char msg[msgSize];
	msg[0] = CT_I2C;
	msg[1] = DT_I2C_WRITE;
	msg[2] = adr;
	msg[3] = offset;
	msg[4] = length;
	for (unsigned int i = 0; i < length; i++) {
		msg[i + 5] = data[i];
	}
	msg[msgSize - 1] = 0;
	for (unsigned int i = 0; i < (unsigned int) (msgSize - 1); i++) {
		msg[msgSize - 1] += msg[i];
	}
	m_serial->writeToSerial(msg, msgSize);

	// retrieve answer and evaluate it
	int const replySize = 4;
	boost::shared_ptr<unsigned char> reply = m_serial->readFromSerial(replySize);
	if (reply.get()[0] != CT_I2C || reply.get()[1] != DT_I2C_WRITE) {
		std::cerr << __FILE__ << ":" << __LINE__
				<< " Error in reply i2c write message." << std::endl;
		return false;
	}
	if (!isChecksumOk(reply.get(), replySize)) {
		std::cerr << __FILE__ << ":" << __LINE__ << " Error in checksum."
				<< std::endl;
		return false;
	}
	if (reply.get()[2] == I2C_NOK) {
		return false;
	}

	return true;
}

} // end of namespace arduinoio

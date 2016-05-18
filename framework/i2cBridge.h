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

#ifndef I2CBRIDGE_H_
#define I2CBRIDGE_H_

#include "pin.h"
#include "ioentity.h"

namespace arduinoio {

static volatile unsigned int i2cBaudRate100k = 100000;
static volatile unsigned int i2cBaudRate400k = 400000;

/**
 * @class i2cBridge
 * @brief this class represents an i2c bridge
 */
class i2cBridge: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param p pin number
	 * @param baudRate Baudrate of the i2c bus
	 */
	i2cBridge(boost::shared_ptr<serial> const &serial, unsigned int const baudRate);

	/**
	 * @brief Destructor
	 */
	virtual ~i2cBridge();

	/**
	 * @brief performs the requested configuration for the ioentity in question
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 * @brief reads from the i2c slave with the address adr from the reg offset length bytes
	 * @param adr address of the slave to read from
	 * @param offset register to read from at the slave with the address adr
	 * @param data pointer to the array, where the read data should be stored
	 * @param length number of bytes to be read from the slave
	 * @return true in case of success, false in case of error
	 */
	bool read(unsigned char const adr, unsigned char const offset,
			unsigned char *data, unsigned char const length);

	/**
	 * @brief writes to the i2c slave with the address adr at the reg offset length bytes
	 * @param adr address of the slave to write too
	 * @param offset register to write to at the slave with the address adr
	 * @param data pointer to the data array which content should be written to the slave device
	 * @param length number of bytes to be written to the slave
	 * @return true in case of success, false in case of error
	 */
	bool write(unsigned char const adr, unsigned char const offset,
			unsigned char const *data, unsigned char const length);

private:
	unsigned int m_baudRate;
};

} // end of namespace arduinoio

#endif /* I2CBRIDGE_H_ */

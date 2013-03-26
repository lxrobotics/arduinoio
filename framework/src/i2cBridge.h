/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file i2cBridge.h
 * @author Alexander Entinger, BSc
 * @brief this file implements an I2C Bridge as an io entity
 * @license MPL2.0
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

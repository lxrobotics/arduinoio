/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file counterPin.h
 * @author Alexander Entinger, BSc
 * @brief this file implements a counter as an ioentity
 * @license MPL2.0
 */

#ifndef COUNTERPIN_H_
#define COUNTERPIN_H_

#include "ioentity.h"
#include "pin.h"

namespace arduinoio {

enum E_COUNTER_OPTIONS {RISE, FALL, BOTH};

class counterPin: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer to the serial com module
	 * @param p pin number
	 */
	counterPin(boost::shared_ptr<serial> const &serial, E_PIN const p, E_COUNTER_OPTIONS const opt);

	/**
	 * @brief Destructor
	 */
	virtual ~counterPin();

	/**
	 * @brief configures the ea hardware depending on the specific needs of the derived ioentity
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 * @brief reads the value of the counter
	 * @param val value of the counter
	 * @return true in case of success, false in case of failure
	 */
	bool readCounter(unsigned int &val);

private:
	E_COUNTER_OPTIONS m_options;
};

} // end of namespace arduinoio

#endif

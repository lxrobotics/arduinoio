/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file analogPin.h
 * @author Alexander Entinger, BSc
 * @brief this file implements a analog input pin as an io entity
 * @license MPL2.0
 */

#ifndef ANALOGPIN_H_
#define ANALOGPIN_H_

#include "ioentity.h"
#include "pin.h"

namespace arduinoio {

static float const vref = 5.0;
static float const lsb = vref / 1024.0;

/**
 * @class analogPin
 * @brief represents a analog input pin
 */
class analogPin: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer to the serial com module
	 * @param p pin number
	 */
	analogPin(boost::shared_ptr<serial> const &serial, E_PIN const p);

	/**
	 * @brief Destructor
	 */
	virtual ~analogPin();

	/**
	 * @brief configures the ea hardware depending on the specific needs of the derived ioentity
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 *  @brief returns the voltage measured at the ADC Pin in V
	 *  @param voltage voltage at the adc pin in V
	 *  @return true in case of success, false in case of failure
	 */
	bool getPinVoltage(float &voltage);
};

} // end of namespace arduinoio

#endif

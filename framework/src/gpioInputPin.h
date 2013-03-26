/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file gpioInputPin.h
 * @author Alexander Entinger, BSc
 * @brief this file implements a digital input pin as an io entity
 * @license MPL2.0
 */

#ifndef GPIOINPUTPIN_H_
#define GPIOINPUTPIN_H_

#include "pin.h"
#include "ioentity.h"

namespace arduinoio {

/**
 * @class gpioInputPin
 * @brief implements a digital input pin as an ioentity
 */
class gpioInputPin: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer th the serial com module
	 * @param p pin number
	 * @param pullUpEnabled the pull up is enabled if this param is true
	 */
	gpioInputPin(boost::shared_ptr<serial> const &serial, E_PIN const p,
			bool const pullUpEnabled = true);

	/**
	 * @brief Destructor
	 */
	virtual ~gpioInputPin();

	/**
	 * @brief returns the value of the pin
	 * @param val current value of the digital input pin
	 * @param rise true, if a rising edge occured since the last readout, false otherwise
	 * @param fall true, if a falling edge occured since the last readout, false otherwise
	 * @return true in case of success, false in case of failure
	 */
	bool getPinValue(bool &val, bool &rise, bool &fall);

	/**
	 * @brief performs the requested configuration for the ioentity in question
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

private:
	bool m_pullUpEnabled;
};

} // end of namespace arduinoio

#endif /* GPIOINPUTPIN_H_ */

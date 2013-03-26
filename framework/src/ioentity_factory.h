/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file ioentity_factory.h
 * @author Alexander Entinger, BSc
 * @brief this file implements a factor producing ioentities using static methods
 * @license MPL2.0
 */

#ifndef IOENTITY_FACTORY_H_
#define IOENTITY_FACTORY_H_

#include "analogPin.h"
#include "servo.h"
#include "i2cBridge.h"
#include "gpioInputPin.h"
#include "gpioOutputPin.h"
#include "counterPin.h"
#include "serial.h"
#include <boost/shared_ptr.hpp>

namespace arduinoio {

class ioentity_factory {
public:
	/**
	 * @brief Constructor and Destructor
	 */
	ioentity_factory() { }
	~ioentity_factory() { }

	/**
	 * @brief creator methods
	 */
	static boost::shared_ptr<analogPin> createAnalogPin(boost::shared_ptr<serial> const &serial, E_PIN const p) {
		return boost::shared_ptr<analogPin>(new analogPin(serial, p));
	}
	static boost::shared_ptr<servo> createServoPin(boost::shared_ptr<serial> const &serial, E_PIN const p, unsigned int const pulseWidth_us) {
		return boost::shared_ptr<servo>(new servo(serial, p, pulseWidth_us));
	}
	static boost::shared_ptr<i2cBridge> createI2CBridge(boost::shared_ptr<serial> const &serial, unsigned int const baudRate) {
		return boost::shared_ptr<i2cBridge>(new i2cBridge(serial, baudRate));
	}
	static boost::shared_ptr<gpioInputPin> createGpioInputPin(boost::shared_ptr<serial> const &serial, E_PIN const p, bool const pullUpEnabled) {
		return boost::shared_ptr<gpioInputPin>(new gpioInputPin(serial, p, pullUpEnabled));
	}
	static boost::shared_ptr<gpioOutputPin> createGpioOutputPin(boost::shared_ptr<serial> const &serial, E_PIN const p,	bool const pinValue) {
		return boost::shared_ptr<gpioOutputPin>(new gpioOutputPin(serial, p, pinValue));
	}
	static boost::shared_ptr<counterPin> createCounterPin(boost::shared_ptr<serial> const &serial, E_PIN const p, E_COUNTER_OPTIONS const opt) {
		return boost::shared_ptr<counterPin>(new counterPin(serial, p, opt));
	}
};

} // end of namespace arduinoio

#endif /* IOENTITY_FACTORY_H_ */

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

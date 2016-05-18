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

#ifndef GPIOOUTPUTPIN_H_
#define GPIOOUTPUTPIN_H_

#include "pin.h"
#include "ioentity.h"

namespace arduinoio {

/**
 * @class gpioOutputPin
 * @brief represents a digital output pin
 */
class gpioOutputPin: public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer to the serial communication device
	 * @param p pin number
	 * @param pinValue initial value of the digital output pin
	 */
	gpioOutputPin(boost::shared_ptr<serial> const &serial, E_PIN const p, bool const pinValue);

	/**
	 * @brief Destructor
	 */
	virtual ~gpioOutputPin();

	/**
	 * @brief performs the requested configuration for the ioentity in question
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 * @brief returns the value of the pin
	 * @return true = 1, false = 0
	 */
	bool getPinValue() {
		return m_pinValue;
	}

	/**
	 * @brief sets the value of the output pin
	 * @param val true = 1, false = 0
	 * @return true in case of success, false in case of error
	 */
	bool setPinValue(bool const val);

private:
	bool m_pinValue;
};

} // end of namespace arduinoio

#endif /* GPIOOUTPUTPIN_H_ */

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

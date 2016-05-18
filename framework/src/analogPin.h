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

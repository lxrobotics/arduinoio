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

#ifndef SERVO_H_
#define SERVO_H_

#include "pin.h"
#include "ioentity.h"

namespace arduinoio {

static volatile unsigned int const minPulseWidth = 1000;
static volatile unsigned int const maxPulseWidth = 2000;

/**
 * @class servo
 * @brief this class implements the configuration and control of a servo ioentity
 */
class servo : public ioentity {
public:
	/**
	 * @brief Constructor
	 * @param pComSerial pointer to the serial com module
	 * @param p pin of the servo io entity
	 * @param pulseWidth_us pulse width of the servo pulse in us (should be between 1000 and 2000 us)
	 */
	servo(boost::shared_ptr<serial> const &serial, E_PIN const p, unsigned int const pulseWidth_us);

	/**
	 * @brief Destructor
	 */
	virtual ~servo();

	/**
	 * @brief configures the servo
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config();

	/**
	 * @brief sets the width of the servo pwm pulse
	 * @param pulseWidth_us pulse width of the servo pulse in us (should be between 1000 and 2000 us)
	 */
	bool setPwm(unsigned int const pulseWidth_us);

	/**
	 * @brief returns the current pwm pulse widht setting
	 * @return pulsewidth in us
	 */
	unsigned int getPwm() const;

private:
	unsigned int m_pulseWidth_us; // pwm pulse width in us
};

} // end of namespace arduinoio

#endif /* SERVO_H_ */

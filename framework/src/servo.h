/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file servo.h
 * @author Alexander Entinger, BSc
 * @brief this file implements the handling of an servo ioentity
 * @license MPL2.0
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

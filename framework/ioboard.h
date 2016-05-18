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

#ifndef IOBOARD_H_
#define IOBOARD_H_

#include <vector>
#include <algorithm>
#include "serial.h"

#include "ioentity.h"
#include "pin.h"
#include "tags.h"
#include "analogPin.h"
#include "gpioInputPin.h"
#include "gpioOutputPin.h"
#include "i2cBridge.h"
#include "servo.h"
#include "counterPin.h"
#include "ioentity_factory.h"

namespace arduinoio {

/**
 * @class ioboard
 * @brief this class represents the arduino io board as an object in the pc
 */
class ioboard {
public:
	/**
	 * @brief Constructor
	 * @param devNode string designating the used device node for communication
	 */
	ioboard(std::string const &devNode, unsigned int const baudRate = 230400);

	/**
	 * @brief Destructor
	 */
	~ioboard();

	boost::shared_ptr<analogPin> createAnalogPin(E_PIN const p);
	boost::shared_ptr<servo> createServoPin(E_PIN const p, unsigned int const pulseWidth_us);
	boost::shared_ptr<i2cBridge> createI2CBridge(unsigned int const baudRate);
	boost::shared_ptr<gpioInputPin> createGpioInputPin(E_PIN const p, bool const pullUpEnabled = true);
	boost::shared_ptr<gpioOutputPin> createGpioOutputPin(E_PIN const p,	bool const pinValue);
	boost::shared_ptr<counterPin> createCounterPin(E_PIN const p, E_COUNTER_OPTIONS const opt);

	/**
	 * @brief resets the ioboard
	 * @return true if successful, false otherwise
	 */
	bool reset();
	/**
	 * @brief retrieves the id from the io board
	 * @param id read from the board
	 * @return true if successful, false otherwise
	 */
	bool getId(unsigned int &id);
	/**
	 * @brief retrieves the temperature from the boards cpu
	 * @param temp temperature of the cpu of the io board
	 * @return true if successful, false otherwise
	 */
	bool getTemperature(float &temp);
	/**
	 * @brief reads the analog value of all 6 analog input pins at once
	 * @param ax voltage of ax, x = 0 to 5
	 * @return true if successful, false otherwise
	 */
	bool getAllAnalog(float &a0, float &a1, float &a2, float &a3, float &a4,
			float &a5);

private:
	boost::shared_ptr<serial> m_serial;
	std::vector<E_PIN > m_pinVect;

	inline bool isPinInVect(E_PIN const p) {
		return (std::find(m_pinVect.begin(), m_pinVect.end(), p) != m_pinVect.end());
	}
};

} // end of namespace arduinoio

#endif /* IOBOARD_H_ */

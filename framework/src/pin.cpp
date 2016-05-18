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

#include "pin.h"
#include <assert.h>

namespace arduinoio {

/**
 * @brief Constructor
 * @param pin pin number
 */
pin::pin(E_PIN const p) :
		m_pin(p) {

}

/**
 * @brief Destructor
 */
pin::~pin() {

}

/**
 * @brief returns the pin number required for the serial communication
 * @return required pin number for serial communication
 */
unsigned char pin::getPinNumber() const {

	switch (m_pin) {
	case A0:
		return 0;
		break;
	case A1:
		return 1;
		break;
	case A2:
		return 2;
		break;
	case A3:
		return 3;
		break;
	case A4:
		return 4;
		break;
	case A5:
		return 5;
		break;
	case D2:
		return 2;
		break;
	case D3:
		return 3;
		break;
	case D4:
		return 4;
		break;
	case D5:
		return 5;
		break;
	case D6:
		return 6;
		break;
	case D7:
		return 7;
		break;
	case D8:
		return 8;
		break;
	case D9:
		return 9;
		break;
	case D10:
		return 10;
		break;
	case D11:
		return 11;
		break;
	case D12:
		return 12;
		break;
	case D13:
		return 13;
		break;
	default: {
		assert(false);
		return 0;
	}
		break;
	}

	return 0;
}

} // end of namespace arduinoio

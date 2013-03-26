/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file pin.cpp
 * @author Alexander Entinger, BSc
 * @brief this file implements the pin class
 * @license MPL2.0
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

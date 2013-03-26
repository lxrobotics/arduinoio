/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file tags.cpp
 * @author Alexander Entinger, BSc
 * @brief tags for the communication between pc and arduino board
 * @license MPL2.0
 */

#include "tags.h"
#include <assert.h>

namespace arduinoio {

/**
 * @brief checks if the checksum in the message is okay
 * @param pMsg pointer to the message
 * @param length length of the message
 * @return true if checksum is okay, false otherwise
 */
bool isChecksumOk(unsigned char *pMsg, int const length) {
	assert(pMsg != 0);

	unsigned char cs = 0;

	for (int i = 0; i < (length-1); i++) {
		cs += pMsg[i];
	}

	if (cs != pMsg[length - 1]) return false;
	else 						return true;
}

} // end of namespace arduinoio

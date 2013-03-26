/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
/**
 * @author Alexander Entinger, BSc
 * @file id.c
 */

#include "id.h"

static volatile uint16_t board_id = 0x0002;

/**
 * @brief retrieves the unique id of each io board
 * @return 16 bit id
 */
uint16_t getId() {
	return board_id;
}

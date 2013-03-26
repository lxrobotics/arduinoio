/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file id.h
 */

#ifndef ID_H_
#define ID_H_

#include <stdint.h>

/**
 * @brief retrieves the unique id of each io board
 * @return 16 bit id
 */
uint16_t getId();

#endif

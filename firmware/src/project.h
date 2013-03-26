/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, BSc
 * @file project.h
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include <stdint.h>

#define FALSE (0)
#define TRUE  (1)

#define set_bit(reg, bit) ((reg) |= (1 << (bit)))
#define clear_bit(reg, bit) ((reg) &= (uint8_t)~(1 << (bit)))

#endif

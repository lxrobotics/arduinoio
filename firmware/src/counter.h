/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file counter.h
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include <stdint.h>

typedef enum {CNT_D2, CNT_D3} cnt_pin;
typedef enum {RISE, FALL, BOTH} cnt_options;

/**
 * @brief configures a counter
 * @param p select the counter which we want to use
 * @param o options for that counter
 */
void configCounter(cnt_pin const p, cnt_options const o);

/**
 * @brief reads the current status of the counter and resets it to zero
 * @param p selects the counter which we want to read from
 * @return current status of the counter
 */
uint8_t readCounter(cnt_pin const p);

#endif

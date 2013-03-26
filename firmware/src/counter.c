/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file counter.c
 */

#include "counter.h"
#include "hal.h"
#include "project.h"
#include <avr/interrupt.h>
#include <avr/io.h>

// counters
static volatile uint8_t cnt_D2 = 0;
static volatile uint8_t cnt_D3 = 0;

/**
 * @brief configures a counter
 * @param p select the counter which we want to use
 * @param o options for that counter
 */
void configCounter(cnt_pin const p, cnt_options const o) {
	if(p == CNT_D2) {
		set_bit(IO2_PORT, IO2); // pull up
		clear_bit(IO2_DDR, IO2);
		if(o == RISE) EICRA |= (1<<ISC01) | (1<<ISC00);
		else if(o == FALL) EICRA |= (1<<ISC01);
		else if(o == BOTH) EICRA |= (1<<ISC00);
		EIMSK |= (1<<INT0);
		readCounter(CNT_D2);
	}
	else if(p == CNT_D3) {
		set_bit(IO3_PORT, IO3); // pull up
		clear_bit(IO3_DDR, IO3);
		if(o == RISE) EICRA |= (1<<ISC11) | (1<<ISC10);
		else if(o == FALL) EICRA |= (1<<ISC11);
		else if(o == BOTH) EICRA |= (1<<ISC10);
		EIMSK |= (1<<INT1);
		readCounter(CNT_D3);
	}
}

/**
 * @brief reads the current status of the counter and resets it to zero
 * @param p selects the counter which we want to read from
 * @return current status of the counter
 */
uint8_t readCounter(cnt_pin const p) {
	uint8_t ret = 0;
	if(p == CNT_D2) {
		cli();
		ret = cnt_D2;
		cnt_D2 = 0;
		sei();
	}
	else if(p == CNT_D3) {
		cli();
		ret = cnt_D3;
		cnt_D3 = 0;
		sei();
	}
	return ret;
}

/**
 * ISR for INT0
 */
ISR(INT0_vect) {
	cnt_D2++;
}

/**
 * ISR for INT1
 */
ISR(INT1_vect) {
	cnt_D3++;
}

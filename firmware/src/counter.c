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

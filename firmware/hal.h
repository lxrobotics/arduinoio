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

#ifndef HAL_H_
#define HAL_H_

#include <avr/io.h>

// digitial IO pins / gpio
#define IO2_PORT	(PORTD)
#define IO2_DDR		(DDRD)
#define IO2_PIN		(PIND)
#define IO2			(2)
#define IO2_PCINT	(PCINT18)
#define IO2_PCMSK	(PCMSK2)

#define IO3_PORT	(PORTD)
#define IO3_DDR		(DDRD)
#define IO3_PIN		(PIND)
#define IO3			(3)
#define IO3_PCINT	(PCINT19)
#define IO3_PCMSK	(PCMSK2)

#define IO4_PORT	(PORTD)
#define IO4_DDR		(DDRD)
#define IO4_PIN		(PIND)
#define IO4			(4)
#define IO4_PCINT	(PCINT20)
#define IO4_PCMSK	(PCMSK2)

#define IO5_PORT	(PORTD)
#define IO5_DDR		(DDRD)
#define IO5_PIN		(PIND)
#define IO5			(5)
#define IO5_PCINT	(PCINT21)
#define IO5_PCMSK	(PCMSK2)

#define IO6_PORT	(PORTD)
#define IO6_DDR		(DDRD)
#define IO6_PIN		(PIND)
#define IO6			(6)
#define IO6_PCINT	(PCINT22)
#define IO6_PCMSK	(PCMSK2)

#define IO7_PORT	(PORTD)
#define IO7_DDR		(DDRD)
#define IO7_PIN		(PIND)
#define IO7			(7)
#define IO7_PCINT	(PCINT23)
#define IO7_PCMSK	(PCMSK2)

#define IO8_PORT	(PORTB)
#define IO8_DDR		(DDRB)
#define IO8_PIN		(PINB)
#define IO8			(0)
#define IO8_PCINT	(PCINT0)
#define IO8_PCMSK	(PCMSK0)

#define IO9_PORT	(PORTB)
#define IO9_DDR		(DDRB)
#define IO9_PIN		(PINB)
#define IO9			(1)
#define IO9_PCINT	(PCINT1)
#define IO9_PCMSK	(PCMSK0)

#define IO10_PORT	(PORTB)
#define IO10_DDR	(DDRB)
#define IO10_PIN	(PINB)
#define IO10		(2)
#define IO10_PCINT	(PCINT2)
#define IO10_PCMSK	(PCMSK0)

#define IO11_PORT	(PORTB)
#define IO11_DDR	(DDRB)
#define IO11_PIN	(PINB)
#define IO11		(3)
#define IO11_PCINT	(PCINT3)
#define IO11_PCMSK	(PCMSK0)

#define IO12_PORT	(PORTB)
#define IO12_DDR	(DDRB)
#define IO12_PIN	(PINB)
#define IO12		(4)
#define IO12_PCINT	(PCINT4)
#define IO12_PCMSK	(PCMSK0)

#define IO13_PORT	(PORTB)
#define IO13_DDR	(DDRB)
#define IO13_PIN	(PINB)
#define IO13		(5)
#define IO13_PCINT	(PCINT5)
#define IO13_PCMSK	(PCMSK0)

// analog pins
#define A0_PORT		(PORTC)
#define A0_DDR		(DDRC)
#define A0_PIN		(PINC)
#define A0			(0)

#define A1_PORT		(PORTC)
#define A1_DDR		(DDRC)
#define A1_PIN		(PINC)
#define A1			(1)

#define A2_PORT		(PORTC)
#define A2_DDR		(DDRC)
#define A2_PIN		(PINC)
#define A2			(2)

#define A3_PORT		(PORTC)
#define A3_DDR		(DDRC)
#define A3_PIN		(PINC)
#define A3			(3)

#define A4_PORT		(PORTC)
#define A4_DDR		(DDRC)
#define A4_PIN		(PINC)
#define A4			(4)

#define A5_PORT		(PORTC)
#define A5_DDR		(DDRC)
#define A5_PIN		(PINC)
#define A5			(5)

// i2c
#define SDA_PORT	(PORTC)
#define SDA_DDR		(DDRC)
#define SDA_PIN		(PINC)
#define SDA			(4)

#define SCL_PORT	(PORTC)
#define SCL_DDR		(DDRC)
#define SCL_PIN		(PINC)
#define SCL			(5)

#endif

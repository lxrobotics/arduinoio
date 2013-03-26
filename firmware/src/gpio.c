/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file gpio.h
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "gpio.h"
#include "hal.h"
#include "project.h"

// static variables
static volatile s_pin io2, io3, io4, io5, io6, io7, io8, io9, io10, io11, io12, io13;

/**
 * @brief initialies the gpio handling
 */
void initGpio() {
	MCUCR &= ~(1<<PUD); // clear pull up disable, thereby preparing to allow the use of a pullup
	PCICR |=  (1<<PCIE0) | (1<<PCIE2); // enable pin change interrupts at PCINT[7:0], PCINT[23:16]
	memset((void*)&io2, 0, sizeof(io2)); // set everything to zero
	memset((void*)&io3, 0, sizeof(io3));
	memset((void*)&io4, 0, sizeof(io4));
	memset((void*)&io5, 0, sizeof(io5));
	memset((void*)&io6, 0, sizeof(io6));
	memset((void*)&io6, 0, sizeof(io7));
	memset((void*)&io8, 0, sizeof(io8));
	memset((void*)&io9, 0, sizeof(io9));
	memset((void*)&io10, 0, sizeof(io10));
	memset((void*)&io11, 0, sizeof(io11));
	memset((void*)&io12, 0, sizeof(io12));
	memset((void*)&io13, 0, sizeof(io13));
}

/**
 * @brief configs the gpio pin
 * @param pin pin tp configure
 * @param dir io direction of the pin, either in or out
 * @param value, initial value of the pin, needs to be set only in case of output
 * @param 1 = pullUpEnabled, needs to be set only in case of input
 */
void configGpio(gpio_pin const pin, gpio_dir const dir, uint8_t const value, uint8_t const pullUpEnabled) {

	switch(pin) {
	case D2: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO2_DDR, IO2);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO2_PORT, IO2);
			else clear_bit(IO2_PORT, IO2);
			set_bit(IO2_PCMSK, IO2_PCINT);
			clear_bit(IO2_DDR, IO2);
			io2.pin.value = (IO2_PIN & (1<<IO2)) >> IO2;
		}
	}
	break;
	case D3: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO3_DDR, IO3);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO3_PORT, IO3);
			else clear_bit(IO3_PORT, IO3);
			set_bit(IO3_PCMSK, IO3_PCINT);
			clear_bit(IO3_DDR, IO3);
			io3.pin.value = (IO3_PIN & (1<<IO3)) >> IO3;
		}
	}
	break;
	case D4: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO4_DDR, IO4);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO4_PORT, IO4);
			else clear_bit(IO4_PORT, IO4);
			set_bit(IO4_PCMSK, IO4_PCINT);
			clear_bit(IO4_DDR, IO4);
			io4.pin.value = (IO4_PIN & (1<<IO4)) >> IO4;
		}
	}
	break;
	case D5: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO5_DDR, IO5);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO5_PORT, IO5);
			else clear_bit(IO5_PORT, IO5);
			set_bit(IO5_PCMSK, IO5_PCINT);
			clear_bit(IO5_DDR, IO5);
			io5.pin.value = (IO5_PIN & (1<<IO5)) >> IO5;
		}
	}
	break;
	case D6: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO6_DDR, IO6);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO6_PORT, IO6);
			else clear_bit(IO6_PORT, IO6);
			set_bit(IO6_PCMSK, IO6_PCINT);
			clear_bit(IO6_DDR, IO6);
			io6.pin.value = (IO6_PIN & (1<<IO6)) >> IO6;
		}
	}
	break;
	case D7: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO7_DDR, IO7);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO7_PORT, IO7);
			else clear_bit(IO7_PORT, IO7);
			set_bit(IO7_PCMSK, IO7_PCINT);
			clear_bit(IO7_DDR, IO7);
			io7.pin.value = (IO7_PIN & (1<<IO7)) >> IO7;
		}
	}
	break;
	case D8: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO8_DDR, IO8);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO8_PORT, IO8);
			else clear_bit(IO8_PORT, IO8);
			set_bit(IO8_PCMSK, IO8_PCINT);
			clear_bit(IO8_DDR, IO8);
			io8.pin.value = (IO8_PIN & (1<<IO8)) >> IO8;
		}
	}
	break;
	case D9: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO9_DDR, IO9);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO9_PORT, IO9);
			else clear_bit(IO9_PORT, IO9);
			set_bit(IO9_PCMSK, IO9_PCINT);
			clear_bit(IO9_DDR, IO9);
			io9.pin.value = (IO9_PIN & (1<<IO9)) >> IO9;
		}
	}
	break;
	case D10: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO10_DDR, IO10);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO10_PORT, IO10);
			else clear_bit(IO10_PORT, IO10);
			set_bit(IO10_PCMSK, IO10_PCINT);
			clear_bit(IO10_DDR, IO10);
			io10.pin.value = (IO10_PIN & (1<<IO10)) >> IO10;
		}
	}
	break;
	case D11: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO11_DDR, IO11);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO11_PORT, IO11);
			else clear_bit(IO11_PORT, IO11);
			set_bit(IO11_PCMSK, IO11_PCINT);
			clear_bit(IO11_DDR, IO11);
			io11.pin.value = (IO11_PIN & (1<<IO11)) >> IO11;
		}
	}
	break;
	case D12: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO12_DDR, IO12);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO12_PORT, IO12);
			else clear_bit(IO12_PORT, IO12);
			clear_bit(IO12_DDR, IO12);
			set_bit(IO12_PCMSK, IO12_PCINT);
			io12.pin.value = (IO12_PIN & (1<<IO12)) >> IO12;
		}
	}
	break;
	case D13: {
	    if(dir == Output) {
			writeGpio(pin, value);
			set_bit(IO13_DDR, IO13);
		}
		else {
			if(pullUpEnabled == 1) set_bit(IO13_PORT, IO13);
			else clear_bit(IO13_PORT, IO13);
			clear_bit(IO13_DDR, IO13);
			set_bit(IO13_PCMSK, IO13_PCINT);
			io13.pin.value = (IO13_PIN & (1<<IO13)) >> IO13;
		}
	}
	break;
	default: {
	}
	break;
	}
}

/**
 * @brief reads the status of a gpio input pin
 * @param pin pin to read 
 * @param value current value of the pin
 * @param rise signals that a rising edge has occured
 * @param fall signals that a falling edge has occured
 */
void readGpio(gpio_pin const pin, uint8_t *value, uint8_t *rise, uint8_t *fall) {

	cli();	

	switch(pin) {
	case D2: {
		*value = io2.pin.value;
		*rise  = io2.pin.rise; io2.pin.rise = 0;
		*fall  = io2.pin.fall; io2.pin.fall = 0;
	}
	break;
	case D3: {
		*value = io3.pin.value;
		*rise  = io3.pin.rise; io3.pin.rise = 0;
		*fall  = io3.pin.fall; io3.pin.fall = 0;
	}
	break;
	case D4: {
		*value = io4.pin.value;
		*rise  = io4.pin.rise; io4.pin.rise = 0;
		*fall  = io4.pin.fall; io4.pin.fall = 0;
	}
	break;
	case D5: {
		*value = io5.pin.value;
		*rise  = io5.pin.rise; io5.pin.rise = 0;
		*fall  = io5.pin.fall; io5.pin.fall = 0;
	}
	break;
	case D6: {
		*value = io6.pin.value;
		*rise  = io6.pin.rise; io6.pin.rise = 0;
		*fall  = io6.pin.fall; io6.pin.fall = 0;
	}
	break;
	case D7: {
		*value = io7.pin.value;
		*rise  = io7.pin.rise; io7.pin.rise = 0;
		*fall  = io7.pin.fall; io7.pin.fall = 0;
	}
	break;
	case D8: {
		*value = io8.pin.value;
		*rise  = io8.pin.rise; io8.pin.rise = 0;
		*fall  = io8.pin.fall; io8.pin.fall = 0;
	}
	break;
	case D9: {
		*value = io9.pin.value;
		*rise  = io9.pin.rise; io9.pin.rise = 0;
		*fall  = io9.pin.fall; io9.pin.fall = 0;
	}
	break;
	case D10: {
		*value = io10.pin.value;
		*rise  = io10.pin.rise; io10.pin.rise = 0;
		*fall  = io10.pin.fall; io10.pin.fall = 0;
	}
	break;
	case D11: {
		*value = io11.pin.value;
		*rise  = io11.pin.rise; io11.pin.rise = 0;
		*fall  = io11.pin.fall; io11.pin.fall = 0;
	}
	break;
	case D12: {
		*value = io12.pin.value;
		*rise  = io12.pin.rise; io12.pin.rise = 0;
		*fall  = io12.pin.fall; io12.pin.fall = 0;
	}
	break;
	case D13: {
		*value = io13.pin.value;
		*rise  = io13.pin.rise; io13.pin.rise = 0;
		*fall  = io13.pin.fall; io13.pin.fall = 0;
	}
	break;
	default: {
	}
	break;
	}

	sei();
}

/**
 * @brief writes a value to a port 
 * @param pin pin for writing
 * @param value value to be written at a port pin
 */
void writeGpio(gpio_pin const pin, uint8_t const value) {
	
	switch(pin) {
	case D2: {
		if(value == 0) clear_bit(IO2_PORT, IO2);
		else if(value == 1) set_bit(IO2_PORT, IO2);
	}
	break;
	case D3: {
		if(value == 0) clear_bit(IO3_PORT, IO3);
		else if(value == 1) set_bit(IO3_PORT, IO3);
	}
	break;
	case D4: {
		if(value == 0) clear_bit(IO4_PORT, IO4);
		else if(value == 1) set_bit(IO4_PORT, IO4);
	}
	break;
	case D5: {
		if(value == 0) clear_bit(IO5_PORT, IO5);
		else if(value == 1) set_bit(IO5_PORT, IO5);
	}
	break;
	case D6: {
		if(value == 0) clear_bit(IO6_PORT, IO6);
		else if(value == 1) set_bit(IO6_PORT, IO6);
	}
	break;
	case D7: {
		if(value == 0) clear_bit(IO7_PORT, IO7);
		else if(value == 1) set_bit(IO7_PORT, IO7);
	}
	break;
	case D8: {
		if(value == 0) clear_bit(IO8_PORT, IO8);
		else if(value == 1) set_bit(IO8_PORT, IO8);
	}
	break;
	case D9: {
		if(value == 0) clear_bit(IO9_PORT, IO9);
		else if(value == 1) set_bit(IO9_PORT, IO9);
	}
	break;
	case D10: {
		if(value == 0) clear_bit(IO10_PORT, IO10);
		else if(value == 1) set_bit(IO10_PORT, IO10);
	}
	break;
	case D11: {
		if(value == 0) clear_bit(IO11_PORT, IO11);
		else if(value == 1) set_bit(IO11_PORT, IO11);
	}
	break;
	case D12: {
		if(value == 0) clear_bit(IO12_PORT, IO12);
		else if(value == 1) set_bit(IO12_PORT, IO12);
	}
	break;
	case D13: {
		if(value == 0) clear_bit(IO13_PORT, IO13);
		else if(value == 1) set_bit(IO13_PORT, IO13);
	}
	break;
	default: {
	}
	break;
	}
}

/**
 * @brief converts a number to the corresponding gpio pin
 * @param pinNumber number of the pin e.g. 3 for D3
 * @return corresponding gpio pin
 */
gpio_pin convertNumberToGpio(uint8_t const pinNumber) {

	switch(pinNumber) {
	case 2: return D2; break;
	case 3: return D3; break;
	case 4: return D4; break;
	case 5: return D5; break;
	case 6: return D6; break;
	case 7: return D7; break;
	case 8: return D8; break;
	case 9: return D9; break;
	case 10: return D10; break;
	case 11: return D11; break;
	case 12: return D12; break;
	case 13: return D13; break;
	default: return D_ERR; break;
	}
}

/**
 * @brief pin change interrupt 0 ISR
 */
ISR(PCINT0_vect) {

	if(IO8_PCMSK & (1<<IO8_PCINT)) {
		uint8_t io8_val  = (IO8_PIN & (1<<IO8)) >> IO8;
		if(io8_val != io8.pin.value) {
			if(io8_val == 0) io8.pin.fall = 1;
			else             io8.pin.rise = 1;
			io8.pin.value = io8_val;
		}
	}

	if(IO9_PCMSK & (1<<IO9_PCINT)) {
		uint8_t io9_val  = (IO9_PIN & (1<<IO9)) >> IO9;
		if(io9_val != io9.pin.value) {
			if(io9_val == 0) io9.pin.fall = 1;
			else             io9.pin.rise = 1;
			io9.pin.value = io9_val;
		}
	}

	if(IO10_PCMSK & (1<<IO10_PCINT)) {
		uint8_t io10_val  = (IO10_PIN & (1<<IO10)) >> IO10;
		if(io10_val != io10.pin.value) {
			if(io10_val == 0) io10.pin.fall = 1;
			else              io10.pin.rise = 1;
			io10.pin.value = io10_val;
		}
	}
	
	if(IO11_PCMSK & (1<<IO11_PCINT)) {
		uint8_t io11_val  = (IO11_PIN & (1<<IO11)) >> IO11;
		if(io11_val != io11.pin.value) {
			if(io11_val == 0) io11.pin.fall = 1;
			else              io11.pin.rise = 1;
			io11.pin.value = io11_val;
		}
	}
	
	if(IO12_PCMSK & (1<<IO12_PCINT)) {
		uint8_t io12_val  = (IO12_PIN & (1<<IO12)) >> IO12;
		if(io12_val != io12.pin.value) {
			if(io12_val == 0) io12.pin.fall = 1;
			else              io12.pin.rise = 1;
			io12.pin.value = io12_val;
		}
	}
	
	if(IO13_PCMSK & (1<<IO13_PCINT)) {
		uint8_t io13_val  = (IO13_PIN & (1<<IO13)) >> IO13;
		if(io13_val != io13.pin.value) {
			if(io13_val == 0) io13.pin.fall = 1;
			else              io13.pin.rise = 1;
			io13.pin.value = io13_val;
		}
	}
}

/**
 * @brief pin change interrupt 2 ISR
 */
ISR(PCINT2_vect) {

	if(IO2_PCMSK & (1<<IO2_PCINT)) {
		uint8_t io2_val  = (IO2_PIN & (1<<IO2)) >> IO2;
		if(io2_val != io2.pin.value) {
			if(io2_val == 0) io2.pin.fall = 1;
			else             io2.pin.rise = 1;
			io2.pin.value = io2_val;
		}
	}

	if(IO3_PCMSK & (1<<IO3_PCINT)) {
		uint8_t io3_val  = (IO3_PIN & (1<<IO3)) >> IO3;
		if(io3_val != io3.pin.value) {
			if(io3_val == 0) io3.pin.fall = 1;
			else             io3.pin.rise = 1;
			io3.pin.value = io3_val;
		}
	}

	if(IO4_PCMSK & (1<<IO4_PCINT)) {
		uint8_t io4_val  = (IO4_PIN & (1<<IO4)) >> IO4;
		if(io4_val != io4.pin.value) {
			if(io4_val == 0) io4.pin.fall = 1;
			else             io4.pin.rise = 1;
			io4.pin.value = io4_val;
		}
	}
	
	if(IO5_PCMSK & (1<<IO5_PCINT)) {
		uint8_t io5_val  = (IO5_PIN & (1<<IO5)) >> IO5;
		if(io5_val != io5.pin.value) {
			if(io5_val == 0) io5.pin.fall = 1;
			else             io5.pin.rise = 1;
			io5.pin.value = io5_val;
		}
	}
	
	if(IO6_PCMSK & (1<<IO6_PCINT)) {
		uint8_t io6_val  = (IO6_PIN & (1<<IO6)) >> IO6;
		if(io6_val != io6.pin.value) {
			if(io6_val == 0) io6.pin.fall = 1;
			else             io6.pin.rise = 1;
			io6.pin.value = io6_val;
		}
	}
	

	if(IO7_PCMSK & (1<<IO7_PCINT)) {
		uint8_t io7_val  = (IO7_PIN & (1<<IO7)) >> IO7;
		if(io7_val != io7.pin.value) {
			if(io7_val == 0) io7.pin.fall = 1;
			else             io7.pin.rise = 1;
			io7.pin.value = io7_val;
		}
	}
}

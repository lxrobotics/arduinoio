/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file servo.c
 */

#include "servo.h"
#include "hal.h"
#include "project.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

static uint16_t const pwm_min = (1000); // 1.0 ms
static uint16_t const pwm_middle = (1500); // 1.5 ms
static uint16_t const pwm_max = (2000); // 2.0 ms
static uint16_t const top_value = (20000); // 20 ms period

typedef union {
  struct {
    uint8_t D2_is_servo : 1; // Pin D2 is servo output
	uint8_t D3_is_servo : 1; // Pin D3 is servo output
	uint8_t D4_is_servo : 1; // ...
	uint8_t D5_is_servo : 1; // ...
	uint8_t D6_is_servo : 1; // ...
	uint8_t D7_is_servo : 1; // ...	
  };
} s_servo_bitmap;

static volatile s_servo_bitmap servo_bitmap;

static uint8_t const timer0_reload = (255-200); // for generating 100 us timer intervals
static uint8_t timer0_pwm_value_D2 = 15;
static uint8_t timer0_pwm_value_D3 = 15;
static uint8_t timer0_pwm_value_D4 = 15;
static uint8_t timer0_pwm_value_D5 = 15;
static uint8_t timer0_pwm_value_D6 = 15;
static uint8_t timer0_pwm_value_D7 = 15;



/**
 * @brief intializes the servo pwm generator
 */
void initServo() {

	memset((void*)(&servo_bitmap), 0, sizeof(servo_bitmap));

	// hardware pwm
	TCNT1 = 0;
	TCCR1B |= (1<<WGM13); // select phase and frequency correct timer mode
	ICR1 = top_value;
	OCR1A = pwm_middle;
	OCR1B = pwm_middle;

	// software pwm
	TCNT0 = 0;
	TIMSK0 = (1<<TOIE0); // enable timer 0 overflow interrupt
}

/**
 * @brief configures a servo pwm output
 * @param p servo pin to use
 * @param pwm_value pwm value for that servo 
 */
void configServo(servo_pin const p, uint16_t const pwm_value) {

	setServoPwm(p, pwm_value);

	switch(p) {
		case SERVO_D9: {
			set_bit(IO9_DDR, IO9);
			TCCR1A |= (1<<COM1A1); // set OC1A on upcounting, clears on downcounting
			TCCR1B |= (1<<CS11); // clk prescaler = 8, tCnt = 500 ns, 2^16 * 500 ns = 32.768 ms
		}
		break;
		case SERVO_D10: {
			set_bit(IO10_DDR, IO10);
			TCCR1A |= (1<<COM1B1);
			TCCR1B |= (1<<CS11);
		}
		break;
		case SERVO_D2: {
			set_bit(IO2_DDR, IO2);
			servo_bitmap.D2_is_servo = 1;
			timer0_pwm_value_D2 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		case SERVO_D3: {
			set_bit(IO3_DDR, IO3);
			servo_bitmap.D3_is_servo = 1;
			timer0_pwm_value_D3 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		case SERVO_D4: {
			set_bit(IO4_DDR, IO4);
			servo_bitmap.D4_is_servo = 1;
			timer0_pwm_value_D4 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		case SERVO_D5: {
			set_bit(IO5_DDR, IO5);
			servo_bitmap.D5_is_servo = 1;
			timer0_pwm_value_D5 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		case SERVO_D6: {
			set_bit(IO6_DDR, IO6);
			servo_bitmap.D6_is_servo = 1;
			timer0_pwm_value_D6 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		case SERVO_D7: {
			set_bit(IO7_DDR, IO7);
			servo_bitmap.D7_is_servo = 1;
			timer0_pwm_value_D7 = (uint8_t) pwm_value;
			TCCR0B |= (1<<CS01); // Prescale = 8, 16 MHz / 8 = 2 MHz, T = 0.5 us
		}
		break;
		default: {
		}
		break;
	}
}

/**
 * @brief set the value of a servo pwm
 * @param p servo pin to use
 * @param pwm_value pwm value for that servo 
 */
void setServoPwm(servo_pin const p, uint16_t const pwm_value) {

	uint16_t pwm = 0;
	if(p == SERVO_D9 || p == SERVO_D10) {
		if(pwm_value < pwm_min) {
			pwm = pwm_min;
		}
		else if(pwm_value > pwm_max) {
			pwm = pwm_max;
		}
		else {
			pwm = pwm_value;
		}
	}

	switch(p) {
		case SERVO_D9: {
			OCR1A = pwm;
		}
		break;
		case SERVO_D10: {
			OCR1B = pwm;
		}
		break;
		case SERVO_D2: {
			timer0_pwm_value_D2 = (uint8_t) pwm_value;
		}
		break;
		case SERVO_D3: {
			timer0_pwm_value_D3 = (uint8_t) pwm_value;
		}
		break;
		case SERVO_D4: {
			timer0_pwm_value_D4 = (uint8_t) pwm_value;
		}
		break;
		case SERVO_D5: {
			timer0_pwm_value_D5 = (uint8_t) pwm_value;
		}
		break;
		case SERVO_D6: {
			timer0_pwm_value_D6 = (uint8_t) pwm_value;
		}
		break;
		case SERVO_D7: {
			timer0_pwm_value_D7 = (uint8_t) pwm_value;
		}
		break;
		default: {
		}
		break;
	}
}

/**
 * @brief Timer 0 Overflow Interrupt, happens every 100 us
 */
static uint8_t timer0_100us_cnt_1 = 0;
static uint8_t timer0_100us_cnt_2 = 0;
#define S_TIMER0_SETPIN (0)
#define S_TIMER0_CLRPIN (1)
static uint8_t timer0_state = 0;


ISR(TIMER0_OVF_vect) {

	uint8_t const c_20_ms = 200;
	uint8_t const c_10_ms = 100;

	TCNT0 = timer0_reload;

	timer0_100us_cnt_1++; // counter for 20 ms period
	timer0_100us_cnt_2++; // counter for impulse length

	if(timer0_state == S_TIMER0_SETPIN) {
		if(timer0_100us_cnt_1 == c_20_ms) {
			if(servo_bitmap.D2_is_servo) set_bit(IO2_PORT, IO2);
			if(servo_bitmap.D3_is_servo) set_bit(IO3_PORT, IO3);
			if(servo_bitmap.D4_is_servo) set_bit(IO4_PORT, IO4);
			if(servo_bitmap.D5_is_servo) set_bit(IO5_PORT, IO5);
			if(servo_bitmap.D6_is_servo) set_bit(IO6_PORT, IO6);
			if(servo_bitmap.D7_is_servo) set_bit(IO7_PORT, IO7);

			timer0_state = S_TIMER0_CLRPIN;
			timer0_100us_cnt_1 = 0;
			timer0_100us_cnt_2 = 0;
		}
	}
	else if(timer0_state == S_TIMER0_CLRPIN) {
		if(timer0_100us_cnt_2 == timer0_pwm_value_D2 && servo_bitmap.D2_is_servo) clear_bit(IO2_PORT, IO2);
		if(timer0_100us_cnt_2 == timer0_pwm_value_D3 && servo_bitmap.D3_is_servo) clear_bit(IO3_PORT, IO3);
		if(timer0_100us_cnt_2 == timer0_pwm_value_D4 && servo_bitmap.D4_is_servo) clear_bit(IO4_PORT, IO4);
		if(timer0_100us_cnt_2 == timer0_pwm_value_D5 && servo_bitmap.D5_is_servo) clear_bit(IO5_PORT, IO5);
		if(timer0_100us_cnt_2 == timer0_pwm_value_D6 && servo_bitmap.D6_is_servo) clear_bit(IO6_PORT, IO6);
		if(timer0_100us_cnt_2 == timer0_pwm_value_D7 && servo_bitmap.D7_is_servo) clear_bit(IO7_PORT, IO7);

		if(timer0_100us_cnt_1 > c_10_ms) { // switch back to state SETPIN, all pins must have cleared till then
			timer0_state = S_TIMER0_SETPIN;
		}
	}
	
 }


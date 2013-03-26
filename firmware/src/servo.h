/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file servo.h
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

typedef enum {SERVO_D9, SERVO_D10, SERVO_D2, SERVO_D3, SERVO_D4, SERVO_D5, SERVO_D6, SERVO_D7} servo_pin; // D9 = OC1A, D10 = OC1B, D2 till D7 Software PWM

/**
 * @brief intializes the servo pwm generator
 */
void initServo();

/**
 * @brief configures a servo pwm output
 * @param p servo pin to use
 * @param pwm_value pwm value for that servo 
 */
void configServo(servo_pin const p, uint16_t const pwm_value);

/**
 * @brief set the value of a servo pwm
 * @param p servo pin to use
 * @param pwm_value pwm value for that servo 
 */
void setServoPwm(servo_pin const p, uint16_t const pwm_value);

#endif

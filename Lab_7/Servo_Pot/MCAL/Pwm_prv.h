/*
 * Pwm_prv.h
 *
 *  Created on: May 24, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef PWM_PRV_H_
#define PWM_PRV_H_

#define MODE_CLEAR_MASK 	0xB7// will be &=  -- valid for Timer0 and Timer 1

#define CLK_CLEAR_MASK 		0x07

#define MAX_VALUE_TIMER0	0xff
#define MAX_VALUE_TIMER1	0xffff
#define MAX_VALUE_TIMER2	0xff

#define MAX_NUM_OF_PRESCALERS_CLK			3
#define MAX_NUM_OF_OVF_CHANNELS				3
#define MAX_NUM_OF_OCM_CHANNELS				4

#define PWM_TCCR1A_WGM_CLEAR_MASK		0xE7
#define PWM_TCCR1B_WGM_CLEAR_MASK		0xFC

#endif /* PWM_PRV_H_ */

/*
 * Adc_cfg.h
 *
 *  Created on: Apr 1, 2022
 *      Author:Abdelrahman Yousry
 */

#ifndef MCAL_ADC_CFG_H_
#define MCAL_ADC_CFG_H_
/*ADMUX Register*/
/*These macros for selecting Channel, voltage and Adjustment*/
#define ADC_CHANNEL			ADC_u8CH_0
#define ADC_ADJUSTMENT		ADC_u8RIGHT_ADJUSTMENT
#define ADC_VOLTAGE_REF		ADC_u8AVCC
/**************************************************************************/


/*ADCSRA Register*/
//----------------------------------
/*This macro for enabling or disable ADC*/
/*Select one of the following options:
 *
1- ADC_u8ENABLE
2- ADC_u8DISABLE
*/
#define ADC_u8CONTROL			ADC_u8ENABLE

/*Select one of the following options:
 *
1- ADC_u8FREE_RUNNING_MODE
2- ADC_u8ANALOG_COMPARATOR
3- ADC_u8EXTERNAL_INTERRUPT_REQUEST_0
4- ADC_u8TIMER0_COMPARE_MATCH
5- ADC_u8TIMER0_OVERFLOW
6- ADC_u8TIMER_COMPARE_MATCH_B
7- ADC_u8TIMER1_OVERFLOW
8- ADC_u8TIMER1_CAPTURE_EVENT
*/
#define ADC_u8AUTO_TRIGGER_SOURCE 	ADC_u8FREE_RUNNING_MODE

/*ADC PRESCALER*/
//this prescaler is to divide the clock entered to the adc circuit
/*Select one of the following options:*/
/*
1- ADC_u8DIVISION_FACTOR_2
2- ADC_u8DIVISION_FACTOR_4
3- ADC_u8DIVISION_FACTOR_8
4- ADC_u8DIVISION_FACTOR_16
5- ADC_u8DIVISION_FACTOR_32
6- ADC_u8DIVISION_FACTOR_64
7- ADC_u8DIVISION_FACTOR_128
 *
 * */
#define ADC_PRESCALER	ADC_u8DIVISION_FACTOR_8
/*Select one of the following options:
 *
1- ADC_u8ENABLE_INTERRUPT
2- ADC_u8DISABLE_INTERRUPT
*/
#define ADC_u8INTERRUPT ADC_u8ENABLE_INTERRUPT
#endif /* MCAL_ADC_CFG_H_ */

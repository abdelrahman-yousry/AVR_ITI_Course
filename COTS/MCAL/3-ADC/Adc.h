/*
 * Adc.h
 *
 *  Created on: Mar 25, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef ADC_H_
#define ADC_H_

//typedef struct
//{
//	u8 channel;
//	u8 adjust_dir;
//	u8 volt_ref;
//}Adc_tmode;


/**
 * REGISTER ---> ADCSRA
 * Those macros will be | (CHENNEL|VOLTREF|ADJUSTMENT)
 * to be set to the ADMUX register
 **/

/*Macros for ADC channels*/
/*PORTA Pin 0-->7 */
#define ADC_u8CH_0						0b00000000
#define ADC_u8CH_1						0b00000001
#define ADC_u8CH_2						0b00000010
#define ADC_u8CH_3						0b00000011
#define ADC_u8CH_4						0b00000100
#define ADC_u8CH_5						0b00000101
#define ADC_u8CH_6						0b00000110
#define ADC_u8CH_7						0b00000111
/***************************************************************************************************/
/*Macros for differential ADC*/
#define ADC_u8DEF_x10_CH_0					0b00001000
#define ADC_u8DEF_x10_CH_1to0				0b00001001
#define ADC_u8DEF_x200_CH_0         	    0b00001010
#define ADC_u8DEF_x200_CH_1to0      	    0b00001011
#define ADC_u8DEF_x10_CH_2              	0b00001100
#define ADC_u8DEF_x10_CH_3to2             	0b00001101
#define ADC_u8DEF_x1_CH_2	                0b00001110
#define ADC_u8DEF_x1_CH_3to2              	0b00001111
#define ADC_u8DEF_x1_CH_0to1              	0b00010000
#define ADC_u8DEF_x1_CH_1to1              	0b00010001
#define ADC_u8DEF_x1_CH_2to1              	0b00010010
#define ADC_u8DEF_x1_CH_3to1              	0b00010011
#define ADC_u8DEF_x1_CH_4to1              	0b00010100
#define ADC_u8DEF_x1_CH_5to1              	0b00010101
#define ADC_u8DEF_x1_CH_6to1				0b00010110
#define ADC_u8DEF_x1_CH_7to1				0b00010111
#define ADC_u8DEF_x1_CH_0to2              	0b00011000
#define ADC_u8DEF_x1_CH_1to2              	0b00011001
#define ADC_u8DEF_x1_CH_2to2             	0b00011010
#define ADC_DEF_x1_CH_3to2              	0b00011011
#define ADC_DEF_x1_CH_4to2              	0b00011101

/*Macro for resetting the 5 MUX bits in reg ADMUX
 * why we should reset first?
 * --> to make these 5 bits zero and the last three bits to be 1
 * so if we  | these macros we will change only in the first 5 bits
 * */
//#define	FIVE_BIT_RESET_MASK				0b11100000



/*Macros for selecting the reference voltage
 * last two bits are responsible for selecting the ref volt
 * 00-->ADC_AREF
 * 01-->ADC_AVCC
 * 11-->ADC_INTERNAL_VOLT
 * */
#define ADC_u8AREF 						0b00000000//max volt is the applied vcc
#define ADC_u8AVCC						0b01000000
#define ADC_u8INTERNAL_2.56VOLT			0b11000000


/*Macros for Left/Right Adjustment*/
#define ADC_u8RIGHT_ADJUSTMENT			0b00000000
#define ADC_u8LEFT_ADJUSTMENT			0b00100000
/*****************************************************************************************************/
/**
 *REGISTER ---> ADCSRA
 */
/*Control selections
 * bit no --> 7*/
#define ADC_u8ENABLE					1//I will make it by #if using SETBIT and CLRBIT
#define ADC_u8DISABLE					0


/*start conversion
 * bit no --> */
#define ADC_u8START_CONVERSION			6

/*ADC auto trigger enable
 * bit no --> 5*/
//ADC Auto Trigger Source:
//-----------------------------
#define ADCSRA_AUTO_TRIG_DISABLE						0b00000000
#define ADCSRA_AUTO_TRIG_ENABLE							0b00100000

/*ADC Interrupt:
 * bit no --> 4*/
#define ADC_u8ENABLE_INTERRUPT 			0b00001000
#define ADC_u8DISABLE_INTERRUPT 		0b00000000


/*ADC PRESCALER selections:
 * bit no --> 0-2 -*/
#define ADC_u8DIVISION_FACTOR_2 		0b00000000
#define ADC_u8DIVISION_FACTOR_4 		0b00000010
#define ADC_u8DIVISION_FACTOR_8 		0b00000011
#define ADC_u8DIVISION_FACTOR_16 		0b00000100
#define ADC_u8DIVISION_FACTOR_32 		0b00000101
#define ADC_u8DIVISION_FACTOR_64 		0b00000110
#define ADC_u8DIVISION_FACTOR_128 		0b00000111


/*Register --> SFIOR*/
#define ADC_u8FREE_RUNNING_MODE 				0b00000000
#define ADC_u8ANALOG_COMPARATOR 				0b00100000
#define ADC_u8EXTERNAL_INTERRUPT_REQUEST_0 		0b01000000
#define ADC_u8TIMER0_COMPARE_MATCH 				0b01100000
#define ADC_u8TIMER0_OVERFLOW 					0b10000000
#define ADC_u8TIMER_COMPARE_MATCH_B 			0b10100000
#define ADC_u8TIMER1_OVERFLOW 					0b11000000
#define ADC_u8TIMER1_CAPTURE_EVENT 				0b11100000
/*****************************************************************************************************/
typedef enum
{
	WrongConfig
}Adc_tenuErrorStatus;


/**********You should go through this sequence*************/
/* 1- call init func
 * 2- call Control function to enable adc
 * 3- call start conversion func
 * 4- call get result func
 * */



/*----------------------------PROTOTYPES----------------------------------*/
/**
 * Description: is used to set the initial value and mode for the ADC
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
void Adc_vidInit(void);
/**
 * Description: is used to get the adc conversion value
 * Inputs: it takes no inputs.
 * Return: it returns u16.
 **/
u16 Adc_u16GetResult(void);
/**
 * Description: is used to make ADC start conversion
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
void Adc_vidStartConversion(void);
/**
 * Description: is used to make ADC enable or disable
 * Inputs: it takes the control value as input.
 * Return: it has no returns.
 **/
void Adc_vidControl(u8 copy_control);
/**
 * Description: is used to get the flag value
 * which indicates that the conversion has been done or not
 * Inputs: it takes no inputs.
 * Return: it returns u8
 **/
u8 Adc_u8GetInterruptFlagValue(void);



#endif /* ADC_H_ */

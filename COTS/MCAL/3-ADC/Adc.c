/*
 * Adc.c
 *
 *  Created on: Mar 25, 2022
 *      Author: Abdelrahman Yousry
 */

#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Adc.h"
#include "../MCAL/Adc_cfg.h"
#include "../MCAL/Adc_prv.h"
#include "avr/io.h"
/**
 * Description: is used to clear the interrupt flag for new conversion
 * because these flag is set once the conversion is completed, then you should
 * clear it agian by set the interrupt flag bit
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
static void Adc_vidClearInterruptFlag(void);

void Adc_vidInit(void)
{
	ADMUX = (ADC_u8CH_0|ADC_u8RIGHT_ADJUSTMENT|ADC_u8AVCC);
	ADCSRA = (ADC_u8INIT_CONTROL|ADC_u8CONVERSION_CONTROL|ADCSRA_FREE_RUNNING|ADC_u8DIVISION_FACTOR_8|ADC_u8ENABLE_INTERRUPT);
	SFIOR &=ADC_u8AUTO_TRIGGER_SOURCE ;// I make the macro ones to the bits that I don't need to change its state
									  // so I use &
}

void Adc_vidControl(u8 copy_control)
{
#if ADC_u8CONTROL == ADC_u8ENABLE
	SET_BIT(ADCSRA,7);
#elif ADC_u8CONTROL == ADC_u8DISABLE
	CLR_BIT(ADCSRA,7);

#endif
}

void Adc_vidStartConversion(void)
{
	SET_BIT(ADCSRA,ADC_u8START_CONVERSION);
}

u16 Adc_u16GetResult(void)
{
	while(Adc_u8GetInterruptFlagValue()==0);
	Adc_vidClearInterruptFlag();
	u16 Loc_RegValue = (ADCL | (ADCH <<8)) ;
	return Loc_RegValue;
}

u8 Adc_u8GetInterruptFlagValue(void)
{
	return GET_BIT(ADCSRA,4);
}

static void Adc_vidClearInterruptFlag(void)
{
	SET_BIT(ADCSRA,4);
}

























//Adc_tenuErrorStatus Adc_enuInit(void)
//{
//	u16 Loc_u16Result=0;
//	ADMUX = 0b01000000;
//	ADCSRA = 0b10000000;
//	while(1)
//	{
//		SET_BIT(ADCSRA,6);
//		while(GET_BIT(ADCSRA,4)==0);
//		Loc_u16Result = (ADCL)|(ADCH<<8);
//		SET_BIT(ADCSRA,4);
//	}
//}
//void Adc_vidInit(void)
//{
//	CLR_BIT(ADMUX,7);  // for select Vref
//	SET_BIT(ADMUX,6);  //for select Vref
//	CLR_BIT(ADMUX,5);  // clearing ADLAR for right adjustment
//	CLR_BIT(ADMUX,4);
//	CLR_BIT(ADMUX,3);
//	CLR_BIT(ADMUX,2);  //dol keda 5lloni 23ml select l ADC0
//	CLR_BIT(ADMUX,1);
//	CLR_BIT(ADMUX,0);
//
//
//	SET_BIT(ADCSRA,7); // b3ml enable ll ADC
//	CLR_BIT(ADCSRA,6); // initialli htb2a b zero w lma 23ml start conversion hya automatically htb2a b one
//	CLR_BIT(ADCSRA,5); // 2na b2oloh 2n feh 7ad tani hy5lek t3ml auto trigger w 2l 7ad dah 2na 2ll b5taroh mmkn ykon timer bas 7alyn 2na 3mlha disable
//	SET_BIT(ADCSRA,4); // flag interrupt
//	CLR_BIT(ADCSRA,3);  // enable PIE interrupt bta3 2l ADC
//	CLR_BIT(ADCSRA,2); // dol y3ni prescalaer 2ni 2asamt 3la 8
//	SET_BIT(ADCSRA,1);
//	SET_BIT(ADCSRA,0);
//
//
//}
//u16 Adc_u16GetResult(void)
//{
//	u16 Digital_Value;
//	SET_BIT(ADCSRA,6);
//	while(GET_BIT(ADCSRA,4)==0);  // b3ml check 3la 2l flag
//	SET_BIT(ADCSRA,4);    // ADIF baktb feh wa7d 34an 23mloh clear
//	Digital_Value=ADCL;
//	Digital_Value |=(ADCH<<8);
//
//	return Digital_Value ;
//}

/*
 * Adc.c
 *
 *  Created on: Mar 25, 2022
 *      Author: Abdelrahman Yousry
 */

#include "Std_types.h"
#include "Bit_utils.h"
#include "Adc.h"
#include "Adc_cfg.h"
#include "Adc_prv.h"
#include "avr/io.h"


void Adc_vidInit(void)
{
	ADMUX = (ADC_u8CH_0|ADC_u8RIGHT_ADJUSTMENT|ADC_u8AVCC);
	ADCSRA = (ADC_u8INIT_CONTROL|ADC_u8CONVERSION_CONTROL|ADCSRA_AUTO_TRIG_DISABLE|ADC_u8DIVISION_FACTOR_8|ADC_u8DISABLE_INTERRUPT);
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
	while(Adc_u8GetInterruptFlagValue()==1);
}

u16 Adc_u16GetResult(void)
{
	u16 Loc_RegValue = (ADCL | (ADCH <<8)) ;
	return Loc_RegValue;
}

u8 Adc_u8GetInterruptFlagValue(void)
{
	return GET_BIT(ADCSRA,4);
}

/*I let this function seperated to not obligate the user to make the polling technique
 * because if he enables ADC interrupt this bit will be cleared by hardware
 * */
void Adc_vidClearInterruptFlag(void)
{
	SET_BIT(ADCSRA,4);
}




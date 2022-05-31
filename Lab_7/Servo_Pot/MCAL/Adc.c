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
	ADMUX = (ADC_CHANNEL|ADC_ADJUSTMENT|ADC_VOLTAGE_REF);
	ADCSRA = (ADC_u8CONTROL|ADC_u8CONVERSION_CONTROL|ADCSRA_AUTO_TRIG_DISABLE|ADC_PRESCALER|ADC_u8INTERRUPT);
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
//	SET_BIT(PORTA,1);
	SET_BIT(ADCSRA,ADC_u8START_CONVERSION);
}

u16 Adc_u16GetResult(void)
{
	while(Adc_u8GetInterruptFlagValue()==0);
//	SET_BIT(PORTA,1);
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




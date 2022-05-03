/*
 * Gpt.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Bit_utils.h"
#include "Registers_prv.h"
#include <avr/interrupt.h>
#include "Gpt.h"
#include "Gpt_prv.h"
#include "Port.h"

#define MODE_CLEAR_MASK 	0x48

#define CLK_CLEAR_MASK 		0x07

#define MAX_VALUE_TIMER0	0xff
#define MAX_VALUE_TIMER1	0xffff
#define MAX_VALUE_TIMER2	0xff

static u8 Gpt_u8arrClk_Prescaler[3];

static pfunc CallBackfunc[3];

Gpt_tenuErrorStatus Gpt_Init(const Gpt_ConfigType* copy_TimeCfg)
{
	Gpt_tenuErrorStatus Loc_enuErrorStatus=Gpt_enuOk;
	if(copy_TimeCfg == NULL)
	{
		Loc_enuErrorStatus = Gpt_enuNullPointerException;
	}
	/**/
	else
	{
		switch (copy_TimeCfg->Gpt_ChannelNo)
		{
		case Channel_0:
			TCNT0=0;
			TIMSK=(copy_TimeCfg->Gpt_u8OvfInterruptControl|copy_TimeCfg->Gpt_u8OcmInterruptControl);
			TCCR0=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl|copy_TimeCfg->Gpt_WaveGenerationMode);
			Gpt_u8arrClk_Prescaler[Channel_0]=copy_TimeCfg->Gpt_u8Clk;
			copy_TimeCfg->Gpt_ChannelNo = 2;


			break;
		case Channel_1:
			TCCR1A=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl);
			TCCR1B=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl);
			TCNT1L=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl);
			TCNT1H=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl);
			TIMSK=(copy_TimeCfg->Gpt_u8OvfInterruptControl|copy_TimeCfg->Gpt_u8OcmInterruptControl);
			Gpt_u8arrClk_Prescaler[Channel_1]=copy_TimeCfg->Gpt_u8Clk;
			break;
		case Channel_2:
			TCCR2=(copy_TimeCfg->Gpt_u8CompareOutputMode|copy_TimeCfg->Gpt_u8ForceOutComapreControl);
			TCNT2=(copy_TimeCfg->Gpt_u8OvfInterruptControl|copy_TimeCfg->Gpt_u8OcmInterruptControl);
			Gpt_u8arrClk_Prescaler[Channel_2]=copy_TimeCfg->Gpt_u8Clk;
			break;
		}
	}
	return Loc_enuErrorStatus;
}


// no
Gpt_tenuErrorStatus Gpt_StartTimer(Gpt_ConfigType* copy_TimeCfg,  u16 Value)
{
	Gpt_tenuErrorStatus Loc_enuErrorStatus= Gpt_enuOk;
	switch(copy_TimeCfg->Gpt_ChannelNo)
	{
	case Channel_0:
		if(Value > MAX_VALUE_TIMER0)
		{
			Loc_enuErrorStatus = Gpt_enuWrongParamValue;
		}
		else
		{
			if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_NORMAL)
			{
				TCNT0 = 255-Value;
				TCCR0 |= Gpt_u8arrClk_Prescaler[Channel_0];
			}
			else if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_CTC){//clear timer on compare match
				OCR0 = Value;// this value will be the overflow value
				TCCR0 |= Gpt_u8arrClk_Prescaler[Channel_0];
			}
			else
			{
				Loc_enuErrorStatus=Gpt_enuWrongMode;
			}
		}
		break;

	case Channel_1:
		if(Value > MAX_VALUE_TIMER1)
		{
			Loc_enuErrorStatus = Gpt_enuWrongParamValue;
		}
		else
		{
			if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_NORMAL)
			{
				TCNT1 = 65536-Value;
				//			TCNT1 = value &0xFF00 ;
				TCCR1B |= Gpt_u8arrClk_Prescaler[Channel_1];
			}
			else if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_CTC){//clear timer on compare match
				OCR1A = Value;// this value will be the overflow value
				TCCR0 |= Gpt_u8arrClk_Prescaler[Channel_1];
			}
		}
		break;

	case Channel_2:
		if(Value > MAX_VALUE_TIMER2)
		{
			Loc_enuErrorStatus = Gpt_enuWrongParamValue;
		}
		else
		{
			if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_NORMAL)
			{
				TCNT2 = 255-Value;
				TCCR2 |= Gpt_u8arrClk_Prescaler[Channel_0];
			}
			else if((copy_TimeCfg->Gpt_WaveGenerationMode)==GPT_MODE_CTC){//clear timer on compare match
				OCR2 = Value;// this value will be the overflow value
				TCCR2 |= Gpt_u8arrClk_Prescaler[Channel_0];
			}
			else
			{
				Loc_enuErrorStatus=Gpt_enuWrongMode;
			}
		}
		break;

	default:

		break;
	}
	/******************************************xxxxxxxxxxxxxxxxxxxxxxxxx*****************************/
	/*enable General Interrupt*/
	SREG |= (1 << 7);
	return Loc_enuErrorStatus;
}


void Gpt_StopTimer(Gpt_ChannelNum Channel)
{
	switch(Channel)
	{
	case Channel_0:
		TCCR0 &=~(CLK_CLEAR_MASK);
		TCCR0 |= GPT_NO_CLK_SRC;
		break;
	case Channel_1:
		TCCR1B &=~(CLK_CLEAR_MASK);
		TCCR1B |= GPT_NO_CLK_SRC;
		break;
	case Channel_2:
		TCCR2 &=~(CLK_CLEAR_MASK);
		TCCR2 |=GPT_NO_CLK_SRC;
		break;

	default:

		break;
	}
}


u16 Gpt_GetTimeElapsed (Gpt_ChannelNum Channel)
{
	u16 value =0;
	switch(Channel)
	{
	case Channel_0:
		value=TCNT0;
		break;
	case Channel_1:
		value=TCNT1H | TCNT1L;
		break;
	case Channel_2:
		value=TCNT2;
		break;

	default:

		break;
	}
	return value ;
}
u16 Gpt_GetTimeRemaining (Gpt_ChannelNum Channel)
{
	u16 value =~(0);
	switch(Channel)
	{
	case Channel_0:
		value=(u8)value-TCNT0;
		break;
	case Channel_1:
		value=value-(TCNT1H | TCNT1L);
		break;
	case Channel_2:
		value=(u8)value-TCNT2;
		break;

	default:

		break;
	}
	return value ;
}

Gpt_tenuErrorStatus Gpt_vidRegisterCbf(pfunc CallBackFn,Gpt_ChannelNum channel){
	Gpt_tenuErrorStatus Loc_enuStatusError = Gpt_enuOk;
	switch (channel)
	{
	case Channel_0:
		if(CallBackFn)
		{
			CallBackfunc[channel] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_1:
		if(CallBackFn)
		{
			CallBackfunc[channel] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_2:
		if(CallBackFn)
		{
			CallBackfunc[channel] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;

	}
	return Loc_enuStatusError ;
}


ISR(TIMER0_OVF_vect)
{
	CallBackfunc[Channel_0]();
	//	SET_BIT(PORTA,PORT_u8PIN_1);
}
ISR(TIMER1_OVF_vect)
{
	//	static u16 Loc_u16No_of_ovf=0;
	CallBackfunc[Channel_1]();
}
ISR(TIMER2_OVF_vect)
{
	//	static u16 Loc_u16No_of_ovf=0;
	CallBackfunc[Channel_2]();
}

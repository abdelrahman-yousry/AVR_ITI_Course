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



static u8 Gpt_u8arrClk_Prescaler[3];
static u8 Gpt_u8CtcModeFlag[3]={0};
static pfunc Ovf_CallBackfunc[3];
static pfunc Ocm_CallBackfunc[4];

Gpt_tenuErrorStatus Gpt_Init(Gpt_ConfigType* copy_TimeCfg){
	Gpt_tenuErrorStatus Loc_enuErrorStatus=Gpt_enuOk;
	u16 TempVar;
	if(copy_TimeCfg == NULL)
	{
		Loc_enuErrorStatus = Gpt_enuNullPointerException;
	}
	else if((copy_TimeCfg->Gpt_WaveGenerationMode&MODE_VALIDATION)!=MODE_VALIDATION)
	{
		Loc_enuErrorStatus=Gpt_enuWrongMode;
	}
	/**/
	else
	{
		u8 Mode = (u8)copy_TimeCfg->Gpt_WaveGenerationMode;
		switch (copy_TimeCfg->Gpt_ChannelNo)
		{
		case Channel_0:
			TCNT0=((u8)copy_TimeCfg->Gpt_u16TimerInitialValue);
			TempVar = TCCR0;
			TempVar &= MODE_CLEAR_MASK ;	// will be &=
			TempVar |= ((u8)copy_TimeCfg->Gpt_u8CompareOutputMode|Mode);
			TCCR0 = TempVar;
			TIMSK |=(copy_TimeCfg->Gpt_u8OvfInterruptControl|copy_TimeCfg->Gpt_u8OcmInterruptControl);
			Gpt_u8arrClk_Prescaler[Channel_0]=copy_TimeCfg->Gpt_u8Clk;
			if(copy_TimeCfg->Gpt_u8CompareOutputMode == GPT_MODE_TIM_02_CTC)
			{

				Gpt_u8CtcModeFlag[0]=1;
			}
			break;
		case Channel_1:
			TCCR1A=(copy_TimeCfg->Gpt_u8CompareOutputMode);
			TCCR1B=Mode;
			TCNT1=(copy_TimeCfg->Gpt_u16TimerInitialValue);
			TIMSK=(copy_TimeCfg->Gpt_u8OvfInterruptControl)|(copy_TimeCfg->Gpt_u8OcmInterruptControl);//sGpt_u8OcmInterruptControl should have two macros| with each other
			Gpt_u8arrClk_Prescaler[Channel_1]=copy_TimeCfg->Gpt_u8Clk;
			if((u8)copy_TimeCfg->Gpt_u8CompareOutputMode == (u8)GPT_MODE_TIM1_CTC)
			{
				Gpt_u8CtcModeFlag[1]=1;
			}
			break;
		case Channel_2:
			TCNT2=((u8)copy_TimeCfg->Gpt_u16TimerInitialValue);
			TempVar = TCCR2;
			TempVar &= MODE_CLEAR_MASK ;	// will be &=
			TempVar |= (copy_TimeCfg->Gpt_u8CompareOutputMode|Mode);
			TCCR2 = TempVar;
			TIMSK|=(copy_TimeCfg->Gpt_u8OvfInterruptControl|copy_TimeCfg->Gpt_u8OcmInterruptControl);
			Gpt_u8arrClk_Prescaler[Channel_2]=copy_TimeCfg->Gpt_u8Clk;
			if(copy_TimeCfg->Gpt_u8CompareOutputMode == GPT_MODE_TIM_02_CTC)
			{
				Gpt_u8CtcModeFlag[2]=1;
			}
			break;
		}
	}
	return Loc_enuErrorStatus;
}


// no
Gpt_tenuErrorStatus Gpt_StartTimer(Gpt_ChannelNum copy_enuCh_Num,  u16 Value)
{
	Gpt_tenuErrorStatus Loc_enuErrorStatus= Gpt_enuOk;
	u8 TempVar;

	switch(copy_enuCh_Num)
	{
	case Channel_0:
		if(Value > MAX_VALUE_TIMER0)
		{
			Loc_enuErrorStatus = Gpt_enuWrongParamValue;
		}
		else
		{
			if(Gpt_u8CtcModeFlag[0]==1)
			{
				//clear timer on compare match
				OCR0 = Value;// this value will be the overflow value
				TempVar = TCCR0;
				TempVar &=~ CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_0];
				TCCR0 = TempVar;
			}
			else
			{
				TCNT0 = Value;
				TempVar = TCCR0;
				TempVar &=~ CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_0];
				TCCR0 = TempVar;
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
			if(Gpt_u8CtcModeFlag[1]==1)
			{
				//clear timer on compare match
				OCR1A = Value;// this value will be the overflow value
				TCNT1 =Value;
				TempVar=TCCR1B;
				TempVar&=~CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_1];
				TCCR1B=TempVar;

			}

			else
			{
				TCNT1 =Value;
				TempVar=TCCR1B;
				TempVar&=~CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_1];
				TCCR1B=TempVar;
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
			if(Gpt_u8CtcModeFlag[2]==1)
			{
				//clear timer on compare match
				OCR2 = Value;// this value will be the overflow value
				TempVar = TCCR2;
				TempVar &=~ CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_0];
				TCCR2 = TempVar;

			}
			else
			{
				TCNT2 = Value;
				TempVar = TCCR2;
				TempVar &=~ CLK_CLEAR_MASK;
				TempVar |= Gpt_u8arrClk_Prescaler[Channel_0];
				TCCR2 = TempVar;
			}
		}
		break;

	default:

		break;
	}

	return Loc_enuErrorStatus;
}


void Gpt_StopTimer(Gpt_ChannelNum Channel)
{
	switch(Channel)
	{
	case Channel_0:
		TCCR0 &=~(CLK_CLEAR_MASK);
		break;
	case Channel_1:
		TCCR1B &=~(CLK_CLEAR_MASK);
		break;
	case Channel_2:
		TCCR2 &=~(CLK_CLEAR_MASK);
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
		value=TCNT1;
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
		if(Gpt_u8CtcModeFlag[Channel_0]==1)
		{
			value=OCR0-TCNT0;
		}
		else
		{
			value=(u8)value-TCNT0;
		}
		break;
	case Channel_1:
		if(Gpt_u8CtcModeFlag[Channel_1]==1)
		{
			value=value-TCNT1;		}
		else
		{
			value=OCR1A-TCNT1;
		}
		break;
	case Channel_2:
		if(Gpt_u8CtcModeFlag[Channel_2]==1)
		{
			value=value-TCNT2;
		}
		else
		{
			value=OCR1A-TCNT2;
		}
		break;

	default:

		break;
	}
	return value ;
}

Gpt_tenuErrorStatus Gpt_vidRegisterOvfCbf(pfunc CallBackFn,Gpt_ChannelNum channel){
	Gpt_tenuErrorStatus Loc_enuStatusError = Gpt_enuOk;
	switch (channel)
	{
	case Channel_0:
		SET_BIT(PORTA,PORT_u8PIN_1);
		if(CallBackFn)
		{
			SET_BIT(PORTA,PORT_u8PIN_1);
			Ovf_CallBackfunc[Channel_0] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_1:
		if(CallBackFn)
		{
			Ovf_CallBackfunc[Channel_1] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_2:
		if(CallBackFn)
		{
			Ovf_CallBackfunc[Channel_2] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	default:

		break;
	}
	return Loc_enuStatusError ;
}
Gpt_tenuErrorStatus Gpt_vidRegisterOcmCbf(pfunc CallBackFn,Gpt_ChannelNum channel){
	Gpt_tenuErrorStatus Loc_enuStatusError = Gpt_enuOk;
	switch (channel)
	{
	case Channel_0:
		if(CallBackFn)
		{
			Ocm_CallBackfunc[Channel_0] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_1:
		if(CallBackFn)
		{
			Ocm_CallBackfunc[Channel_1] = CallBackFn;
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case 3:
		if(CallBackFn)
		{
			Ocm_CallBackfunc[3] = CallBackFn;//Timer1B
		}
		else
		{
			Loc_enuStatusError = Gpt_enuNullPointerException;
		}
		break;
	case Channel_2:
		if(CallBackFn)
		{
			Ocm_CallBackfunc[Channel_2] = CallBackFn;
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
	Ovf_CallBackfunc[Channel_0]();
	//		SET_BIT(PORTA,PORT_u8PIN_1);
}
ISR(TIMER1_OVF_vect)
{
	//	static u16 Loc_u16No_of_ovf=0;
	Ovf_CallBackfunc[Channel_1]();
}
ISR(TIMER2_OVF_vect)
{
	//	static u16 Loc_u16No_of_ovf=0;
	Ovf_CallBackfunc[Channel_2]();
}

ISR(TIMER0_COMP_vect)
{
	Ocm_CallBackfunc[Channel_0]();
}
ISR(TIMER1_COMPA_vect)
{
	Ocm_CallBackfunc[Channel_1]();
}
ISR(TIMER1_COMPB_vect)
{
	Ocm_CallBackfunc[3]();//Timer1B
}
ISR(TIMER2_COMP_vect)
{
	Ocm_CallBackfunc[Channel_2]();
}

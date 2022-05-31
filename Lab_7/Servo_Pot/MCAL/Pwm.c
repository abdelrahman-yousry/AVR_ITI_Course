/*
 * Pwm.c
 *
 *  Created on: May 21, 2022
 *      Author: Abdelrahman Yousry
 */
#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include "../Services/Registers_prv.h"
#include <avr/interrupt.h>
#include "Pwm.h"
#include "Pwm_prv.h"

static u8 Pwm_u8arrClk_Prescaler[MAX_NUM_OF_PRESCALERS_CLK];
static u8 Pwm_u8CtcModeFlag[3]={0};
static pfunc Ovf_CallBackfunc[MAX_NUM_OF_OVF_CHANNELS];
static pfunc Ocm_CallBackfunc[MAX_NUM_OF_OCM_CHANNELS];

Pwm_tenuErrorStatus Pwm_vidInit(Pwm_ConfigType* copy_TimeCfg)
{
	Pwm_tenuErrorStatus Loc_enuErrorStatus;
	u8 TempVar;
	if (copy_TimeCfg == NULL)
	{
		Loc_enuErrorStatus = Pwm_enuNullPtr;
	}

	switch(copy_TimeCfg->Pwm_SourceNo)
	{
	case Pwm_enuSource0:
		TempVar = TCCR0;
		TempVar &= MODE_CLEAR_MASK ;	// will be &=
		TempVar |= (copy_TimeCfg->Pwm_u16CompareOutputMode|copy_TimeCfg->Pwm_WaveGenerationMode);
		TCCR0 = TempVar;
		TIMSK |=(copy_TimeCfg->Pwm_u8OvfInterruptControl|copy_TimeCfg->Pwm_u8OcmInterruptControl);
		Pwm_u8arrClk_Prescaler[Pwm_enuSource0]=copy_TimeCfg->Pwm_u8Clk;
		break;
	case Pwm_enuSource1:
		TempVar = TCCR1A ;
		TempVar |= (copy_TimeCfg->Pwm_WaveGenerationMode&PWM_TCCR1A_WGM_CLEAR_MASK);
		TempVar |= (copy_TimeCfg->Pwm_u16CompareOutputMode);
		TCCR1A = TempVar;
		TempVar = TCCR1B;
		TempVar |= (copy_TimeCfg->Pwm_WaveGenerationMode&PWM_TCCR1B_WGM_CLEAR_MASK);
		Pwm_u8arrClk_Prescaler[Pwm_enuSource1]=copy_TimeCfg->Pwm_u8Clk;
		TCCR1B=TempVar;
		break;
	case Pwm_enuSource2:
		TempVar = TCCR2;
		TempVar &= MODE_CLEAR_MASK ;	// will be &=
		TempVar |= (copy_TimeCfg->Pwm_u16CompareOutputMode|copy_TimeCfg->Pwm_WaveGenerationMode);
		TCCR2 = TempVar;
		TIMSK |=(copy_TimeCfg->Pwm_u8OvfInterruptControl|copy_TimeCfg->Pwm_u8OcmInterruptControl);
		Pwm_u8arrClk_Prescaler[Pwm_enuSource2]=copy_TimeCfg->Pwm_u8Clk;
		break;
	}

	return Loc_enuErrorStatus;
}

Pwm_tenuErrorStatus Pwm_StartTimer(Pwm_ChannelNum copy_enuCh_Num,  u16 Value)
{
	Pwm_tenuErrorStatus Loc_enuErrorStatus;
	u8 TempVar;

	switch(copy_enuCh_Num)
	{
	case Channel_0:
		if(Value > MAX_VALUE_TIMER0)
		{
			Loc_enuErrorStatus = Pwm_enuWrongParamValue;
		}
		else
		{

			OCR0 = Value;
			TempVar = TCCR0;
			TempVar &=~ CLK_CLEAR_MASK;
			TempVar |= Pwm_u8arrClk_Prescaler[Pwm_enuSource0];
			TCCR0 = TempVar;

		}
		break;

	case Channel_1A:
		if(Value > MAX_VALUE_TIMER1)
		{
			Loc_enuErrorStatus = Pwm_enuWrongParamValue;
		}
		else
		{
//			SET_BIT(PORTA,0);
			OCR1A = Value;
			TempVar=TCCR1B;// this Reg which have the CLK bits
			TempVar&=~CLK_CLEAR_MASK;
			TempVar |= Pwm_u8arrClk_Prescaler[Pwm_enuSource1];
			TCCR1B=TempVar;

		}
		break;
	case Channel_1B:
		if(Value > MAX_VALUE_TIMER1)
		{
			Loc_enuErrorStatus = Pwm_enuWrongParamValue;
		}
		else
		{
			OCR1B = Value;
			TempVar=TCCR1B;// this Reg which have the CLK bits
			TempVar&=~CLK_CLEAR_MASK;
			TempVar |= Pwm_u8arrClk_Prescaler[Pwm_enuSource1];
			TCCR1B=TempVar;

		}
		break;

	case Channel_2:
		if(Value > MAX_VALUE_TIMER2)
		{
			Loc_enuErrorStatus = Pwm_enuWrongParamValue;
		}
		else
		{
			OCR2 = Value;
			TempVar = TCCR2;
			TempVar &=~ CLK_CLEAR_MASK;
			TempVar |= Pwm_u8arrClk_Prescaler[Pwm_enuSource2];
			TCCR2 = TempVar;
		}
		break;

	default:

		break;
	}
	return Loc_enuErrorStatus;
}

Pwm_tenuErrorStatus Pwm_enuSetOutCompareMatchVal(Pwm_ChannelNum copy_enuCh_Num,  u16 Value)
{
	Pwm_tenuErrorStatus Loc_enuErrorStatus= Pwm_enuOk;
	switch(copy_enuCh_Num)
	{
	case Channel_0:
		OCR0 = (u8)Value;
		break;
	case Channel_1A:
		OCR1A = Value;
		break;
	case Channel_1B:
		OCR1B = Value;
		break;
	case Channel_2:
		OCR2 = (u8)Value;
		break;
	}
	return Loc_enuErrorStatus;
}


void Pwm_enuSetIcrVal(u16 Copy_u16Val)
{
	ICR1 = Copy_u16Val;
}


void Pwm_StopTimer(Pwm_enuSourceNum Channel)
{
	switch(Channel)
	{
	case Pwm_enuSource0:
		TCCR0 &=~(CLK_CLEAR_MASK);
		break;
	case Pwm_enuSource1:
		TCCR1B &=~(CLK_CLEAR_MASK);
		break;
	case Pwm_enuSource2:
		TCCR2 &=~(CLK_CLEAR_MASK);
		break;

	default:
		break;
	}
}

Pwm_tenuErrorStatus Pwm_enuRegisterOvfCbf(pfunc CallBackFn,Pwm_enuSourceNum Pwm_SrcNum)
{
	Pwm_tenuErrorStatus Loc_enuStatusError = Pwm_enuOk;

	if(CallBackFn)
	{

		Ovf_CallBackfunc[Pwm_SrcNum] = CallBackFn;
	}
	else
	{
		Loc_enuStatusError = Pwm_enuNullPtr;
	}
	return Loc_enuStatusError ;
}

Pwm_tenuErrorStatus Pwm_enuRegisterOcmCbf(pfunc CallBackFn,Pwm_ChannelNum Pwm_SrcNum)
{
	Pwm_tenuErrorStatus Loc_enuStatusError = Pwm_enuOk;

	if(CallBackFn)
	{

		Ocm_CallBackfunc[Pwm_SrcNum] = CallBackFn;
	}
	else
	{
		Loc_enuStatusError = Pwm_enuNullPtr;
	}
	return Loc_enuStatusError ;
}

ISR(TIMER0_OVF_vect)
{
	if(Ovf_CallBackfunc[Pwm_enuSource0])
	{
		Ovf_CallBackfunc[Pwm_enuSource0]();
	}
	//		SET_BIT(PORTA,PORT_u8PIN_1);
}
ISR(TIMER1_OVF_vect)
{
	if(Ovf_CallBackfunc[Pwm_enuSource1])
	{
		//	static u16 Loc_u16No_of_ovf=0;
		Ovf_CallBackfunc[Pwm_enuSource1]();
	}
}
ISR(TIMER2_OVF_vect)
{
	if(Ovf_CallBackfunc[Pwm_enuSource2])
	{
		//	static u16 Loc_u16No_of_ovf=0;
		Ovf_CallBackfunc[Pwm_enuSource2]();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(Ocm_CallBackfunc[Channel_0])
	{
		//			SET_BIT(PORTA,PORT_u8PIN_0);
		Ocm_CallBackfunc[Channel_0]();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(Ocm_CallBackfunc[Channel_1A])
	{
		//SET_BIT(PORTA,PORT_u8PIN_0);
		Ocm_CallBackfunc[Channel_1A]();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(Ocm_CallBackfunc[Channel_1B])
	{
		//SET_BIT(PORTA,PORT_u8PIN_0);
		Ocm_CallBackfunc[Channel_1B]();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(Ocm_CallBackfunc[Channel_2])
	{
		Ocm_CallBackfunc[Channel_2]();
	}
}

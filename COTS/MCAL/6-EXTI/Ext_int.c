/*
 * Ext_int.c
 *
 *  Created on: April 25, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Registers_prv.h"
#include "Ext_Int.h"
#include "Ext_prv.h"
#include <avr/interrupt.h>

pcbf Ext_IntCbf[3];
Ext_tenuErrorStatus Ext_enuInit(Ext_tstrCfg* Ext_strCfg)
{
	Ext_tenuErrorStatus Loc_ErrorStatus;
	u8 TempVar;
	if (Ext_strCfg->Ext_NUM>Ext_MaxNum)
	{
		Loc_ErrorStatus= Ext_InvalidIntNum;
	}
	else
	{
		switch((u8)Ext_strCfg->Ext_NUM)
		{
		case Ext_INT_0:
			TempVar = MCUCR;
			TempVar&=EXT_u8INT0_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntSenseCtrl;
			MCUCR=TempVar;
			TempVar=GICR;
			TempVar&=EXT_u8INT_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntCtrl;
			GICR=TempVar;
			break;
		case Ext_INT_1:
			TempVar = MCUCR;
			TempVar&=EXT_u8INT1_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntSenseCtrl;
			MCUCR=TempVar;
			TempVar=GICR;
			TempVar&=EXT_u8INT_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntCtrl;
			GICR=TempVar;
			break;
		case Ext_INT_2:
			TempVar = MCUCSR;
			TempVar&=EXT_u8INT1_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntSenseCtrl;
			MCUCSR=TempVar;
			TempVar=GICR;
			TempVar&=EXT_u8INT_CLEAR_MASK;
			TempVar=Ext_strCfg->Ext_u8IntCtrl;
			GICR=TempVar;
			break;
		}

	}
	return Loc_ErrorStatus;
}

Ext_tenuErrorStatus Ext_enuIntEnable(Ext_enuNum Ext_enuIntNum)
{
	Ext_tenuErrorStatus Loc_ErrorStatus=Ext_enuOk;
	if (Ext_enuIntNum>Ext_MaxNum)
	{
		Loc_ErrorStatus= Ext_InvalidIntNum;
	}
	else
	{
		switch(Ext_enuIntNum)
		{
		case Ext_INT_0:
			GICR|=EXT_INT0_ENABLE;
			break;
		case Ext_INT_1:
			GICR|=EXT_INT1_ENABLE;
			break;
		case Ext_INT_2:
			GICR|=EXT_INT2_ENABLE;
			break;
		}
	}
	return Loc_ErrorStatus;
}
Ext_tenuErrorStatus Ext_enuIntDisable(Ext_enuNum Ext_enuIntNum)
{
	Ext_tenuErrorStatus Loc_ErrorStatus=Ext_enuOk;
	if (Ext_enuIntNum>Ext_MaxNum)
	{
		Loc_ErrorStatus= Ext_InvalidIntNum;
	}
	else
	{
		switch(Ext_enuIntNum)
		{
		case Ext_INT_0:
			GICR&=~(EXT_INT_DISABLE<<6);
			break;
		case Ext_INT_1:
			GICR&=~(EXT_INT_DISABLE<<7);
			break;
		case Ext_INT_2:
			GICR&=~(EXT_INT_DISABLE<<5);
			break;
		}
	}
	return Loc_ErrorStatus;
}

Ext_tenuErrorStatus Ext_enuRegCallBackFun(pcbf Copy_pcbf,Ext_enuNum Ext_enuIntNum)
{
	Ext_tenuErrorStatus Loc_ErrorStatus=Ext_enuOk;
	if(Copy_pcbf == NULL)
	{
		Loc_ErrorStatus =Ext_NullPtr;
	}
	else if (Ext_enuIntNum>Ext_MaxNum)
	{
		Loc_ErrorStatus= Ext_InvalidIntNum;
	}
	else{
		switch(Ext_enuIntNum)
		{
		case Ext_INT_0:
			Ext_IntCbf[Ext_INT_0]=Copy_pcbf;
			break;
		case Ext_INT_1:
			Ext_IntCbf[Ext_INT_1]=Copy_pcbf;
			break;
		case Ext_INT_2:
			Ext_IntCbf[Ext_INT_2]=Copy_pcbf;
			break;
		}
		return Loc_ErrorStatus;
	}
}

void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
	Ext_IntCbf[Ext_INT_0]();
}

void __vector_2(void) __attribute__((signal,used));
void __vector_2(void)
{
	Ext_IntCbf[Ext_INT_1]();
}

void __vector_3(void) __attribute__((signal,used));
void __vector_3(void)
{
	Ext_IntCbf[Ext_INT_2]();
}

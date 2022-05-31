/*
 * Servo.c
 *
 *  Created on: May 29, 2022
 *      Author: Abdelrahman Yousry
 */


#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../Services/Registers_prv.h"
#include "Serrvo.h"
#include "Servo_cfg.h"
#include "../MCAL/Pwm.h"


extern const Servo_tCfg Servo_Cfg[SERVO_MAX_NUM];

void Servo_vidInit(Servo_tCfg* Servo_strCfg)
{
	u8 iterator;
	Pwm_ConfigType Pwm_strCfg;
	s32 Mapping = 10.6 * Servo_strCfg->InitialAngle + 530;
	for (iterator=0; iterator<SERVO_MAX_NUM ; iterator++)
	{

		switch(Servo_strCfg->ChNum)
		{
		break;
		case Pwm_enuCh1A:
			Pwm_strCfg.Pwm_SourceNo=Pwm_enuSource1;
			Pwm_strCfg.Pwm_WaveGenerationMode=PWM_u8MODE_CH1_FAST_MODE_TOP_ICR1;
			Pwm_strCfg.Pwm_u16CompareOutputMode=PWM_u8TIM1_COM_CLR_OC1A;
			Pwm_strCfg.Pwm_u8Clk=PWM_CLK_CH_01_PRESCALER_8;
			Pwm_strCfg.Pwm_u8OcmInterruptControl=0;
			Pwm_strCfg.Pwm_u8OvfInterruptControl=0;
			Pwm_vidInit(&Pwm_strCfg);
			Pwm_StartTimer(Channel_1A,Mapping);
			break;
		case Pwm_enuCh1B:
			Pwm_strCfg.Pwm_SourceNo=Pwm_enuSource1;
			Pwm_strCfg.Pwm_WaveGenerationMode=PWM_u8MODE_CH1_FAST_MODE_TOP_ICR1;
			Pwm_strCfg.Pwm_u16CompareOutputMode=PWM_u8TIM1_COM_SET_OC1B;
			Pwm_strCfg.Pwm_u8Clk=PWM_CLK_CH_01_PRESCALER_8;
			Pwm_strCfg.Pwm_u8OcmInterruptControl=0;
			Pwm_strCfg.Pwm_u8OvfInterruptControl=0;
			Pwm_vidInit(&Pwm_strCfg);
			Pwm_StartTimer(Channel_1B,Mapping);
			break;
		}

		Pwm_enuSetIcrVal(20000);
	}
}


void Servo_vidSetAngle(u8 Motor_u8Name,u16 Servo_u16AngleVal)
{
	u32 MappingVal = 10.6 *Servo_u16AngleVal + 530 ;
	switch(Servo_Cfg[Motor_u8Name].ChNum)
	{
	case Pwm_enuCh1A:
		Pwm_enuSetOutCompareMatchVal(Channel_1A,MappingVal);
		break;
	case Pwm_enuCh1B:
		Pwm_enuSetOutCompareMatchVal(Channel_1B,MappingVal);
		break;
	}
}



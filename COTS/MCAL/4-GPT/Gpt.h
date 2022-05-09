/*
 * AVR_GPT_Driver.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Abdelrahman yousry
 */

#ifndef GPT_H_
#define GPT_H_

/********************************TCCR0/2Configuration****************************/
/*FORCE OUTPUT COMPARE --> works only in case non-pwm mode activated*/
#define GPT_FORCE_OUTPUT_COMPARE_ENABLED	0x80
#define GPT_FORCE_OUTPUT_COMPARE_DISABLED	0x00

/******************WAVE FORM GENERATION MODES' OPTIONS***************************/
/*Note: -
 * after clearing using MODE_CLEAR_MASK set these macros (|=)*/
#define GPT_MODE_TIM_02_NORMAL			0x0100
#define GPT_MODE_TIM_02_CTC				  0x0180

/*********************COMPARE OUTPUT MODE OPTIONS********************************/
/*IN CASE OF NON-PWM-MODE*/
#define GPT_u8COM_OC0_DISCONNECTED				0x00
#define GPT_u8COM_OC0_TOGGLE					    0x10
#define GPT_u8COM_OC0_CLEAR						    0x20
#define GPT_u8COM_OC0_SET						      0x30
/********************************************************************************/

/**************************TCCR1 Configuration***********************************/
/*********************COMPARE OUTPUT MODE OPTIONS********************************/
#define GPT_u8TIM1_COM_OC1A_DISCONNECTED		    0x00
#define GPT_u8TIM1_COM_TOGGLE_OC1A			        0x40
#define GPT_u8TIM1_COM_CLR_OC1A				          0x80
#define GPT_u8TIM1_COM_SET_OC1A				          0xC0
#define GPT_u8TIM1_COM_OC1B_DISCONNECTED		    0x00
#define GPT_u8TIM1_COM_TOGGLE_OC1B			        0x10
#define GPT_u8TIM1_COM_CLR_OC1B				          0x20
#define GPT_u8TIM1_COM_SET_OC1B				          0x30
/********************WAVE FORM GENERATION MODES' OPTIONS*************************/
#define GPT_MODE_TIM1_NORMAL					0x0100 // TCCR1A
#define GPT_MODE_TIM1_CTC						  0x0108 // TCCR1B // CTC



/********************************CLOCK SELECT Timer0/1/2********************************/
		//timer stopped
#define GPT_CLK_NO_PRESCALING					0x01
#define GPT_CLK_PRESCALER_8						0x02
#define GPT_CLK_PRESCALER_64					0x03
#define GPT_CLK_PRESCALER_256					0x04
#define GPT_CLK_PRESCALER_1024				0x05
#define GPT_CLK_EXT_FALLING_TIMER0		0x06		//count on falling edge on To pin
#define GPT_CLK_EXT_RISING_TIMER0			0x07		//count on rising edge on To pin

/*******************************Interrupt Control*****************************/

#define GPT_OVF_INT_CHANNEL_0_ENABLED				  0x01
#define GPT_ON_COMP_INT_CHANNEL_0_ENABLED			0x02
#define GPT_OVF_INT_CHANNEL_1_ENABLED				  0x04
#define GPT_ON_COMP_A_INT_CHANNEL_1_ENABLED		0x10
#define GPT_ON_COMP_B_INT_CHANNEL_1_ENABLED		0x08
#define GPT_OVF_INT_CHANNEL_2_ENABLED				  0x40
#define GPT_ON_COMP_INT_CHANNEL_2_ENABLED			0x80
#define GPT_INT_DISABLE								        0x00







/*********************************** Typedef ************************************/

typedef void(*pfunc)(void);

typedef enum
{
	Channel_0,
	Channel_1,
	Channel_2

}Gpt_ChannelNum;



typedef struct
{
	u8 Gpt_u8Clk;
	u8 Gpt_u8OvfInterruptControl;		//control ovf interrupt pin which is will go to isr when ovf is occured
	u8 Gpt_u8OcmInterruptControl;		//control interrupts OCm pin which is the go to isr when the compare value is reached
	u16 Gpt_u16CompareOutputMode;			//this is the wave generartion mode to select which mode the timer will be operated(normal/pwm/ctc ...)
	u16 Gpt_u16TimerInitialValue;   	//TCNT0/1A-!B/2
	u16 Gpt_WaveGenerationMode;
	Gpt_ChannelNum Gpt_ChannelNo;
}Gpt_ConfigType;
u8 Gpt_u8ChannelNum;
u8 Gpt_u8TimerMode;
u8 Gpt_u8CompareMatchOpMode;
u8 Gpt_u8ChannelPrescaller;
u8 Gpt_u8EnableInterrupts;

typedef enum
{
	Gpt_enuOk,
	Gpt_enuNullPointerException,
	Gpt_enuWrongParamValue,
	Gpt_enuWrongMode,

}Gpt_tenuErrorStatus;

/*********************************** Prototypes **********************************/

/**
 *Description: is used to Init timer
 *Input parameters :Gpt_ConfigType* copy_TimeCfg
 *					--> have the configuration of the timer to be initialized
 *
 * Return: the error status of the function, it has the following options
	1-Gpt_enuOk,
	2-Gpt_enuNullPointerException,
	3-Gpt_enuWrongParamValue,
 **/
Gpt_tenuErrorStatus Gpt_Init(Gpt_ConfigType* copy_TimeCfg);
/**
 *Description: is used to Start timer
*Input parameters :Gpt_ChannelNum Channel,  u16 Value
 *
 * Return: the error status of the function, it has the following options
	1-Gpt_enuOk,
	2-Gpt_enuNullPointerException,
	3-Gpt_enuWrongParamValue,
 **/
Gpt_tenuErrorStatus Gpt_StartTimer(Gpt_ChannelNum copy_enuCh_Num,  u16 Value)
;
/**
 *Description: is used to Stop timer
 *Input parameters :Gpt_ChannelNum Channel
 *
 * Return:void
 **/
void Gpt_StopTimer(Gpt_ChannelNum Channel);
/**
 *Description: is used to Set Output compare  match value in OCCRx and according to CTC mode
*Input parameters :Gpt_ChannelNum Channel,  u16 Value
 *
 * Return: the error status of the function, it has the following options
	1-Gpt_enuOk,
	2-Gpt_enuNullPointerException,
	3-Gpt_enuWrongParamValue,
 **/
Gpt_tenuErrorStatus Gpt_enuSetOutCompareMatchVal(Gpt_ChannelNum copy_enuCh_Num,  u16 Value);

/**
 *Description: is used to get time elapsed
 *Input parameters :Gpt_ChannelNum
 * Return: u16
 **/

u16  Gpt_GetTimeElapsed (Gpt_ChannelNum Channel);
/**
 *Description: is used to get time remaining
 *Input parameters :Gpt_ChannelNum
 * Return: u16
 **/
u16  Gpt_GetTimeRemaining (Gpt_ChannelNum Channel);

Gpt_tenuErrorStatus Gpt_enuRegisterOvfCbf(pfunc CallBackFn,Gpt_ChannelNum channel);
Gpt_tenuErrorStatus Gpt_enuRegisterOcmCbf(pfunc CallBackFn,Gpt_ChannelNum channel);
#endif /* GPT_H_ */

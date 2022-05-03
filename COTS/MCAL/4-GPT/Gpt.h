/*
 * AVR_GPT_Driver.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Abdelrahman yousry
 */

#ifndef GPT_H_
#define GPT_H_



/********************************TCCR0 Configuration****************************************/
/*FORCE OUTPUT COMPARE --> works only in case non-pwm mode activated*/
#define GPT_FORCE_OUTPUT_COMPARE_ENABLED	0x80
#define GPT_FORCE_OUTPUT_COMPARE_DISABLED	0x00


/*WAVE FORM GENERATION MODES' OPTIONS*/
/*Note: -
 * after clearing using MODE_CLEAR_MASK set these macros (|=)*/
#define GPT_MODE_NORMAL				0x00
//#define GPT_MODE_PWM				0x40
#define GPT_MODE_CTC				0x80
//#define GPT_MODE_FASTPWM			0x48



/*********************COMPARE OUTPUT MODE OPTIONS********************************/
/*IN CASE OF NON-PWM-MODE*/
#define GPT_COM_OC0_DISCONNECTED				0x00
#define GPT_COM_OC0_TOGGLE						0x10
#define GPT_COM_OC0_CLEAR						0x20
#define GPT_COM_OC0_SET							0x30


/********************************CLOCK SELECT Timer0********************************/
#define GPT_NO_CLK_SRC							0x00		//timer stopped
#define GPT_CLK_NO_PRESCALING					0x01
#define GPT_CLK_PRESCALER_8						0x02
#define GPT_CLK_PRESCALER_64					0x03
#define GPT_CLK_PRESCALER_256					0x04
#define GPT_CLK_PRESCALER_1024					0x05
#define GPT_CLK_EXT_FALLING_TIMER0				0x06		//count on falling edge on To pin
#define GPT_CLK_EXT_RISING_TIMER0				0x07		//count on rising edge on To pin


/*******************************Interrupt Control*****************************/

#define GPT_TOIE0_CHANNEL_0_ENABLED			0x01
#define GPT_TOIE0_CHANNEL_0_DISABLED		0x00
#define GPT_OCIE0_CHANNEL_0_ENABLED			0x02
#define GPT_OCIE0_CHANNEL_0_DISABLED		0x00
#define GPT_TOIE1_CHANNEL_1_ENABLED			0x04
#define GPT_TOIE1_CHANNEL_1_DISABLED		0x04
#define GPT_OCIE1A_CHANNEL_1_ENABLED		0x08
#define GPT_OCIE1A_CHANNEL_1_DISABLED		0x08
#define GPT_OCIE1B_CHANNEL_1_ENABLED		0x10
#define GPT_OCIE1B_CHANNEL_1_DISABLED		0x00
#define GPT_TOIE2_CHANNEL_2_ENABLED			0x04
#define GPT_TOIE2_CHANNEL_2_DISABLED		0x00
#define GPT_OCIE2_CHANNEL_2_ENABLED			0x80
#define GPT_OCIE2_CHANNEL_2_DISABLED		0x00


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
	u8 Gpt_u8OvfInterruptControl;		
	u8 Gpt_u8OcmInterruptControl;		
	u8 Gpt_u8CompareOutputMode;		
	u8 Gpt_u8ForceOutComapreControl;	
	u16 Gpt_u16OvfValue;   				
	u8 Gpt_WaveGenerationMode;
	Gpt_ChannelNum Gpt_ChannelNo;
}Gpt_ConfigType;


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
Gpt_tenuErrorStatus Gpt_StartTimer(Gpt_ConfigType* copy_TimeCfg,  u16 Value)
;
/**
 *Description: is used to Stop timer
 *Input parameters :Gpt_ChannelNum Channel
 *
 * Return:void
 **/
void Gpt_StopTimer(Gpt_ChannelNum Channel);
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

Gpt_tenuErrorStatus Gpt_vidRegisterCbf(pfunc CallBackFn,Gpt_ChannelNum channel);
#endif /* GPT_H_ */

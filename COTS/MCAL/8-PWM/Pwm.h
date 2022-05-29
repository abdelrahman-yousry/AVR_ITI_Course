/*
 * Pwm.h
 *
 *  Created on: May 21, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef PWM_H_
#define PWM_H_

/******************WAVE FORM GENERATION MODES' TIMER 0/2 OPTIONS***************************/
/*Note: -
 * after clearing using MODE_CLEAR_MASK set these macros (|=)*/
#define PWM_u8MODE_CH02_PHASE_CORRECT						0X48
#define PWM_u8MODE_CH02_FAST_PWM						    0X40

/*********************COMPARE OUTPUT MODE OPTIONS********************************/
/*IN CASE OF FAST_PWM and PHASE_CORRECT MODE*/
#define PWM_u8TIM02_COM_OC0_DISCONNECTED							0x00
#define PWM_u8TIM02_FAST_CLEAR_OC0_ON_COMP_SET_ON_TOP				0x20
#define PWM_u8TIM02_FAST_SET_OC0_ON_COMP_CLEAR_ON_TOP				0x30
#define PWM_u8TIM02_PHASE_CLEAR_OC0_ON_COMP_UP_SET_ON_COMP_DOWN		0x20
#define PWM_u8PHASE_SET_OC0_ON_COMP_UP_CLEAR_ON_COMP_DOWN			0x30




/***************************TCCR1 Configuration************************************/
/***********************COMPARE OUTPUT MODE OPTIONS********************************/
#define PWM_u8TIM1_COM_OC1A_DISCONNECTED		            0x00
#define PWM_u8TIM1_COM_TOGGLE_OC1A			                0x40
#define PWM_u8TIM1_COM_CLR_OC1A				                0x80
#define PWM_u8TIM1_COM_SET_OC1A				                0xC0
#define PWM_u8TIM1_COM_OC1B_DISCONNECTED		            0x00
#define PWM_u8TIM1_COM_TOGGLE_OC1B			                0x10
#define PWM_u8TIM1_COM_CLR_OC1B				                0x20
#define PWM_u8TIM1_COM_SET_OC1B				                0x30
/********************WAVE FORM GENERATION MODES'channel 1A and 1B OPTIONS********************************/
#define PWM_u8MODE_CH1_PHASE_CORRECT_8_BIT					0X01
#define PWM_u8MODE_CH1_PHASE_CORRECT_9_BIT					0X02
#define PWM_u8MODE_CH1_PHASE_CORRECT_10_BIT					0X03
#define PWM_u8MODE_CH1_FAST_MODE_8_BIT						0X09
#define PWM_u8MODE_CH1_FAST_MODE_9_BIT						0X0A
#define PWM_u8MODE_CH1_FAST_MODE_10_BIT						0X0B
#define PWM_u8MODE_CH1_PHASE_FREQUENY_CORRECT_TOP_OCR1A		0X11
#define PWM_u8MODE_CH1_PHASE_CORRECT_TOP_OCR1A				0X13
#define PWM_u8MODE_CH1_FAST_MODE_TOP_OCR1A					0X1B
#define PWM_u8MODE_CH1_PHASE_FREQUENCY_CORRECT_TOP_ICR1		0X10
#define PWM_u8MODE_CH1_PHASE_CORRECT_TOP_ICR1				0X12
#define PWM_u8MODE_CH1_FAST_MODE_TOP_ICR1					0X1A

/********************************CLOCK SELECT Timer0/1********************************/

#define PWM_CLK_CH_01_NO_PRESCALING					            0x01		//timer stopped
#define PWM_CLK_CH_01_PRESCALER_8						        0x02
#define PWM_CLK_CH_01_PRESCALER_64					            0x03
#define PWM_CLK_CH_01_PRESCALER_256					            0x04
#define PWM_CLK_CH_01_PRESCALER_1024					        0x05
#define PWM_CLK_CH_01_EXT_FALLING_TIMER0				        0x06		//count on falling edge on To pin
#define PWM_CLK_CH_01_EXT_RISING_TIMER0				            0x07		//count on rising edge on To pin

/********************************CLOCK SELECT Timer2********************************/
#define PWM_CLK_CH_2_NO_PRESCALING					            0x01		//timer stopped
#define PWM_CLK_CH_2_PRESCALER_8						        0x02
#define PWM_CLK_CH_2_PRESCALER_32					            0x03
#define PWM_CLK_CH_2_PRESCALER_64					            0x04
#define PWM_CLK_CH_2_PRESCALER_128					            0x05
#define PWM_CLK_CH_2_PRESCALER_256					            0x06		//count on falling edge on To pin
#define PWM_CLK_CH_2_PRESCALER_1024					            0x07		//count on rising edge on To pin


/*******************************Interrupt Control*****************************/

#define PWM_OVF_INT_CHANNEL_0_ENABLED				        0x01
#define PWM_ON_COMP_INT_CHANNEL_0_ENABLED			        0x02
#define PWM_OVF_INT_CHANNEL_1_ENABLED				        0x04
#define PWM_ON_COMP_A_INT_CHANNEL_1_ENABLED			        0x10
#define PWM_ON_COMP_B_INT_CHANNEL_1_ENABLED		            0x08
#define PWM_OVF_INT_CHANNEL_2_ENABLED				        0x40
#define PWM_ON_COMP_INT_CHANNEL_2_ENABLED			        0x80
#define PWM_INT_DISABLE							            0x00


typedef void(*pfunc)(void);

typedef enum
{
	Channel_0,
	Channel_1A,
	Channel_1B,
	Channel_2

}Pwm_ChannelNum;


typedef enum
{
	Pwm_enuSource0,
	Pwm_enuSource1,
	Pwm_enuSource2,
}Pwm_enuSourceNum;
typedef struct
{
	u8 Pwm_u8Clk;
	u8 Pwm_u8OvfInterruptControl;//control ovf interrupt pin which is will go to isr when ovf is occured
	u8 Pwm_u8OcmInterruptControl;//control interrupts OCm pin which is the go to isr when the compare value is reached
	u16 Pwm_u16CompareOutputMode;//this is the wave generation mode to select which mode the timer will be operated(normal/pwm/ctc ...)
	u16 Pwm_WaveGenerationMode;
	Pwm_ChannelNum Pwm_SourceNo;
}Pwm_ConfigType;

typedef enum
{
	Pwm_enuOk,
	Pwm_enuWrongParamValue,
	Pwm_enuNullPtr
}Pwm_tenuErrorStatus;




/*********************************** Prototypes **********************************/

/**
 *Description: is used to Init Pwm timer
 *Input parameters :Pwm_ConfigType* copy_TimeCfg
 *					--> have the configuration of the timer to be initialized
 *
 * Return: the error status of the function, it has the following options
	1-Pwm_enuOk,
	2-Pwm_enuNullPtr,
	3-Pwm_enuWrongParamValue,
 **/
Pwm_tenuErrorStatus Pwm_vidInit(Pwm_ConfigType* copy_TimeCfg);


/**
 *Description: is used to Start timer
 *Input parameters :Pwm_ChannelNum Channel,  u16 Value
 *
 * Return: the error status of the function, it has the following options
	1-Pwm_enuOk,
	2-Pwm_enuNullPtr,
	3-Pwm_enuWrongParamValue,
 **/
Pwm_tenuErrorStatus Pwm_StartTimer(Pwm_ChannelNum copy_enuCh_Num,  u16 Value);

/**
 *Description: is used to Set Output compare  match value in OCCRx and according to CTC mode
 *Input parameters :Pwm_ChannelNum Channel,  u16 Value
 *
 * Return: the error status of the function, it has the following options
	1-Pwm_enuOk,
	2-Pwm_enuNullPtr,
	3-Pwm_enuWrongParamValue,
 **/
Pwm_tenuErrorStatus Pwm_enuSetOutCompareMatchVal(Pwm_ChannelNum copy_enuCh_Num,  u16 Value);

/**
 *Description: is used to Set ICR value in ICR1
 *Input parameters :Pwm_ChannelNum Channel,  u16 Value
 *
 * Return: void
 **/
void Pwm_enuSetIcrVal(u16 Copy_u16Val);
/**
 *Description: is used to Stop timer
 *Input parameters :Pwm_ChannelNum Channel
 *
 * Return:void
 **/
void Pwm_StopTimer(Pwm_enuSourceNum Channel);

/*
 * Description: is used to Register CBF if an overflow happened
 * Input parameters :Pwm_ChannelNum Channel, Cbf
 * Return: Pwm_tenuErrorStatus
 * */
Pwm_tenuErrorStatus Pwm_enuRegisterOvfCbf(pfunc CallBackFn,Pwm_enuSourceNum Pwm_SrcNum);

/*
 * Description: is used to Register CBF if an OnCompare happened
 * Input parameters :Pwm_ChannelNum Channel, Cbf
 * Return: Pwm_tenuErrorStatus
 * */
Pwm_tenuErrorStatus Pwm_enuRegisterOcmCbf(pfunc CallBackFn,Pwm_ChannelNum Pwm_SrcNum);


#endif /* PWM_H_ */

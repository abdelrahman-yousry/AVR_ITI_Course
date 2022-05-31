/*
 * Serrvo.h
 *
 *  Created on: May 29, 2022
 *      Author: U3
 */

#ifndef HAL_SERRVO_H_
#define HAL_SERRVO_H_


#define SERVO_NUM1	0

typedef enum
{
	Pwm_enuCh1A,
	Pwm_enuCh1B,
}Pwm_enuChannel;

typedef struct
{
	u8 InitialAngle;
	Pwm_enuChannel ChNum;
}Servo_tCfg;


void Servo_vidInit(Servo_tCfg* Servo_strCfg);
void Servo_vidSetAngle(u8 Motor_u8Name,u16 Servo_u16AngleVal);
s32 Mapping(s32 InputVal,s32 MinIn,s32 MaxIn,s32 MinOut,s32 MaxOut);
void Timer1_voidInit(void);
#endif /* HAL_SERRVO_H_ */

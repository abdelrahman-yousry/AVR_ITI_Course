/*
 * main.c
 *
 *  Created on: Mar 25, 2022
 *      Author: U3
 */
#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"
#include "../MCAL/Pwm.h"
#include "../MCAL/Adc.h"
#include "../HAL/Serrvo.h"
#include <avr/io.h>
#include <avr/delay.h>



int main (void)
{
	Servo_tCfg ServCfg;
	u16 Adc_u16Val=0;
	u16 Angle;
	ServCfg.ChNum=Pwm_enuCh1A;
	ServCfg.InitialAngle=0;
	Port_vidInit();
	Servo_vidInit(&ServCfg);
	Adc_vidInit();
	while (1)
	{
		Adc_vidStartConversion();
		Adc_u16Val=Adc_u16GetResult();
		Angle = (Adc_u16Val / (f32)5.7) ;
		Servo_vidSetAngle(SERVO_NUM1,Angle);
	}
	return 0 ;
}


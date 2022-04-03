/*
 * main.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Abdelrahman Yousry
 */
#include "../Services/Std_types.h"
#include "../MCAL/Port.h"
#include "../MCAL/Dio.h"
#include "../HAL/Lcd.h"
#include "../MCAL/Adc.h"
#include <avr/delay.h>
#include <stdlib.h>

int main (void)
{
	f32 AdcResult=0;
	u32 AnalogValue=0;
	u8 flag=0;
	u8 buffer[20];
	Port_vidInit();
	Adc_vidInit();
	Adc_vidControl(ADC_u8ENABLE);
	Lcd_vidInit();
	Lcd_vidDiaplayString((pu8)"Volt");
	while (1)
	{
		u8 switchbtn=0;
		Adc_vidStartConversion();
		AdcResult=Adc_u16GetResult();
		AnalogValue=(AdcResult* ((5000)/1024));
		itoa(AnalogValue,buffer,10);
		Dio_enuReadChannelId(DIO_PIN_24,&switchbtn);
		if(switchbtn==0)
		{
			flag^=1;
			_delay_ms(200);
		}
		if(flag==0)
		{
			Lcd_vidGoTo(1,8);
			Lcd_vidDiaplayString(buffer);
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("mv");
		}
		else
		{
			Lcd_vidGoTo(1,8);
			Lcd_vidDiaplayChar(buffer[0]);
			Lcd_vidDiaplayChar('.');
			Lcd_vidDiaplayChar(buffer[1]);
			Lcd_vidDiaplayChar(buffer[2]);
			Lcd_vidDiaplayChar(buffer[3]);
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("  ");
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("v");
		}

//		Lcd_vidGoTo(1,8);
//		itoa(AnalogValue,buffer,10);
//		Lcd_vidDiaplayString(buffer);
////		Lcd_vidDisplayNumber(AnalogValue);
//		Lcd_vidDiaplayChar('.');
//		AnalogValue=(AdcResult* (u32)((5*num)/1024)*10)-(AdcResult-AnalogValue);
////		Lcd_vidDisplayNumber(AnalogValue);
//		itoa(AnalogValue,buffer,10);
//		Lcd_vidDiaplayString(buffer);

	}

	return 0 ;
}

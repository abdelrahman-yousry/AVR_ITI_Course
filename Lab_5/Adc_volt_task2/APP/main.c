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
	u8 switchbtn1=1;
	u8 switchbtn2=1;
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
	Port_vidInit();
	Adc_vidInit();
	Adc_vidControl(ADC_u8ENABLE);
	Lcd_vidInit();
	Lcd_vidDiaplayString((pu8)"Welcome to the");
	Lcd_vidGoTo(1,0);
	Lcd_vidDiaplayString((pu8)"Voltameter");
	_delay_ms(3000);
	Lcd_vidSendCommand(LCD_u8CLEAR_DISPAY);
	Lcd_vidGoTo(0,0);
	Lcd_vidDiaplayString((pu8)"Choose unit");
	Lcd_vidGoTo(1,0);
	Lcd_vidDiaplayString((pu8)"1-V         2-mV");

	while (1)
	{

		Adc_vidStartConversion();
		AdcResult=Adc_u16GetResult();
		AnalogValue=(AdcResult* ((5000)/1024));
		itoa(AnalogValue,buffer,10);
		Dio_enuReadChannelId(DIO_PIN_24,&switchbtn1);
		Dio_enuReadChannelId(DIO_PIN_25,&switchbtn2);
		if(switchbtn1==0)
		{
			flag=1;
			Lcd_vidSendCommand(LCD_u8CLEAR_DISPAY);
		}
		else if(switchbtn2==0)
		{
			flag=2;
			Lcd_vidSendCommand(LCD_u8CLEAR_DISPAY);
		}
		if (flag == 1)
		{
			Lcd_vidDiaplayString((pu8)"Volt");
			Lcd_vidGoTo(1,8);
			Lcd_vidDiaplayChar(buffer[0]);
			Lcd_vidDiaplayChar('.');
			Lcd_vidDiaplayChar(buffer[1]);
			Lcd_vidDiaplayChar(buffer[2]);
			Lcd_vidDiaplayChar(buffer[3]);
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("  ");
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("v ");
			Dio_enuReadChannelId(DIO_PIN_25,&switchbtn2);
		}

		else if(flag==2)
		{

			Lcd_vidDiaplayString((pu8)"Volt");
			Lcd_vidGoTo(1,8);
			Lcd_vidDiaplayString(buffer);
			Lcd_vidGoTo(1,14);
			Lcd_vidDiaplayString("mv");
			Dio_enuReadChannelId(DIO_PIN_24,&switchbtn1);
		}

		else
		{

		}
	}

	return 0 ;
}

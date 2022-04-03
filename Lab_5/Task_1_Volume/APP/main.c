/*
 * main.c
 *
 *  Created on: Mar 30, 2022
 *      Author: Abdelrahman Yousry
 */
#include "../Services/Std_types.h"
#include "../MCAL/Port.h"
#include "../HAL/Lcd.h"
#include "../MCAL/Adc.h"
#include <avr/delay.h>

int main (void)
{
	Port_vidInit();
	Adc_vidInit();
	Adc_vidControl(ADC_u8ENABLE);
	Lcd_vidInit();
	Lcd_vidDiaplayString((pu8)"Volume");
	u8 char1[8] = {  0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00001111};
	u8 char2[8] = {
					 0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000011
					,0b00011111
	};
	u8 char3[8]={
					 0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000011
					,0b00011111
					,0b00011111
	};
	u8 char4[8]= {
					 0b00000000
					,0b00000000
					,0b00000000
					,0b00000000
					,0b00000011
					,0b00011111
					,0b00011111
					,0b00011111
	};
	u8 char5[8] = {
					 0b00000000
					,0b00000000
					,0b00000000
					,0b00000111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
	};

	u8 char6[8] = {
					0b00000000
					,0b00000001
					,0b00000111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
	};

	u8 char7[8] = {
					 0b00000000
					,0b00000111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
	};

	u8 char8[8] = {
					 0b00000011
					,0b00001111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
					,0b00011111
	};

    Lcd_vidCreateCustomCharacter(char1,0);
    Lcd_vidCreateCustomCharacter(char2,1);
    Lcd_vidCreateCustomCharacter(char3,2);
    Lcd_vidCreateCustomCharacter(char4,3);
    Lcd_vidCreateCustomCharacter(char5,4);
    Lcd_vidCreateCustomCharacter(char6,5);
    Lcd_vidCreateCustomCharacter(char7,6);
    Lcd_vidCreateCustomCharacter(char8,7);

	while (1)
	{
		Adc_vidStartConversion();
		u16 Loc_AdcResult = Adc_u16GetResult();

		if (Loc_AdcResult<128)
		{

			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidGoTo(1,1);
			Lcd_vidDiaplayString("       ");
		}
		else if (Loc_AdcResult>128 && Loc_AdcResult<220)
		{
			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidGoTo(1,2);
			Lcd_vidDiaplayString("       ");
		}

		else if (Loc_AdcResult>220 && Loc_AdcResult<320)
		{

			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidGoTo(1,3);
			Lcd_vidDiaplayString("            ");
		}
		else if (Loc_AdcResult>320 && Loc_AdcResult<420)
		{

			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidDiaplayChar(3);
			Lcd_vidGoTo(1,4);
			Lcd_vidDiaplayString("         ");
		}
		else if (Loc_AdcResult>420 && Loc_AdcResult<540)
		{

			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidDiaplayChar(3);
			Lcd_vidDiaplayChar(4);
			Lcd_vidGoTo(1,5);
			Lcd_vidDiaplayString("           ");
		}
		else if (Loc_AdcResult>540 && Loc_AdcResult<640)
		{
			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidDiaplayChar(3);
			Lcd_vidDiaplayChar(4);
			Lcd_vidDiaplayChar(5);
			Lcd_vidGoTo(1,6);
			Lcd_vidDiaplayString("         ");
		}
		else if (Loc_AdcResult>640 &&Loc_AdcResult<740)
		{
			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidDiaplayChar(3);
			Lcd_vidDiaplayChar(4);
			Lcd_vidDiaplayChar(5);
			Lcd_vidDiaplayChar(6);
			Lcd_vidGoTo(1,7);
			Lcd_vidDiaplayString("       ");
		}
		else if (Loc_AdcResult>740 &&Loc_AdcResult<850)
		{

			Lcd_vidGoTo(1,0);
			Lcd_vidDiaplayChar(0);
			Lcd_vidDiaplayChar(1);
			Lcd_vidDiaplayChar(2);
			Lcd_vidDiaplayChar(3);
			Lcd_vidDiaplayChar(4);
			Lcd_vidDiaplayChar(5);
			Lcd_vidDiaplayChar(6);
			Lcd_vidDiaplayChar(7);
			Lcd_vidGoTo(1,8);
			Lcd_vidDiaplayString("     ");
		}

		_delay_ms(100);
	}


	return 0 ;
}

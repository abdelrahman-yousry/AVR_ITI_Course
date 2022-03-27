/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: U3
 */

#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"
#include "../HAL/Lcd_int.h"
#include "../HAL/Lcd_priv.h"

int main (void)
{
	Lcd_vidInit();
	Lcd_vidSendCommand(0x01);
	u8 char1[8] = {0B00000, 0B00011, 0B00100, 0B01000, 0B00100, 0B00011, 0B11111, 0B00000};
	u8 char3[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00001, 0B00001, 0B11111, 0B00100};
	u8 char4[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00011, 0B00001, 0B01111, 0B00000};
	u8 char5[8] = {0B00000, 0B00000, 0B00000, 0B01110, 0B10001, 0B10001, 0B01110, 0B00000};

	LCD_Custom_Char(0 , char1);
	LCD_Custom_Char(1 , char3);
	LCD_Custom_Char(2 , char4);
	LCD_Custom_Char(3 , char5);
	for(s8 i=10,j=0;i>6;i--,j++)
	{
		Lcd_vidGoTo(0 , i);
		Lcd_vidWriteChar(j);
	}

	u8 char6[8] = {0B00000, 0B00000, 0B00001, 0B00001, 0B11110, 0B00000, 0B01100, 0B00000};
	u8 char7[8] = {0B00000, 0B00000, 0B10101, 0B10101, 0B01010, 0B00000, 0B00000, 0B00000};
	u8 char8[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00011, 0B00010, 0B00100, 0B11000};
	u8 char9[8] = {0B00000, 0B00000, 0B00000, 0B00001, 0B10010, 0B10001, 0B01110, 0B00000};
	LCD_Custom_Char(4 , char6);
	LCD_Custom_Char(5 , char7);
	LCD_Custom_Char(6 , char8);
	LCD_Custom_Char(7 , char9);
	for(s8 i=10,j=4;i>6;i--,j++)
	{
		Lcd_vidGoTo(1 , i);
		Lcd_vidWriteChar(j);
	}
	while(1);

}

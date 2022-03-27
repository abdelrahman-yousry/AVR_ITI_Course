/*
 * main.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */

#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include <avr/delay.h>
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"
#include "../HAL/Lcd_int.h"

int main (void)
{
	Lcd_vidInit();
	while(1)
	{
		/*phase 1*/
		/*RoW 1 --- coulmn 6*/
		u8 char1[8] = {0B01010, 0B01110, 0B01010, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		/*RoW 0 --- coulmn 6*/
		u8 char2[8] ={0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00100};
		LCD_Custom_Char(0 , char1);
		LCD_Custom_Char(1 , char2);
		Lcd_vidGoTo(0 , 6);
		Lcd_vidWriteChar(1);
		Lcd_vidGoTo(1 , 6);
		Lcd_vidWriteChar(0);
		_delay_ms(1500);
		_delay_ms(1500);
		Lcd_vidSendCommand(0x01);
		/*RoW 1 --- coulmn 6*/
		u8 char3[8] = {0B11111, 0B10001, 0B10001, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		/*RoW 0 --- coulmn 6*/
		u8 char4[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00100, 0B01010, 0B10001};
		LCD_Custom_Char(2 , char3);
		LCD_Custom_Char(3 , char4);
		Lcd_vidGoTo(0 , 6);
		Lcd_vidWriteChar(3);
		Lcd_vidGoTo(1 , 6);
		Lcd_vidWriteChar(2);
		_delay_ms(1500);
		_delay_ms(1500);
		Lcd_vidSendCommand(0x01);
		u8 char5[8] = {0B00010, 0B00011, 0B00010, 0B00010, 0B00010, 0B00010, 0B00000, 0B00000};
		u8 char6[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00001};
		u8 char7[8] = {0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B10000};
		u8 char8[8] = {0B01000, 0B11000, 0B01000, 0B01000, 0B01000, 0B01000, 0B00000, 0B00000};
		u8 char9[8] = {0B00000, 0B11111, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		u8 char10[8]= {0B00000, 0B00000, 0B00000, 0B00100, 0B01010, 0B10001, 0B00000, 0B00000};
		LCD_Custom_Char(0 , char5);
		LCD_Custom_Char(1 , char6);
		LCD_Custom_Char(2 , char7);
		LCD_Custom_Char(3 , char8);
		LCD_Custom_Char(4 , char9);
		LCD_Custom_Char(5 , char10);
		Lcd_vidGoTo(1 , 5);
		Lcd_vidWriteChar(0);
		Lcd_vidGoTo(0 , 5);
		Lcd_vidWriteChar(1);
		Lcd_vidGoTo(1 , 6);
		Lcd_vidWriteChar(4);
		Lcd_vidGoTo(0 , 6);
		Lcd_vidWriteChar(5);
		Lcd_vidGoTo(1 , 7);
		Lcd_vidWriteChar(3);
		Lcd_vidGoTo(0 , 7);
		Lcd_vidWriteChar(2);
		_delay_ms(1500);
		_delay_ms(1500);
		Lcd_vidSendCommand(0x01);
		u8 char11[8] = {0B10000, 0B10000, 0B11111, 0B10000, 0B10000, 0B10000, 0B10000, 0B10000};
		u8 char12[8] = {0B00000, 0B00000, 0B00000, 0B00001, 0B00010, 0B00100, 0B01000, 0B10000};
		u8 char13[8] = {0B01000, 0B10000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		u8 char14[8] = {0B00000, 0B00000, 0B11111, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		u8 char15[8] = {0B00000, 0B00000, 0B11111, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		u8 char16[8] = {0B00000, 0B00000, 0B00000, 0B10000, 0B01000, 0B00100, 0B00010, 0B00001};
		u8 char17[8] = {0B00010, 0B00001, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
		u8 char18[8] = {0B00001, 0B00001, 0B11111, 0B00001, 0B00001, 0B00001, 0B00001, 0B00001};
		LCD_Custom_Char(0 , char11);
		LCD_Custom_Char(1 , char12);
		LCD_Custom_Char(2 , char13);
		LCD_Custom_Char(3 , char14);
		LCD_Custom_Char(4 , char15);
		LCD_Custom_Char(5 , char16);
		LCD_Custom_Char(6 , char17);
		LCD_Custom_Char(7 , char18);

		Lcd_vidGoTo(1 , 4);
		Lcd_vidWriteChar(0);
		Lcd_vidGoTo(0 , 4);
		Lcd_vidWriteChar(1);
		Lcd_vidGoTo(0 , 5);
		Lcd_vidWriteChar(2);
		Lcd_vidGoTo(1 , 5);
		Lcd_vidWriteChar(3);
		Lcd_vidGoTo(1 , 6);
		Lcd_vidWriteChar(4);
		Lcd_vidGoTo(0 , 7);
		Lcd_vidWriteChar(5);
		Lcd_vidGoTo(0 , 6);
		Lcd_vidWriteChar(6);
		Lcd_vidGoTo(1 , 7);
		Lcd_vidWriteChar(7);

		_delay_ms(1500);
		_delay_ms(1500);
		Lcd_vidSendCommand(0x01);
	}
}

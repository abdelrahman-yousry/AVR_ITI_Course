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
#include "../HAL/Lcd_priv.h"

int main (void)
{

	Lcd_vidInit();
	s8 Count_row = 0,Count_column = 0;
	while(1)
	{
		for(;;Count_row = !Count_row,Count_column++)
		{
			if(Count_column == 15)
			{
				break;
			}
			if(Count_column-3 >= 0 && Count_column-3 <= 15)
			{
				Lcd_vidGoTo(!Count_row , Count_column-3);
				Lcd_vidWriteChar('A');
				_delay_ms(500);
			}
			if(Count_column-2 >= 0 && Count_column-2 <= 15)
			{
				Lcd_vidGoTo(Count_row , Count_column-2);
				Lcd_vidWriteChar('B');
				_delay_ms(500);
			}
			if(Count_column-1 >= 0 && Count_column-1 <= 15)
			{
				Lcd_vidGoTo(!Count_row , Count_column-1);
				Lcd_vidWriteChar('D');
				_delay_ms(500);
			}
			if(Count_column >= 0 && Count_column <= 15)
			{
				Lcd_vidGoTo(Count_row , Count_column);
				Lcd_vidWriteChar('O');
				_delay_ms(500);
			}
			_delay_ms(500);
			_delay_ms(500);
			Lcd_vidSendCommand(0x01);
			_delay_ms(2);
		}
		for(;;Count_row = !Count_row,Count_column--)
		{
			if(Count_column-3 >= 0 && Count_column-3 <= 15)
			{
				Lcd_vidGoTo(!Count_row , Count_column-3);
				Lcd_vidWriteChar('A');
				_delay_ms(500);
			}
			if(Count_column-2 >= 0 && Count_column-2 <= 15)
			{
				Lcd_vidGoTo(Count_row , Count_column-2);
				Lcd_vidWriteChar('B');
				_delay_ms(500);
			}
			if(Count_column-1 >= 0 && Count_column-1 <= 15)
			{
				Lcd_vidGoTo(!Count_row , Count_column-1);
				Lcd_vidWriteChar('D');
				_delay_ms(500);
			}
			if(Count_column >= 0 && Count_column <= 15)
			{
				Lcd_vidGoTo(Count_row , Count_column);
				Lcd_vidWriteChar('O');
				_delay_ms(500);
			}
			_delay_ms(500);
			_delay_ms(500);
			Lcd_vidSendCommand(0x01);
			_delay_ms(2);
			if(Count_column-3 == 1)
			{
				Count_row = !Count_row;
				Count_column = 3;
				break;
			}
		}
	}
	return 0;
}

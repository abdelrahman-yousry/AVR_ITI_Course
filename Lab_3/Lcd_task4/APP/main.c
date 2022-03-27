/*
 * main.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */

#include <util/delay.h>
#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"
#include "../HAL/Lcd_int.h"
#include "../HAL/Lcd_priv.h"

int main (void)
{
	Lcd_vidInit();
	Lcd_vidWriteChar('X');
	_delay_ms(200);
	while(1)
	{
		for(u8 Count_column=1,Count_row=0;;Count_column++)
		{
			if(Count_column == 16)
			{
				if(Count_row == 0)
				{
					Count_column = 0;
					Count_row = 1;
				}
				else
				{
					break;
				}
			}
			Lcd_vidSendCommand(0x01);
			Lcd_vidGoTo(Count_row,Count_column);
			_delay_ms(2);
			Lcd_vidWriteChar('X');
			_delay_ms(1000);

		}

		for(u8 Count_column=14,Count_row=1;;Count_column--)
		{
			Lcd_vidSendCommand(0x01);
			Lcd_vidGoTo(Count_row,Count_column);
			_delay_ms(2);
			Lcd_vidWriteChar('X');
			_delay_ms(1000);
			if(Count_column == 0)
			{
				if(Count_row == 1)
				{
					Count_column = 16;
					Count_row = 0;
				}
				else
				{
					break;
				}
			}
		}
	}
	return 0;
}

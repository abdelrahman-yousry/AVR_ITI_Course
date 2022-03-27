/*
 * Lcd_prg.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */

#include <util/delay.h>
#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include "../MCAL/Port.h"
#include "../MCAL/Dio.h"
#include "../HAL/Lcd_cfg.h"
#include "../HAL/Lcd_int.h"
#include "../HAL/Lcd_priv.h"





void Lcd_vidInit(void)
{
	u8 iterator=0;
	for(iterator=16; iterator<=23;iterator++)
	{
		Port_enuSetPinDir(iterator,PORT_u8OUTPUT);
	}
	Port_enuSetPinDir(LCD_u8PIN_RS,PORT_u8OUTPUT);
	Port_enuSetPinDir(LCD_u8PIN_RW,PORT_u8OUTPUT);
	Port_enuSetPinDir(LCD_u8PIN_EN,PORT_u8OUTPUT);

	Lcd_vidSendCommand(TWO_LINES_5x7);
	//TODO:
	_delay_ms(2);
	Lcd_vidSendCommand(LCD_CURSOR_OFF);
	//0c m4 maogood
	//0f maogood w bbylink

	_delay_ms(2);
	Lcd_vidSendCommand(LCD_CLR_DISPLAY);

	//clr display
	_delay_ms(2);

}


void Lcd_vidSendCommand(u8 Command)
{
	Dio_enuWriteChannelId(LCD_u8PIN_RS,DIO_u8LOW);
	Dio_enuWriteChannelId(LCD_u8PIN_RW,DIO_u8LOW);


	Dio_enuWriteChannelId(LCD_u8PIN_D0,GET_BIT(Command,0));
	Dio_enuWriteChannelId(LCD_u8PIN_D1,GET_BIT(Command,1));
	Dio_enuWriteChannelId(LCD_u8PIN_D2,GET_BIT(Command,2));
	Dio_enuWriteChannelId(LCD_u8PIN_D3,GET_BIT(Command,3));
	Dio_enuWriteChannelId(LCD_u8PIN_D4,GET_BIT(Command,4));
	Dio_enuWriteChannelId(LCD_u8PIN_D5,GET_BIT(Command,5));
	Dio_enuWriteChannelId(LCD_u8PIN_D6,GET_BIT(Command,6));
	Dio_enuWriteChannelId(LCD_u8PIN_D7,GET_BIT(Command,7));



	Dio_enuWriteChannelId(LCD_u8PIN_EN,DIO_u8HIGH);
	_delay_ms(2);
	Dio_enuWriteChannelId(LCD_u8PIN_EN,DIO_u8LOW);
	_delay_ms(2);



}

void Lcd_vidWriteChar(u8 Data)
{
	Dio_enuWriteChannelId(LCD_u8PIN_RS,DIO_u8HIGH);
	Dio_enuWriteChannelId(LCD_u8PIN_RW,DIO_u8LOW);


	Dio_enuWriteChannelId(LCD_u8PIN_D0,GET_BIT(Data,0));
	Dio_enuWriteChannelId(LCD_u8PIN_D1,GET_BIT(Data,1));
	Dio_enuWriteChannelId(LCD_u8PIN_D2,GET_BIT(Data,2));
	Dio_enuWriteChannelId(LCD_u8PIN_D3,GET_BIT(Data,3));
	Dio_enuWriteChannelId(LCD_u8PIN_D4,GET_BIT(Data,4));
	Dio_enuWriteChannelId(LCD_u8PIN_D5,GET_BIT(Data,5));
	Dio_enuWriteChannelId(LCD_u8PIN_D6,GET_BIT(Data,6));
	Dio_enuWriteChannelId(LCD_u8PIN_D7,GET_BIT(Data,7));


	Dio_enuWriteChannelId(LCD_u8PIN_EN,DIO_u8HIGH);
	_delay_ms(2);
	Dio_enuWriteChannelId(LCD_u8PIN_EN,DIO_u8LOW);
	_delay_ms(2);
}



void Lcd_vidGoTo(u8 Row, u8 Col)
{
	switch(Row)
	{
	case 0 :

		if (Col>=0 && Col < LCD_MAX_CHAR_IN_LINE)
		{
			Lcd_vidSendCommand(FIRST_ROW + Col);
		}
		break ;

	case 1 :
		if (Col>=0 && Col < LCD_MAX_CHAR_IN_LINE)
		{
			Lcd_vidSendCommand(SECOND_ROW + Col);
		}
		break ;

	default:

		break ;
	}
}


void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		/* Command 0x40 and onwards forces the device to point CGRAM address */
		Lcd_vidSendCommand (0x40 + (loc*8));
		for(i=0;i<8;i++)
		{
			/* Write 8 byte for generation of 1 character */
			Lcd_vidWriteChar(msg[i]);
		}
	}
}



void Lcd_vidString(u8 *string)
{

	u8 INDIX=0;
	for(;string[INDIX]!=0;INDIX++)
	{
		Lcd_vidWriteChar(string[INDIX]);


	}

}

















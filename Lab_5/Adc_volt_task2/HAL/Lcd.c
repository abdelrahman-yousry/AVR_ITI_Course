/*
 * Lcd.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Abdelrahman Yousry
 */
#include "../Services/Std_types.h"
#include "../Services/Bit_utils.h"
#include <avr/delay.h>
#include "../MCAL/Dio.h"
#include "Lcd.h"
#include "Lcd_cfg.h"
#include "Lcd_prv.h"




void Lcd_vidInit(void)
{
	_delay_ms(LCD_u8DELAY_FOR_INITIALIZATION);
	Lcd_vidSendCommand(LCD_u8FUNCTION_SET_CFG);  		//Function Set: 8-bit, 2 Line, 5x7 Dots
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
	Lcd_vidSendCommand(LCD_u8DISPLAY_ON_CFG);   		//Display on Cursor off
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
	Lcd_vidSendCommand(LCD_u8CLEAR_DISPLAY_CFG); 		//Clear LCD
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
	Lcd_vidSendCommand(LCD_u8ENTRY_MODE_SET_CFG);       //Entry Mode
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
}
void Lcd_vidSendCommand(u8 copy_data)
{
	Dio_enuWriteChannelId(LCD_u8EN_PIN,DIO_u8LOW);
	Dio_enuWriteChannelId(LCD_u8RS_PIN,DIO_u8LOW);
	Dio_enuWriteChannelId(LCD_u8RW_PIN,DIO_u8LOW);

	Lcd_prvSendData(copy_data);
	Applying_Falling_Edge_On_EN();
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
}

void Lcd_vidDiaplayChar(u8 copy_data)
{
	Dio_enuWriteChannelId(LCD_u8EN_PIN,DIO_u8LOW);
	Dio_enuWriteChannelId(LCD_u8RS_PIN,DIO_u8HIGH);
	Dio_enuWriteChannelId(LCD_u8RW_PIN,DIO_u8LOW);
	Lcd_prvSendData(copy_data);
	Applying_Falling_Edge_On_EN();
	_delay_ms(LCD_u8DELAY_FOR_APPLYING_SEQ);
}

void Lcd_vidGoTo(u8 Copy_u8Row , u8 Copy_u8Column)
{
	if(Copy_u8Row == 0)
	{
		Lcd_vidSendCommand((0x80)+(Copy_u8Column));
		_delay_ms(2);
	}
	else if(Copy_u8Row == 1)
	{
		Lcd_vidSendCommand((0xC0)+(Copy_u8Column));
		_delay_ms(2);
	}
}

void Lcd_vidCreateCustomCharacter (pu8 Pattern, u8 Location)
{
	u8 i=0;
	Lcd_vidSendCommand (0x40+(Location*8));     //Send the Address of CGRAM
	for (i=0; i<8; i++)
	{
		Lcd_vidDiaplayChar (Pattern [ i ] );         //Pass the bytes of pattern on LCD
	}
}

void Lcd_vidDisplayNumber(u16 copy_number)
{
	u16 Loc_value = 0;
	if (copy_number==0)
	{
		Lcd_vidDiaplayChar('0');
	}
	else if(copy_number!=0)
	{
		Loc_value=copy_number/10;
		Lcd_vidDiaplayChar('0'+Loc_value);
		Loc_value=copy_number%10;
		Lcd_vidDiaplayChar('0'+Loc_value);
	}
}

void Lcd_vidDiaplayString(pu8 string)
{
	u8 iterator=0;
	while (string[iterator]!='\0')
	{
		Lcd_vidDiaplayChar(string[iterator]);
		iterator ++;
	}
}

/*This function is a private function to use it in those funcs : -
 * 1-Lcd_vidSendCommand
 * 2-Lcd_vidDiaplayChar
 * because of this I make it in function
 * note:
 * in this function I use WriteChannelID not WritePort because
 * if the user want to connect the LCD pins in different place
 * */
static void Lcd_prvSendData(u8 copy_data)
{
	Dio_enuWriteChannelId(LCD_u8D0_PIN,GET_BIT(copy_data,0));
	Dio_enuWriteChannelId(LCD_u8D1_PIN,GET_BIT(copy_data,1));
	Dio_enuWriteChannelId(LCD_u8D2_PIN,GET_BIT(copy_data,2));
	Dio_enuWriteChannelId(LCD_u8D3_PIN,GET_BIT(copy_data,3));
	Dio_enuWriteChannelId(LCD_u8D4_PIN,GET_BIT(copy_data,4));
	Dio_enuWriteChannelId(LCD_u8D5_PIN,GET_BIT(copy_data,5));
	Dio_enuWriteChannelId(LCD_u8D6_PIN,GET_BIT(copy_data,6));
	Dio_enuWriteChannelId(LCD_u8D7_PIN,GET_BIT(copy_data,7));

}


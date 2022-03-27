/*
 * main.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */


#ifndef LCD_INT_H_
#define LCD_INT_H_

void Lcd_vidInit(void);
void Lcd_vidWriteChar(u8 Data);
void Lcd_vidSendCommand(u8 Command);
void Lcd_vidGoTo(u8 Row, u8 Col);
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void Lcd_vidString(u8 *string);
#endif /* LCD_INT_H_ */

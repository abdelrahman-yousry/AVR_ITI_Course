/*
 * Lcd_cfg.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*Data pins*/
#define LCD_u8D0_PIN	DIO_PIN_16
#define LCD_u8D1_PIN	DIO_PIN_17
#define LCD_u8D2_PIN	DIO_PIN_18
#define LCD_u8D3_PIN	DIO_PIN_19
#define LCD_u8D4_PIN	DIO_PIN_20
#define LCD_u8D5_PIN	DIO_PIN_21
#define LCD_u8D6_PIN	DIO_PIN_22
#define LCD_u8D7_PIN	DIO_PIN_23

/*Control pins*/
#define LCD_u8RS_PIN	DIO_PIN_8
#define LCD_u8RW_PIN	DIO_PIN_9
#define LCD_u8EN_PIN	DIO_PIN_10


#define LCD_u8FUNCTION_SET_CFG		LCD_u8FUNCTION_SET_8BIT_2LINES_5x7
#define LCD_u8DISPLAY_ON_CFG		LCD_u8DISPALY_ON_CURSOR_OFF
#define LCD_u8CLEAR_DISPLAY_CFG		LCD_u8CLEAR_DISPAY
#define LCD_u8ENTRY_MODE_SET_CFG	LCD_u8ENTRY_MODE_SET

#endif /* LCD_CFG_H_ */

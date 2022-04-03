/*
 * Lcd_prv.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef LCD_PRV_H_
#define LCD_PRV_H_

#define LCD_u8DELAY_FOR_INITIALIZATION		((u8) 30)
#define LCD_u8DELAY_FOR_CLR_DISPLAY			((u8) 2)
#define LCD_u8DELAY_FOR_APPLYING_SEQ		((u8) 1)


#define Applying_Falling_Edge_On_EN()			Dio_enuWriteChannelId(LCD_u8EN_PIN,DIO_u8HIGH);\
		_delay_ms(2);\
		Dio_enuWriteChannelId(LCD_u8EN_PIN,DIO_u8LOW);\
		_delay_ms(2)

static void Lcd_prvSendData(u8 copy_data);

#endif /* LCD_PRV_H_ */

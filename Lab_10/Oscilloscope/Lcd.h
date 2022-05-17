/*
 * Lcd.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef LCD_H_
#define LCD_H_



/*************************COMMANDS********************************/

/*when you sending command, RS and RW are set to 0*/

/*These macros for FUNCTION SET used in the init function */
#define LCD_u8FUNCTION_SET_8BIT_2LINES_5x7	    	((u8) 0b00111000)
#define LCD_u8FUNCTION_SET_8BIT_2LINES_5x10	    	((u8) 0b00111100)
#define LCD_u8FUNCTION_SET_8BIT_1LINES_5x7		    ((u8) 0b00110000)
#define LCD_u8FUNCTION_SET_8BIT_1LINES_5x10		    ((u8) 0b00110100)
#define LCD_u8FUNCTION_SET_4BIT_2LINES_5x7		    ((u8) 0b00101000)
#define LCD_u8FUNCTION_SET_4BIT_2LINES_5x10	    	((u8) 0b00101100)
#define LCD_u8FUNCTION_SET_4BIT_1LINES_5x7		    ((u8) 0b00100000)
#define LCD_u8FUNCTION_SET_4BIT_1LINES_5x10		    ((u8) 0b00100100)

/*These macros for DISPLAY command used in the init function */
#define LCD_u8DISPALY_ON_CUSROR_BLINK				((u8) 0b00001111)
#define LCD_u8DISPALY_ON_CURSOR_OFF     			((u8) 0b00001100)
#define LCD_u8DISPALY_ON_CURSOR_ON      			((u8) 0b00001110)
#define LCD_u8DISPALY_OFF_CUSRSOR_OFF     			((u8) 0b00001000)

/*This macro is for Mode command used in init func
 * has this configuration
 * 1- incrementing the address of the DRRAM after writing
 * or reading from DDRAM
 * 2-shifting feature (right / left) the entire display
 * */
#define LCD_u8ENTRY_MODE_SET						((u8) 0b00000110)


//--------------------------------------------------------------------------------

/*This macro for clearing command*/
#define LCD_u8CLEAR_DISPAY							((u8) 0b00000001)

/*Return Home command*/
#define LCD_u8RETURN_HOME 							((u8) 0b00000010)


/*----------------------------PROTOTYPES----------------------------------*/
/**
 * Description: is used to set the initialization and mode for the LCD
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
void Lcd_vidInit(void);

/**
 * Description: is used to send DATA for the uC of the LCD
 * Inputs: it takes Byte represents in data to be displayed.
 * Return: it has no returns.
 **/
void Lcd_vidSendCommand(u8 copy_data);
/**
 * Description: is used to send command for the uC of the LCD
 * Inputs: it takes Byte represents in command to be executed.
 * Return: it has no returns.
 **/
void Lcd_vidDiaplayChar(u8 copy_data);
/**
 * Description: is used to GOTO specific loc in the LCD
 * Inputs: it takes TWO inputs.
 * 1- ROW.
 * 2- COULUMN.
 * Return: it has no returns.
 **/
void Lcd_vidGoTo(u8 Copy_u8Row , u8 Copy_u8Column);
/**
 * Description: is used to create custom character for the LCD in the CGRAM
 * you should first go to the address of the first loc in the CGRAM
 * and then write the pattern which you make in the array
 * and then go back to DDRAM by using GOTO func to go to DDRAM again
 * then Display the pattern by using the Display func and pass the index from 0 -- 8 as an argument
 * to display 0 --> 8 patterns in the CGRAM
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
void Lcd_vidCreateCustomCharacter (pu8 Pattern, u8 Location);

void Lcd_vidDiaplayString(pu8 string);
void Lcd_vidDisplayNumber(u16 copy_number);
#endif /* LCD_H_ */

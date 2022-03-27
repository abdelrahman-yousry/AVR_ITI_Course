/*
 * main.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */
#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"


/*in this task we have three switches:
 * 1-for incrementing
 * 2-for decrementing
 * 3-for blinking
 * if the increment btn is pressed it will cause turning the next led on
 * if the decrement btn is pressed it will cause turning the led off
 * if the value of the incrementing or decrementing counter exceed the range another led will be blinking
 *
 * note:: you should button long pressed on the switch bec of debouncing
 *
 * inc_switch ----> pin 4 in porta
 * dec_switch ----> pin 5 in porta
 * blink_switch --> pin 6 in porta
 * blinking led --> pin 1 in porta
 *
 * 8 Leds --------> portb
 * */
#define INCREMENT_SWITCH  PORT_u8PIN_4
#define DECREMENT_SWITCH  PORT_u8PIN_5
#define BLINK_SWITCH 	  PORT_u8PIN_6
#define BLINKING_LED 	  PORT_u8PIN_1
#define PRESSED			  0
int main (void)
{
	u8 status_flag =0;
	s8 counter =0;
	u8 iterator;
	u8 Bit_value1=1;
	u8 Bit_value2=1;
	u8 Bit_value3=1;
	/*initializing PORTB to be output which is connected to leds*/
	for(iterator=PORT_u8PIN_9;iterator<PORT_u8PIN_17;iterator++)
	{
		Port_enuSetPinMode(iterator,Output_enuLow);
	}

	/*make the increment,decrement and blink switch input pullup*/
	Port_enuSetPinMode(INCREMENT_SWITCH,Input_enuPullup);
	Port_enuSetPinMode(DECREMENT_SWITCH,Input_enuPullup);
	Port_enuSetPinMode(BLINK_SWITCH,Input_enuPullup);
	/*make the blinking led pin to be output */
	Port_enuSetPinMode(PORT_u8PIN_1,Output_enuLow);
	/*super loop*/
	while(1)
	{
		Dio_enuReadChannelId(DIO_PIN_4,&Bit_value1);
		/*if the increment switch is pressed then increment from the turning on leds for every press*/

		if(Bit_value1==PRESSED)
		{
			_delay_ms(200);
			if(counter>7)
			{
				counter =7;
				status_flag = 1;
			}
			else
			{
				Dio_enuWriteChannelId(counter+9,DIO_u8HIGH);
				_delay_ms(500);
				counter++ ;
			}
		}
		/*if the decrement switch is pressed then decrement from the turning on leds for every press*/
		else if((Dio_enuReadChannelId(DIO_PIN_5,&Bit_value2)==Dio_enuOK) &&(Bit_value2==PRESSED))
		{
			_delay_ms(200);
			if(counter<0)
			{
				counter=0;
				status_flag = 1;
			}
			else
			{
				Dio_enuWriteChannelId(counter+9,DIO_u8LOW);
				_delay_ms(500);
				counter-- ;
			}
		}
		/*if the blinking switch is pressed then blinking the leds which are in the ON state*/
		else if((Dio_enuReadChannelId(DIO_PIN_6,&Bit_value3)==Dio_enuOK) &&(Bit_value3==PRESSED))
		{
			for(iterator=0;iterator<counter;iterator++)

			{
				Dio_enuWriteChannelId(iterator,DIO_u8HIGH);
			}
			_delay_ms(500);
			for(iterator=0;iterator<counter;iterator++)
			{
				Dio_enuWriteChannelId(iterator,DIO_u8LOW);
			}
			_delay_ms(500);
		}
		/*if we exceed the led no 8 or decremented less than led no 0, the status falg will be equal 1*/
		while(status_flag==1)
		{
			Dio_enuWriteChannelId(DIO_PIN_1,DIO_u8HIGH);
			_delay_ms(500);
			Dio_enuWriteChannelId(DIO_PIN_1,DIO_u8LOW);
			_delay_ms(500);
			/*conditions to break this while loop*/
			if((Dio_enuReadChannelId(DIO_PIN_4,&Bit_value1)==Dio_enuOK) &&(Bit_value1==PRESSED))
			{
				if ((counter<7))
				{
					status_flag=0;
				}
			}
			if((Dio_enuReadChannelId(DIO_PIN_5,&Bit_value2)==Dio_enuOK) &&(Bit_value2==PRESSED))
			{
				if ((counter>0))
				{
					status_flag=0;
				}
			}
			_delay_ms(100);
		}
	}
}

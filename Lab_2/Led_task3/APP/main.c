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
/*
 *      this task aims to turn on one LED and shifting it through 8 leds
 *      we have two states:-
 *      1-when push button pressed,  reverse the direction to backward
 *      2-when push button released, reverse the direction to forward
*/

#define SW_PIN		  	  PORT_u8PIN_1
#define PRESSED 		  0
#define NOTPRESSED 		  1
int main(void)
{
	u8 Bit_value=1;

	u8 iterator;
	/*initializing PORTA to be output which is connected to leds*/
	for(iterator=PORT_u8PIN_9;iterator<PORT_u8PIN_17;iterator++)
	{
		Port_enuSetPinMode(iterator,Output_enuLow);
	}
	Dio_enuWriteChannelId(DIO_PIN_9,DIO_u8HIGH);
	/*make the switch input pullup*/
	Port_enuSetPinMode(SW_PIN,Input_enuPullup);

	/*super loop*/
	while(1)
	{
		/*Reading if the switch is pressed or not*/
		Dio_enuReadChannelId(SW_PIN,&Bit_value);
		/*/*Check if the button is pressed*/
		if(Bit_value==PRESSED)
		{
			/*make circular right shift by one to turn on the next led*/
			CRSHIFT_REG(PORTB,1);
			_delay_ms(800);
		}
		else if(Bit_value==NOTPRESSED)
		{
			/*make circular left shift by one to turn on the next led*/
			CLSHIFT_REG(PORTB,1);
			_delay_ms(800);
		}
	}
}

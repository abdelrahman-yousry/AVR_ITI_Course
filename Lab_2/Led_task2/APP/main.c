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
 *      this task aims to shifting 1 LED (turned on) through 8 leds
 *      if push button is pressed, the shifting stopped and the current turning on led
 *      from the shifting process will be on
 *       if push button is pressed again the shifting process will continue
*/
#define SW_PIN		  	  PORT_u8PIN_1
#define PRESSED 		  0
#define LED_SHIFTING	  0x01

int main (void)
{
	u8 iterator;
	u8 Bit_value=1;
	/*initializing PORTA to be output which is connected to leds*/
	for(iterator=PORT_u8PIN_9;iterator<PORT_u8PIN_17;iterator++)
	{
		Port_enuSetPinMode(iterator,Output_enuLow);
	}
	/*make the switch input pullup*/
	Port_enuSetPinMode(SW_PIN,Input_enuPullup);
	Dio_enuWriteChannelId(DIO_PIN_9,DIO_u8HIGH);
	/*super loop*/
	while(1)
	{
		/*Reading if the switch is pressed or not*/
		Dio_enuReadChannelId(SW_PIN,&Bit_value);
		/*/*Check if the button is pressed*/
		if(Bit_value==PRESSED)
		{
			/*make circular shift by one to turn on the next led*/
			CRSHIFT_REG(PORTB,LED_SHIFTING);
			/*delay for half second*/
			_delay_ms(500);
		}
	}
}

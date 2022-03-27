/*
 * main.c
 *
 *  Created on: Mar 11, 2022
 *      Author: U3
 */
#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "../MCAL/Dio.h"
#include "../MCAL/Port.h"
int main (void)
{
	Port_enuSetPinMode(PORT_u8PIN_9,Output_enuHigh);
	Port_enuSetPinMode(PORT_u8PIN_10,Output_enuHigh);
	Port_enuSetPinMode(PORT_u8PIN_11,Output_enuHigh);

	while(1)
	{
		Dio_enuWriteChannelId(DIO_PIN_9,DIO_u8HIGH);
		_delay_ms(2000);
		Dio_enuWriteChannelId(DIO_PIN_9,DIO_u8LOW);
		Dio_enuWriteChannelId(DIO_PIN_10,DIO_u8HIGH);
		_delay_ms(1000);
		Dio_enuWriteChannelId(DIO_PIN_10,DIO_u8LOW);
		Dio_enuWriteChannelId(DIO_PIN_11,DIO_u8HIGH);
		_delay_ms(2000);
		Dio_enuWriteChannelId(DIO_PIN_11,DIO_u8LOW);
	}
	return 0;
}

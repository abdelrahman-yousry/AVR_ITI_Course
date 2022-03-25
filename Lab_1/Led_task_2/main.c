/*
 * main.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Abdelrahman Yousry
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "../Std_types/Bit_utils.c"

int main (void)
{
	int counter=1;
	char status=0;
	DDRB=0xff;
	PORTB=0x01;
	CLR_BIT(DDRA,4);
	SET_BIT(PORTA,4);
	while (1)
	{
		if (status == 0)
		{
			if(GET_BIT(PINA,4)==0)
			{
				_delay_ms(200);
				status^=1;
			}
			CRSHIFT_REG(PORTB,1);
			_delay_ms(200);
			if (counter == 9)
			{
				counter=1;
			}
			counter ++;
		}
		if (status == 1)
		{
			if(GET_BIT(PINA,4)==0)
			{
				_delay_ms(200);
				status^=1;
			}
			switch(counter)
			{
				case 1:
					PORTB=0b00000001;
				break ;
				case 2:
					PORTB=0b00000010;
				break ;
				case 3:
					PORTB=0b00000100;
				break ;
				case 4:
					PORTB=0b00001000;
				break ;
				case 5:
					PORTB=0b00010000;
				break ;
				case 6:
					PORTB=0b00100000;
				break ;
				case 7:
					PORTB=0b01000000;
				break ;
				case 8:
					PORTB=0b10000000;
				break ;
			}
		}
	}
	return 0;
}


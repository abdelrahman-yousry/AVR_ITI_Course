/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Abdelrahman Yousry
 */
#include <avr/io.h>
#include <avr/delay.h>
#include "../Std_types/Bit_utils.c"

int main (void)
{
	char counter =0;

	SET_REG(DDRB);
	CLR_BIT(DDRA,4);
	SET_BIT(DDRA,1);
	SET_BIT(PORTA,4);
	CLR_BIT(DDRA,5);
	SET_BIT(PORTA,5);
	CLR_BIT(DDRA,6);
	SET_BIT(PORTA,6);
	while(1)
	{
		if(GET_BIT(PINA,4)==0)
		{

				SET_BIT(PORTB,counter);
				_delay_ms(500);
				counter++;

		}
		else if(GET_BIT(PINA,5)==0)
		{

				CLR_BIT(PORTB,counter);
				_delay_ms(500);
				counter--;

		}
		while(GET_BIT(PINA,6)==0)
		{
//			PORTB=0xff;
			int i ;
				for(i=0;i<counter;i++)

				{
					CLR_BIT(PORTB,i);
				}
				_delay_ms(500);
				for(i=0;i<counter;i++)
				{
					SET_BIT(PORTB,i);

				}
				_delay_ms(500);
		}
		if (counter>7|counter<0)
		{
			SET_BIT(PORTA,1);
			_delay_ms(500);
			CLR_BIT(PORTA,1);
			_delay_ms(500);
		}

	}

}





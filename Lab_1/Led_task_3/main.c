/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Abdelrahman Yousry
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "../Std_types/Bit_utils.c"

int main(void)
{
	SET_REG(DDRB);

	while (1)
	{
		SET_BIT(PORTB,7);
		_delay_ms(2000);
		CLR_BIT(PORTB,7);
		SET_BIT(PORTB,6);
		_delay_ms(1000);
		CLR_BIT(PORTB,6);
		SET_BIT(PORTB,5);
		_delay_ms(2000);
		CLR_BIT(PORTB,5);
	}

}

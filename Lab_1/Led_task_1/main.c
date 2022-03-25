/*
 * main.c
 *
 *  Created on: Feb 11, 2022
 *      Author: Abdelrahman Yousry
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "../Std_types/Bit_utils.c"

int main (void)
{
	DDRB=0xff;
	PORTB=0x01;
	CLR_BIT(DDRA,4);
	SET_BIT(PORTA,4);
	while (1)
	{
		while(GET_BIT(PINA,4)==0)
		{
			CRSHIFT_REG(PORTB,1);
			_delay_ms(200);
		}
		while(GET_BIT(PINA,4)==1)
		{
			CLSHIFT_REG(PORTB,1);
			_delay_ms(200);
		}
	}
	return 0;
}









///*
// * main.c
// *
// *  Created on: Feb 11, 2022
// *      Author: U3
// */
//
//#include <avr/io.h>
//
//#define CLR_BIT(Reg,Bit) (Reg) &= ~(1<<(Bit))
//#define SET_BIT(Reg,Bit) (Reg) |= (1<<(Bit))
//#define GET_BIT(Reg,Bit) ((Reg>>Bit)&1)
//
//int main (void)
//{
//	CLR_BIT(DDRA,4);
//	SET_BIT(DDRA,1);
//	SET_BIT(PORTA,4);
//	while (1)
//	{
//		if(GET_BIT(PINA,4)==0)
//		{
//			SET_BIT(PORTA,1);
//		}
//		else{
//			CLR_BIT(PORTA,1);
//		}
//	}
//	return 0;
//}

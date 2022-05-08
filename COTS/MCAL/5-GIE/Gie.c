/*
 * Gie.c
 *
 *  Created on: Apr 25, 2022
 *      Author: U3
 */
#include "Std_types.h"
#include "Registers_prv.h"
#include "Gie.h"

void Gie_vidInterruptEnable(void)
{
	SREG |= 1<<7;
}
void Gie_vidInterruptDisable(void)
{
	SREG &=~ (1<<7);
}

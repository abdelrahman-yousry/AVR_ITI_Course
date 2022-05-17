/*
 * Registers_prv.h
 *
 *  Created on: Apr 23, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef REGISTERS_PRV_H_
#define REGISTERS_PRV_H_
/*********************************DIO***************************/
#define DDRA              *((volatile u8*) 0x3A)
#define DDRB              *((volatile u8*) 0x37)
#define DDRC              *((volatile u8*) 0x34)
#define DDRD              *((volatile u8*) 0x31)
#define PORTA             *((volatile u8*) 0x3B)
#define PORTB             *((volatile u8*) 0x38)
#define PORTC             *((volatile u8*) 0x35)
#define PORTD             *((volatile u8*) 0x32)
#define PINA              *((volatile u8*) 0x39)
#define PINB              *((volatile u8*) 0x36)
#define PINC              *((volatile u8*) 0x33)
#define PIND              *((volatile u8*) 0x30)
/******************************TIMER****************************/
#define TCCR0             *((volatile u8*) 0x53)
#define TCNT0             *((volatile u8*) 0x52)
#define OCR0              *((volatile u8*) 0x5C)
#define SREG              *((volatile u8*) 0x5F)
#define TIMSK             *((volatile u8*) 0x59)
#define TIFR              *((volatile u8*) 0x58)
#define TCCR1A            *((volatile u8*) 0x4F)
#define TCCR1B            *((volatile u8*) 0x4E)
#define TCNT1            *((volatile u16*) 0x4C)
//#define TCNT1            *((volatile u16*) 0x4D)
#define OCR1A             *((volatile u16*) 0x4A)
#define OCR1B             *((volatile u16*) 0x48)
#define TCCR2			  *((volatile u8*) 0x45)
#define TCNT2			  *((volatile u8*) 0x44)


/*******************************UART****************************/
#define UCSRB             *((volatile u8*) 0x2A)
#define UCSRA             *((volatile u8*) 0x2B)
#define UCSRC             *((volatile u8*) 0x40)
#define UBRRH             *((volatile u8*) 0x40)
#define UBRRL             *((volatile u8*) 0x29)
#define UDR    	          *((volatile u8*) 0x2C)
#define SREG              *((volatile u8*) 0x5F)
/*******************************ADC*****************************/
#define ADCSRA            *((volatile u8*) 0x26)
#define ADMUX             *((volatile u8*) 0x27)
#define ADCL              *((volatile u8*) 0x24)
#define ADCH              *((volatile u8*) 0x25)
#define SFIOR             *((volatile u8*) 0x50)


#endif /* REGISTERS_PRV_H_ */

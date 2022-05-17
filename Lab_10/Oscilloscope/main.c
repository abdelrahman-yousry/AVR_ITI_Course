/*
 * main.c
 *
 *  Created on: May 13, 2022
 *      Author: U3
 */


#include "Std_types.h"
#include "Bit_Utils.h"
#define F_CPU 8000000
#include "Dio.h"
#include "Port.h"
#include "Adc.h"
#include "Lcd.h"
#include <avr/interrupt.h>
#include <avr/io.h>

f32 Ton ;
f32 Toff;
u8 first_Reading=1;
u8 state =0;
u32 ovf_counts=0;
f32 freq ;
u8 Duty ;
u16 AdcResult;
u16 AnalogValue;
int main (void)
{
	Port_enuSetPinDir(PORT_u8PIN_11,PORT_u8OUTPUT);
	Adc_vidInit();

	SET_BIT(TCCR0,6);// two bits for FAST PWM on TIM0
	SET_BIT(TCCR0,3);

	CLR_BIT(TCCR0,4);//  two bits for CLR OC0 on compare match, set OC0 at TOP
	SET_BIT(TCCR0,5);

	SET_BIT(TCCR0,2);// three bits for prescalers
	CLR_BIT(TCCR0,1);
	SET_BIT(TCCR0,0);




	CLR_BIT(TCCR1A,0);// two bits for selecting normal mode
	CLR_BIT(TCCR1A,1);

	CLR_BIT(TCCR1B,4);// two bits for selecting normal mode
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,6);// for selecting either rising of falling edge ICSE
	CLR_BIT(TCCR1B,2);//
	CLR_BIT(TCCR1B,1);// three bits for prescalers
	SET_BIT(TCCR1B,0);//



	SET_BIT(TIMSK,5);//Input Capture Interrupt Enable TICIE1 bit5
	SET_BIT(TIMSK,2);// Overflow Interrupt Enable TOIE1 bit 2

	SET_BIT(SREG,7); // enable global interrupt
	Port_vidInit();
	Adc_vidInit();
	Adc_vidControl(ADC_u8ENABLE);
	Lcd_vidInit();
	Port_enuSetPinDir(PORT_u8PIN_30,PORT_u8INPUT);




	while(1)
	{
		Adc_vidStartConversion();
		OCR0=Adc_u16GetResult();
		freq = (f32)1/(Ton+Toff);
		Duty = (Ton*(f32)100)/(Ton+Toff);
		//Lcd_vidSendCommand(0x80);
		Lcd_vidGoTo(1,0);
		Lcd_vidDiaplayString("Freq=");

		Lcd_vidDiaplayChar((((u8)freq%100)/10)+'0');
		Lcd_vidDiaplayChar((((u8)freq%100)%10)+'0');

//		Lcd_vidString("Hz");
		//Lcd_vidSendCommand(0xC0);
		Lcd_vidGoTo(1,8);
		Lcd_vidDiaplayString("Duty=");

		Lcd_vidDiaplayChar((((u8)Duty%100)/10)+'0');
		Lcd_vidDiaplayChar((((u8)Duty%100)%10)+'0');

		Lcd_vidDiaplayString("%");




		char j;
	unsigned char Character1[8]= { 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char Character2[8]= { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff};
	unsigned char Character3[8]= { 0xff,0x01,0x01,0x01,0x01,0x01,0x01,0x01};

	Lcd_vidCreateCustomCharacter(Character1,0);  /* Build Character5 at position 4 */
	Lcd_vidCreateCustomCharacter(Character2,1);  /* Build Character6 at position 5 */
	Lcd_vidCreateCustomCharacter(Character3,2);  /* Build Character6 at position 6 */



		if (Duty>=0&&Duty<=11)
		{


			for (j=0;j<1;j++)
			{
				Lcd_vidGoTo(0,j);
				Lcd_vidDiaplayChar(0);
			}
			Lcd_vidGoTo(0,0);
			Lcd_vidDiaplayChar(2);
			for (j=1;j<16;j++)

			{
				Lcd_vidGoTo(0,j);
				Lcd_vidDiaplayChar(1);
			}
		}



			if (Duty>=12&&Duty<=24)
			{


				for (j=0;j<2;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,2);
				Lcd_vidDiaplayChar(2);
				for (j=3;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}

			if (Duty>=25&&Duty<=36)
			{


				for (j=0;j<3;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,3);
				Lcd_vidDiaplayChar(2);
				for (j=4;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
			if (Duty>=37&&Duty<=42)
			{


				for (j=0;j<4;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,4);
				Lcd_vidDiaplayChar(2);
				for (j=5;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
			if (Duty>=43&&Duty<=49)
			{


				for (j=0;j<5;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,5);
				Lcd_vidDiaplayChar(2);
				for (j=6;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 50 :
//
			if (Duty>=50&&Duty<=55)
			{


				for (j=0;j<6;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,6);
				Lcd_vidDiaplayChar(2);
				for (j=7;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 56 :
//
			if (Duty>=56&&Duty<=61)
			{


				for (j=0;j<7;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,7);
				Lcd_vidDiaplayChar(2);
				for (j=8;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 62 :
//
			if (Duty>=62&&Duty<=67)
			{


				for (j=0;j<8;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,8);
				Lcd_vidDiaplayChar(2);
				for (j=9;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 68 :
//
			if (Duty>=68&&Duty<=74)
			{


				for (j=0;j<9;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,9);
				Lcd_vidDiaplayChar(2);
				for (j=10;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 75 :
//
			if (Duty>=75&&Duty<=81)
			{


				for (j=0;j<10;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,10);
				Lcd_vidDiaplayChar(2);
				for (j=11;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 82 :
//
			if (Duty>=82&&Duty<=87)
			{


				for (j=0;j<11;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,11);
				Lcd_vidDiaplayChar(2);
				for (j=12;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 88 :
//
			if (Duty>=88&&Duty<=93)
			{


				for (j=0;j<12;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,12);
				Lcd_vidDiaplayChar(2);
				for (j=13;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 94 :
//
			if (Duty>=94&&Duty<=99)
			{


				for (j=0;j<13;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,13);
				Lcd_vidDiaplayChar(2);
				for (j=14;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//		case 100 :
//
			if (Duty>=99&&Duty<=102)
			{


				for (j=0;j<14;j++)
				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(0);
				}
				Lcd_vidGoTo(0,14);
				Lcd_vidDiaplayChar(2);
				for (j=15;j<16;j++)

				{
					Lcd_vidGoTo(0,j);
					Lcd_vidDiaplayChar(1);
				}
			}
//





	}
}

ISR(TIMER1_OVF_vect)
{
	ovf_counts++;
}




ISR(TIMER1_CAPT_vect)
{
	if (first_Reading==1)
	{
		TCNT1=0;
		first_Reading=0;
		state=1;
		CLR_BIT(TCCR1B,6);
		ovf_counts=0;
	}
	else
	{
		if (state==1)
		{
			TCNT1=0;
			SET_BIT(TCCR1B,6);
			state= 0 ;
			Ton=(f32)(ICR1+(ovf_counts*65536))/(f32)8000000 ;
			ovf_counts = 0 ;
		}

		else
		{
			TCNT1=0;
			CLR_BIT(TCCR1B,6);
			state= 1 ;
			Toff=(f32)(ICR1+(ovf_counts*65536))/(f32)8000000 ;
			ovf_counts = 0 ;
		}
	}

}


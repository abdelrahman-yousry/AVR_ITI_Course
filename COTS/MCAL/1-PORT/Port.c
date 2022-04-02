/*
 * Port.c
 *
 *  Created on: Mar 17, 2022
 *      Author: U3
 */
#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include "Port.h"
#include "Port_prv_cfg.h"
#include "Port_cfg.h"
#include <avr/io.h>
Port_tenuErrorStatus Port_enuSetPinDir(u8 copy_u8PinNum, u8 copy_u8PinDir)
{
	Port_tenuErrorStatus Loc_ErrorStatus = Port_enuOk;

	/*make the checking before the logic bec. if there is an error we will return from the function*/
	/*if the number of pins exceed the number of the HW pins*/
	if (copy_u8PinNum>MAX_PIN_NUM)
	{
		/*pin number error */
		Loc_ErrorStatus = Port_enuPinError;
	}
	/*if the user pass parameter other than the two directions (input/output)*/
	else if(copy_u8PinDir > 1)
	{
		/*Direction error*/
		Loc_ErrorStatus = Port_enuPortError;
	}

	else
	{
		u8 Loc_u8PinIndex = copy_u8PinNum%PIN_AND_PORT_DIVISOR;
		u8 Loc_u8PortIndex = copy_u8PinNum/PIN_AND_PORT_DIVISOR;
		/* switch on the port index and according to the pin Dir the pin will be set or cleared*/
		switch (Loc_u8PortIndex)
		{
		case PORT_A:
			if(copy_u8PinDir==PORT_u8OUTPUT)
			{
				SET_BIT(DDRA,Loc_u8PinIndex);
			}
			else
			{
				CLR_BIT(DDRA,Loc_u8PinIndex);
			}
			break;
		case PORT_B:
			if(copy_u8PinDir==PORT_u8OUTPUT)
			{
				SET_BIT(DDRB,Loc_u8PinIndex);
			}
			else
			{
				CLR_BIT(DDRB,Loc_u8PinIndex);
			}
			break;
		case PORT_C:
			if(copy_u8PinDir==PORT_u8OUTPUT)
			{
				SET_BIT(DDRC,Loc_u8PinIndex);
			}
			else
			{
				CLR_BIT(DDRC,Loc_u8PinIndex);
			}
			break;
		case PORT_D:
			if(copy_u8PinDir==PORT_u8OUTPUT)
			{
				SET_BIT(DDRD,Loc_u8PinIndex);
			}
			else
			{
				CLR_BIT(DDRD,Loc_u8PinIndex);
			}
			break;

		default:
			/*Do nothing*/
			break;
		}
	}
	return Loc_ErrorStatus;
}


Port_tenuErrorStatus Port_enuSetPinMode(u8 copy_u8PinNum, Port_tenuPinMode enu_PinMode)
{
	Port_tenuErrorStatus Loc_ErrorStatus = Port_enuOk;
	if(enu_PinMode>NUMBER_OF_MODES)
	{
		Loc_ErrorStatus = Port_enuModeError;
	}
	else if(copy_u8PinNum>MAX_PIN_NUM)
	{
		Loc_ErrorStatus = Port_enuPinError;
	}
	else
	{
		u8 Loc_u8PortIndex = (copy_u8PinNum /PIN_AND_PORT_DIVISOR);
		u8 Loc_u8PinIndex  = (copy_u8PinNum %PIN_AND_PORT_DIVISOR);

		switch(Loc_u8PortIndex)
		{
		case PORT_A:
			switch(enu_PinMode)
			{
			case Output_enuHigh:
				SET_BIT(DDRA,Loc_u8PinIndex);
				SET_BIT(PORTA,Loc_u8PinIndex);
				break;
			case Output_enuLow:
				SET_BIT(DDRA,Loc_u8PinIndex);
				CLR_BIT(PORTA,Loc_u8PinIndex);
				break;
			case Input_enuPullup:
				CLR_BIT(DDRA,Loc_u8PinIndex);
				SET_BIT(PORTA,Loc_u8PinIndex);
				break;
			case Input_enuHighImpedence:
				CLR_BIT(DDRA,Loc_u8PinIndex);
				CLR_BIT(PORTA,Loc_u8PinIndex);
				break;
			default:
				/*do nothing*/
				break;
			}
			break;
			case PORT_B:
				switch(enu_PinMode)
				{
				case Output_enuHigh:
					SET_BIT(DDRB,Loc_u8PinIndex);
					SET_BIT(PORTB,Loc_u8PinIndex);
					break;
				case Output_enuLow:
					SET_BIT(DDRB,Loc_u8PinIndex);
					CLR_BIT(PORTB,Loc_u8PinIndex);
					break;
				case Input_enuPullup:
					CLR_BIT(DDRB,Loc_u8PinIndex);
					SET_BIT(PORTB,Loc_u8PinIndex);
					break;
				case Input_enuHighImpedence:
					CLR_BIT(DDRB,Loc_u8PinIndex);
					CLR_BIT(PORTB,Loc_u8PinIndex);
					break;
				default:
					/*do nothing*/
					break;
				}
				break ;
				case PORT_C:
					switch(enu_PinMode)
					{
					case Output_enuHigh:
						SET_BIT(DDRC,Loc_u8PinIndex);
						SET_BIT(PORTC,Loc_u8PinIndex);
						break;
					case Output_enuLow:
						CLR_BIT(DDRC,Loc_u8PinIndex);
						CLR_BIT(PORTC,Loc_u8PinIndex);
						break;
					case Input_enuPullup:
						CLR_BIT(DDRC,Loc_u8PinIndex);
						SET_BIT(PORTC,Loc_u8PinIndex);
						break;
					case Input_enuHighImpedence:
						CLR_BIT(DDRC,Loc_u8PinIndex);
						CLR_BIT(PORTC,Loc_u8PinIndex);
						break;
					default:
						/*do nothing*/
						break;
					}
					break ;
					case PORT_D:
						switch(enu_PinMode)
						{
						case Output_enuHigh:
							SET_BIT(DDRD,Loc_u8PinIndex);
							SET_BIT(PORTD,Loc_u8PinIndex);
							break;
						case Output_enuLow:
							SET_BIT(DDRD,Loc_u8PinIndex);
							CLR_BIT(PORTD,Loc_u8PinIndex);
							break;
						case Input_enuPullup:
							CLR_BIT(DDRD,Loc_u8PinIndex);
							SET_BIT(PORTA,Loc_u8PinIndex);
							break;
						case Input_enuHighImpedence:
							CLR_BIT(DDRD,Loc_u8PinIndex);
							CLR_BIT(PORTD,Loc_u8PinIndex);
							break;
						default:
							/*do nothing*/
							break;
						}
						break ;
						default:
							/*do nothing*/
							break;
		}

	}
	return Loc_ErrorStatus;
}

void Port_vidInit(void)
{

#if PORT_PIN_0_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b0_DDRA		0
#define b0_PORTA	0
#elif PORT_PIN_0_INIT_CFG == INPUT_PULLUP
#define b0_DDRA		0
#define b0_PORTA	1
#elif PORT_PIN_0_INIT_CFG == OUTPUT_HIGH
#define b0_DDRA		1
#define b0_PORTA	1
#elif PORT_PIN_0_INIT_CFG == OUTPUT_LOW
#define b0_DDRA		1
#define b0_PORTA	0
#endif

#if PORT_PIN_1_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b1_DDRA		0
#define b1_PORTA	0
#elif PORT_PIN_1_INIT_CFG == INPUT_PULLUP
#define b1_DDRA		0
#define b1_PORTA	1
#elif PORT_PIN_1_INIT_CFG == OUTPUT_HIGH
#define b1_DDRA		1
#define b1_PORTA	1
#elif PORT_PIN_1_INIT_CFG == OUTPUT_LOW
#define b1_DDRA		1
#define b1_PORTA	0
#endif

#if PORT_PIN_2_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b2_DDRA		0
#define b2_PORTA	0
#elif PORT_PIN_2_INIT_CFG == INPUT_PULLUP
#define b2_DDRA		0
#define b2_PORTA	1
#elif PORT_PIN_2_INIT_CFG == OUTPUT_HIGH
#define b2_DDRA		1
#define b2_PORTA	1
#elif PORT_PIN_2_INIT_CFG == OUTPUT_LOW
#define b2_DDRA		1
#define b2_PORTA	0
#endif


#if PORT_PIN_3_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b3_DDRA		0
#define b3_PORTA	0
#elif PORT_PIN_3_INIT_CFG == INPUT_PULLUP
#define b3_DDRA		0
#define b3_PORTA	1
#elif PORT_PIN_3_INIT_CFG == OUTPUT_HIGH
#define b3_DDRA		1
#define b3_PORTA	1
#elif PORT_PIN_3_INIT_CFG == OUTPUT_LOW
#define b3_DDRA		1
#define b3_PORTA	0
#endif


#if PORT_PIN_4_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b4_DDRA		0
#define b4_PORTA	0
#elif PORT_PIN_4_INIT_CFG == INPUT_PULLUP
#define b4_DDRA		0
#define b4_PORTA	1
#elif PORT_PIN_4_INIT_CFG == OUTPUT_HIGH
#define b4_DDRA		1
#define b4_PORTA	1
#elif PORT_PIN_4_INIT_CFG == OUTPUT_LOW
#define b4_DDRA		1
#define b4_PORTA	0
#endif


#if PORT_PIN_5_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b5_DDRA		0
#define b5_PORTA	0
#elif PORT_PIN_5_INIT_CFG == INPUT_PULLUP
#define b5_DDRA		0
#define b5_PORTA	1
#elif PORT_PIN_5_INIT_CFG == OUTPUT_HIGH
#define b5_DDRA		1
#define b5_PORTA	1
#elif PORT_PIN_5_INIT_CFG == OUTPUT_LOW
#define b5_DDRA		1
#define b5_PORTA	0
#endif


#if PORT_PIN_6_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b6_DDRA		0
#define b6_PORTA	0
#elif PORT_PIN_6_INIT_CFG == INPUT_PULLUP
#define b6_DDRA		0
#define b6_PORTA	1
#elif PORT_PIN_6_INIT_CFG == OUTPUT_HIGH
#define b6_DDRA		1
#define b6_PORTA	1
#elif PORT_PIN_6_INIT_CFG == OUTPUT_LOW
#define b6_DDRA		1
#define b6_PORTA	0
#endif


#if PORT_PIN_7_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b7_DDRA		0
#define b7_PORTA	0
#elif PORT_PIN_7_INIT_CFG == INPUT_PULLUP
#define b7_DDRA		0
#define b7_PORTA	1
#elif PORT_PIN_7_INIT_CFG == OUTPUT_HIGH
#define b7_DDRA		1
#define b7_PORTA	1
#elif PORT_PIN_7_INIT_CFG == OUTPUT_LOW
#define b7_DDRA		1
#define b7_PORTA	0
#endif


	DDRA=CONC(b7_DDRA,b6_DDRA,b5_DDRA,b4_DDRA,b3_DDRA,b2_DDRA,b1_DDRA,b0_DDRA);
	PORTA=CONC(b7_PORTA,b6_PORTA,b5_PORTA,b4_PORTA,b3_PORTA,b2_PORTA,b1_PORTA,b0_PORTA);

#if PORT_PIN_8_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b8_DDRB		0
#define b8_PORTB	0
#elif PORT_PIN_8_INIT_CFG == INPUT_PULLUP
#define b8_DDRB		0
#define b8_PORTB	1
#elif PORT_PIN_8_INIT_CFG == OUTPUT_HIGH
#define b8_DDRB		1
#define b8_PORTB	1
#elif PORT_PIN_8_INIT_CFG == OUTPUT_LOW
#define b8_DDRB		1
#define b8_PORTB	0
#endif

#if PORT_PIN_9_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b9_DDRB		0
#define b9_PORTB	0
#elif PORT_PIN_9_INIT_CFG == INPUT_PULLUP
#define b9_DDRB		0
#define b9_PORTB	1
#elif PORT_PIN_9_INIT_CFG == OUTPUT_HIGH
#define b9_DDRB		1
#define b9_PORTB	1
#elif PORT_PIN_9_INIT_CFG == OUTPUT_LOW
#define b9_DDRB		1
#define b9_PORTB	0
#endif

#if PORT_PIN_10_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b10_DDRB		0
#define b10_PORTB	0
#elif PORT_PIN_10_INIT_CFG == INPUT_PULLUP
#define b10_DDRB		0
#define b10_PORTB	1
#elif PORT_PIN_10_INIT_CFG == OUTPUT_HIGH
#define b10_DDRB		1
#define b10_PORTB	1
#elif PORT_PIN_10_INIT_CFG == OUTPUT_LOW
#define b10_DDRB		1
#define b10_PORTB	0
#endif


#if PORT_PIN_11_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b11_DDRB		0
#define b11_PORTB	0
#elif PORT_PIN_10_INIT_CFG == INPUT_PULLUP
#define b11_DDRB		0
#define b11_PORTB	1
#elif PORT_PIN_10_INIT_CFG == OUTPUT_HIGH
#define b11_DDRB		1
#define b11_PORTB	1
#elif PORT_PIN_10_INIT_CFG == OUTPUT_LOW
#define b11_DDRB		1
#define b11_PORTB	0
#endif

#if PORT_PIN_12_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b12_DDRB		0
#define b12_PORTB	0
#elif PORT_PIN_12_INIT_CFG == INPUT_PULLUP
#define b12_DDRB		0
#define b12_PORTB	1
#elif PORT_PIN_12_INIT_CFG == OUTPUT_HIGH
#define b12_DDRB		1
#define b12_PORTB	1
#elif PORT_PIN_4_INIT_CFG == OUTPUT_LOW
#define b12_DDRB		1
#define b12_PORTB	0
#endif

#if PORT_PIN_13_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b13_DDRB		0
#define b13_PORTB	0
#elif PORT_PIN_13_INIT_CFG == INPUT_PULLUP
#define b13_DDRB		0
#define b13_PORTB	1
#elif PORT_PIN_13_INIT_CFG == OUTPUT_HIGH
#define b13_DDRB		1
#define b13_PORTB	1
#elif PORT_PIN_13_INIT_CFG == OUTPUT_LOW
#define b13_DDRB		1
#define b13_PORTB	0
#endif

#if PORT_PIN_14_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b14_DDRB		0
#define b14_PORTB	0
#elif PORT_PIN_14_INIT_CFG == INPUT_PULLUP
#define b14_DDRB		0
#define b14_PORTB	1
#elif PORT_PIN_14_INIT_CFG == OUTPUT_HIGH
#define b14_DDRB		1
#define b14_PORTB	1
#elif PORT_PIN_14_INIT_CFG == OUTPUT_LOW
#define b14_DDRB		1
#define b14_PORTB	0
#endif

#if PORT_PIN_15_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b15_DDRB		0
#define b15_PORTB		0
#elif PORT_PIN_15_INIT_CFG == INPUT_PULLUP
#define b15_DDRB		0
#define b15_PORTB		1
#elif PORT_PIN_15_INIT_CFG == OUTPUT_HIGH
#define b15_DDRB		1
#define b15_PORTB		1
#elif PORT_PIN_15_INIT_CFG == OUTPUT_LOW
#define b15_DDRB		1
#define b15_PORTB		0
#endif

	DDRB=CONC(b15_DDRB,b14_DDRB,b13_DDRB,b12_DDRB,b11_DDRB,b10_DDRB,b9_DDRB,b8_DDRB);
	PORTB=CONC(b15_PORTB,b14_PORTB,b13_PORTB,b12_PORTB,b11_PORTB,b10_PORTB,b9_PORTB,b8_PORTB);

	/**********************************************************************/
#if PORT_PIN_16_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b16_DDRC		0
#define b16_PORTC		0
#elif PORT_PIN_16_INIT_CFG == INPUT_PULLUP
#define b16_DDRC		0
#define b16_PORTC 		1
#elif PORT_PIN_16_INIT_CFG == OUTPUT_HIGH
#define b16_DDRC		1
#define b16_PORTC		1
#elif PORT_PIN_16_INIT_CFG == OUTPUT_LOW
#define b16_DDRC		1
#define b16_PORTC		0
#endif

#if PORT_PIN_17_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b17_DDRC		0
#define b17_PORTC	 	0
#elif PORT_PIN_17_INIT_CFG == INPUT_PULLUP
#define b17_DDRC		0
#define b17_PORTC		1
#elif PORT_PIN_17_INIT_CFG == OUTPUT_HIGH
#define b17_DDRC		1
#define b17_PORTC		1
#elif PORT_PIN_17_INIT_CFG == OUTPUT_LOW
#define b17_DDRC		1
#define b17_PORTC		0
#endif

#if PORT_PIN_18_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b18_DDRC		0
#define b18_PORTC		0
#elif PORT_PIN_18_INIT_CFG == INPUT_PULLUP
#define b18_DDRC		0
#define b18_PORTC		1
#elif PORT_PIN_18_INIT_CFG == OUTPUT_HIGH
#define b18_DDRC		1
#define b18_PORTC		1
#elif PORT_PIN_18_INIT_CFG == OUTPUT_LOW
#define b18_DDRC		1
#define b18_PORTC		0
#endif


#if PORT_PIN_19_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b19_DDRC		0
#define b19_PORTC		0
#elif PORT_PIN_19_INIT_CFG == INPUT_PULLUP
#define b19_DDRC		0
#define b19_PORTC		1
#elif PORT_PIN_19_INIT_CFG == OUTPUT_HIGH
#define b19_DDRC		1
#define b19_PORTC		1
#elif PORT_PIN_19_INIT_CFG == OUTPUT_LOW
#define b19_DDRC		1
#define b19_PORTC		0
#endif

#if PORT_PIN_20_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b20_DDRC		0
#define b20_PORTC		0
#elif PORT_PIN_20_INIT_CFG == INPUT_PULLUP
#define b20_DDRC		0
#define b20_PORTC		1
#elif PORT_PIN_20_INIT_CFG == OUTPUT_HIGH
#define b20_DDRC		1
#define b20_PORTC		1
#elif PORT_PIN_20_INIT_CFG == OUTPUT_LOW
#define b20_DDRC		1
#define b20_PORTC		0
#endif

#if PORT_PIN_21_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b21_DDRC		0
#define b21_PORTC		0
#elif PORT_PIN_21_INIT_CFG == INPUT_PULLUP
#define b21_DDRC		0
#define b21_PORTC		1
#elif PORT_PIN_21_INIT_CFG == OUTPUT_HIGH
#define b21_DDRC		1
#define b21_PORTC		1
#elif PORT_PIN_21_INIT_CFG == OUTPUT_LOW
#define b21_DDRC		1
#define b21_PORTC		0
#endif

#if PORT_PIN_22_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b22_DDRC		0
#define b22_PORTC		0
#elif PORT_PIN_22_INIT_CFG == INPUT_PULLUP
#define b22_DDRC		0
#define b22_PORTC		1
#elif PORT_PIN_22_INIT_CFG == OUTPUT_HIGH
#define b22_DDRC		1
#define b22_PORTC		1
#elif PORT_PIN_22_INIT_CFG == OUTPUT_LOW
#define b22_DDRC		1
#define b22_PORTC		0
#endif

#if PORT_PIN_23_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b23_DDRC		0
#define b23_PORTC		0
#elif PORT_PIN_23_INIT_CFG == INPUT_PULLUP
#define b23_DDRC		0
#define b23_PORTC		1
#elif PORT_PIN_23_INIT_CFG == OUTPUT_HIGH
#define b23_DDRC		1
#define b23_PORTC		1
#elif PORT_PIN_23_INIT_CFG == OUTPUT_LOW
#define b23_DDRC		1
#define b23_PORTC		0
#endif

	DDRC=CONC(b23_DDRC,b22_DDRC,b21_DDRC,b20_DDRC,b19_DDRC,b18_DDRC,b17_DDRC,b16_DDRC);
	PORTC=CONC(b23_PORTC,b22_PORTC,b21_PORTC,b20_PORTC,b19_PORTC,b18_PORTC,b17_PORTC,b16_PORTC);
	/**********************************************************************/
#if PORT_PIN_24_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b24_DDRD		0
#define b24_PORTD		0
#elif PORT_PIN_24_INIT_CFG == INPUT_PULLUP
#define b24_DDRD		0
#define b24_PORTD		1
#elif PORT_PIN_24_INIT_CFG == OUTPUT_HIGH
#define b24_DDRD		1
#define b24_PORTD		1
#elif PORT_PIN_24_INIT_CFG == OUTPUT_LOW
#define b24_DDRD		1
#define b24_PORTD		0
#endif

#if PORT_PIN_25_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b25_DDRD		0
#define b25_PORTD		0
#elif PORT_PIN_25_INIT_CFG == INPUT_PULLUP
#define b25_DDRD		0
#define b25_PORTD		1
#elif PORT_PIN_25_INIT_CFG == OUTPUT_HIGH
#define b25_DDRD		1
#define b25_PORTD		1
#elif PORT_PIN_25_INIT_CFG == OUTPUT_LOW
#define b25_DDRD		1
#define b25_PORTD		0
#endif

#if PORT_PIN_26_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b26_DDRD		0
#define b26_PORTD		0
#elif PORT_PIN_26_INIT_CFG == INPUT_PULLUP
#define b26_DDRD		0
#define b26_PORTD		1
#elif PORT_PIN_26_INIT_CFG == OUTPUT_HIGH
#define b26_DDRD		1
#define b26_PORTD		1
#elif PORT_PIN_26_INIT_CFG == OUTPUT_LOW
#define b26_DDRD		1
#define b26_PORTD		0
#endif

#if PORT_PIN_27_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b27_DDRD		0
#define b27_PORTD		0
#elif PORT_PIN_27_INIT_CFG == INPUT_PULLUP
#define b27_DDRD		0
#define b27_PORTD		1
#elif PORT_PIN_27_INIT_CFG == OUTPUT_HIGH
#define b27_DDRD		1
#define b27_PORTD		1
#elif PORT_PIN_27_INIT_CFG == OUTPUT_LOW
#define b27_DDRD		1
#define b27_PORTD		0
#endif

#if PORT_PIN_28_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b28_DDRD		0
#define b28_PORTD		0
#elif PORT_PIN_28_INIT_CFG == INPUT_PULLUP
#define b28_DDRD		0
#define b28_PORTD		1
#elif PORT_PIN_28_INIT_CFG == OUTPUT_HIGH
#define b28_DDRD		1
#define b28_PORTD		1
#elif PORT_PIN_28_INIT_CFG == OUTPUT_LOW
#define b28_DDRD		1
#define b28_PORTD		0
#endif

#if PORT_PIN_29_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b29_DDRD		0
#define b29_PORTD		0
#elif PORT_PIN_29_INIT_CFG == INPUT_PULLUP
#define b29_DDRD		0
#define b29_PORTD		1
#elif PORT_PIN_29_INIT_CFG == OUTPUT_HIGH
#define b29_DDRD		1
#define b29_PORTD		1
#elif PORT_PIN_29_INIT_CFG == OUTPUT_LOW
#define b29_DDRD		1
#define b29_PORTD		0
#endif

#if PORT_PIN_30_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b30_DDRD		0
#define b30_PORTD	0
#elif PORT_PIN_30_INIT_CFG == INPUT_PULLUP
#define b30_DDRD		0
#define b30_PORTD	1
#elif PORT_PIN_30_INIT_CFG == OUTPUT_HIGH
#define b30_DDRD		1
#define b30_PORTD	1
#elif PORT_PIN_30_INIT_CFG == OUTPUT_LOW
#define b30_DDRD		1
#define b30_PORTD	0
#endif

#if PORT_PIN_31_INIT_CFG == INPUT_HIGH_IMPEDENCE
#define b31_DDRD		0
#define b31_PORTD		0
#elif PORT_PIN_31_INIT_CFG == INPUT_PULLUP
#define b31_DDRD		0
#define b31_PORTD		1
#elif PORT_PIN_31_INIT_CFG == OUTPUT_HIGH
#define b31_DDRD		1
#define b31_PORTD		1
#elif PORT_PIN_31_INIT_CFG == OUTPUT_LOW
#define b31_DDRD		1
#define b31_PORTD		0
#endif

	DDRD=CONC(b31_DDRD,b30_DDRD,b29_DDRD,b28_DDRD,b27_DDRD,b26_DDRD,b25_DDRD,b24_DDRD);
	DDRD=CONC(b31_PORTD,b30_PORTD,b29_PORTD,b28_PORTD,b27_PORTD,b26_PORTD,b25_PORTD,b24_PORTD);
}

/*
 * Dio.c
 *
 *  Created on: Mar 10, 2022
 *      Author: U3
 */

/*---------Functions---------------*/

#include "../Services/Bit_utils.h"
#include "../Services/Std_types.h"
#include <avr/io.h>
#include "Dio.h"

/*
  Write on pin
  take two args Copy_u8ChannedId and Copy_u8Level
  return Dio_tenuErrorStatus
 */
Dio_tenuErrorStatus Dio_enuWriteChannelId(u8 Copy_u8ChannedId,u8 Copy_u8Level)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	u8 Loc_u8Port = Copy_u8ChannedId/8 ;
	u8 Loc_u8Pin = (Copy_u8ChannedId%8) ;

	if(Copy_u8ChannedId<=32)
	{
		switch (Loc_u8Port)
		{
		case PORT_A:

			if(Copy_u8Level==DIO_u8HIGH)
			{
				SET_BIT(PORTA,Loc_u8Pin);
			}
			else if(Copy_u8Level==DIO_u8LOW)
			{
				CLR_BIT(PORTA,Loc_u8Pin);
			}

			break;
		case PORT_B:
			if(Copy_u8Level==DIO_u8HIGH)
			{
				SET_BIT(PORTB,Loc_u8Pin);
			}
			else if(Copy_u8Level==DIO_u8LOW)
			{
				CLR_BIT(PORTB,Loc_u8Pin);
			}
			break ;
		case PORT_C:
			if(Copy_u8Level==DIO_u8HIGH)
			{
				SET_BIT(PORTC,Loc_u8Pin);
			}
			else if(Copy_u8Level==DIO_u8LOW)
			{
				CLR_BIT(PORTC,Loc_u8Pin);
			}
			break ;
		case PORT_D:
			if(Copy_u8Level==DIO_u8HIGH)
			{
				SET_BIT(PORTD,Loc_u8Pin);
			}
			else if(Copy_u8Level==DIO_u8LOW)
			{
				CLR_BIT(PORTD,Loc_u8Pin);
			}
			break ;
		}
	}
	else
	{
		Loc_enuReturnStatus =  Dio_enuPortError ;

	}
	return Loc_enuReturnStatus;

}

/*
  Read from pin
  take two args Copy_u8ChannedId and Add_pu8ChannelLevel
  return Dio_tenuErrorStatus
 */
Dio_tenuErrorStatus Dio_enuReadChannelId(u8 Copy_u8ChannedId, pu8 Add_pu8ChannelLevel)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	if(Copy_u8ChannedId<=32)
	{
		u8 Loc_u8Port = (Copy_u8ChannedId/8) ;
		u8 Loc_u8Pin = (Copy_u8ChannedId%8)  ;

		switch (Loc_u8Port)
		{
		case PORT_A:
			*Add_pu8ChannelLevel = GET_BIT(PINA,Loc_u8Pin);
			break;
		case PORT_B:
			*Add_pu8ChannelLevel = GET_BIT(PINB,Loc_u8Pin);
			break ;
		case PORT_C:
			*Add_pu8ChannelLevel = GET_BIT(PINC,Loc_u8Pin);
			break ;
		case PORT_D:
			*Add_pu8ChannelLevel = GET_BIT(PIND,Loc_u8Pin);
			break ;
		}
	}
	else
	{
		Loc_enuReturnStatus =Dio_enuPinError;
	}
	return Loc_enuReturnStatus;

}


/*
  Write on port
  take two args Copy_u8PortID and Copy_u8Level
  return Dio_tenuErrorStatus
 */

Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortID, u8 Copy_u8Value)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	if(Copy_u8PortID<=PORT_SIZE)
	{
		switch (Copy_u8PortID)
		{
		case PORT_A:
			ASSIGN_REG(PORTA,Copy_u8Value);
			break;
		case PORT_B:
			ASSIGN_REG(PORTB,Copy_u8Value);
			break ;
		case PORT_C:
			ASSIGN_REG(PORTC,Copy_u8Value);
			break ;
		case PORT_D:
			ASSIGN_REG(PORTD,Copy_u8Value);
			break ;
		}
	}
	else
	{
		Loc_enuReturnStatus =Dio_enuPortError;
	}
	return Loc_enuReturnStatus;
}
/*
  Read from port
  take two args Copy_u8PortID and Add_pu8PortValue
  return Dio_tenuErrorStatus
 */
Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId, pu8 Add_pu8PortValue)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	if(Copy_u8PortId<=PORT_SIZE)
	{

		switch (Copy_u8PortId)
		{
		case PORT_A:
			*Add_pu8PortValue = PORTA;
			break;
		case PORT_B:
			*Add_pu8PortValue = PORTB;
			break ;
		case PORT_C:
			*Add_pu8PortValue = PORTC;
			break ;
		case PORT_D:
			*Add_pu8PortValue =PORTD;
			break ;
		}
	}
	else
	{
		Loc_enuReturnStatus =Dio_enuPinError;
	}
	return Loc_enuReturnStatus;

}
/*
  Toggle Pin
  take one arg Copy_u8ChannedId
  return Dio_tenuErrorStatus
 */
Dio_tenuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannedId)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	if(Copy_u8ChannedId<=32)
	{
		u8 Loc_u8Port= Copy_u8ChannedId/8 ;
		u8 Loc_u8Pin = Copy_u8ChannedId%8 ;
		switch (Loc_u8Port)
		{
		case PORT_A:
			TGL_BIT(PORTA,Loc_u8Pin);
			break;
		case PORT_B:
			TGL_BIT(PORTA,Loc_u8Pin);
			break ;
		case PORT_C:
			TGL_BIT(PORTA,Loc_u8Pin);
			break ;
		case PORT_D:
			TGL_BIT(PORTA,Loc_u8Pin);
			break ;
		}
	}
	else
	{
		Loc_enuReturnStatus =Dio_enuPinError;
	}
	return Loc_enuReturnStatus;

}



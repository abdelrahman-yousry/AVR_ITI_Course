/*
 * Dio.h
 *
 *  Created on: Mar 10, 2022
 *      Author: U3
 */

#ifndef DIO_H_
#define DIO_H_

/*----------DIO_Driver------------*/
/*-------enum status return----------------*/

typedef enum
{
  Dio_enuOK = 1,
  Dio_enuPinError,
  Dio_enuPortError

}Dio_tenuErrorStatus;

#define DIO_u8HIGH   		  1
#define DIO_u8LOW    		  0
#define PORT_A 		  0
#define PORT_B 		  1
#define PORT_C 		  2
#define PORT_D 		  3

#define PORT_SIZE 	  4

#define DIO_PIN_0     0
#define DIO_PIN_1     1
#define DIO_PIN_2     2
#define DIO_PIN_3     3
#define DIO_PIN_4     4
#define DIO_PIN_5     5
#define DIO_PIN_6     6
#define DIO_PIN_7     7
#define DIO_PIN_8     8
#define DIO_PIN_9     9
#define DIO_PIN_10	  10
#define DIO_PIN_11	  11
#define DIO_PIN_12	  12
#define DIO_PIN_13	  13
#define DIO_PIN_14	  14
#define DIO_PIN_15	  15
#define DIO_PIN_16	  16
#define DIO_PIN_17	  17
#define DIO_PIN_18	  18
#define DIO_PIN_19	  19
#define DIO_PIN_20	  20
#define DIO_PIN_21	  21
#define DIO_PIN_22	  22
#define DIO_PIN_23	  23
#define DIO_PIN_24	  24
#define DIO_PIN_25	  25
#define DIO_PIN_26	  26
#define DIO_PIN_27	  27
#define DIO_PIN_28	  28
#define DIO_PIN_29	  29
#define DIO_PIN_30	  30
#define DIO_PIN_31	  31

/*---------Functions---------------*/

/*
  Write on pin
  take two args Copy_u8ChannedId and Copy_u8Level
  return Dio_tenuErrorStatus
*/
//Dio_tenuErrorStatus Dio_enuWriteChannelId(u8 Copy_u8ChannedId,Dio_tenuCopyLevel Copy_u8Level);
Dio_tenuErrorStatus Dio_enuWriteChannelId(u8 Copy_u8ChannedId,u8 Copy_u8Level);

/*
  Read from pin
  take two args Copy_u8ChannedId and Add_pu8ChannelLevel
  return Dio_tenuErrorStatus
*/
Dio_tenuErrorStatus Dio_enuReadChannelId(u8 Copy_u8ChannedId, pu8 Add_pu8ChannelLevel);

/*
  Write on port
  take two args Copy_u8PortID and Copy_u8Level
  return Dio_tenuErrorStatus
*/

Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortID,u8 Copy_u8Level);
/*
  Read from port
  take two args Copy_u8PortID and Add_pu8PortValue
  return Dio_tenuErrorStatus
*/
Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId, pu8 Add_pu8PortValue);
/*
  Toggle Pin
  take two args Copy_u8PortID and Add_pu8PortValue
  return Dio_tenuErrorStatus
*/
Dio_tenuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannedId);

#endif /* DIO_H_ */

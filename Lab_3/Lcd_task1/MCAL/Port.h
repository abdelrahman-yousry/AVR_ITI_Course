/*
 * Port.h
 *
 *  Created on: Mar 15, 2022
 *      Author: U3
 */

#ifndef PORT_H_
#define PORT_H_
/**
 * Port_tenuErrorStatus --> is an enum to indicate the error status of the function
 * consists of: -
 * 1- Port_enuPinError  --> to indicate that the pin number passed to the function is wrong
 * 2- Port_enuPortError --> to indicate that the port number passed to the function is wrong
 * 3- Port_enuModeError --> to indicate that the mode passed to the function is wrong
 * 4- Port_enuOk 		--> to indicate that the arguments passed to the function is correct
 *
 **/
typedef enum
{
	Port_enuPinError,
	Port_enuPortError,
	Port_enuModeError,
	Port_enuOk
}Port_tenuErrorStatus;


/**
 * Port_tenuPinMode --> is enum to indicate the mode of the pin
 * consists of: -
 * 1-Output_enuLow			-->pin is output and low
 * 2-Output_enuHigh			-->pin is output and high
 * 3-Input_enuPullup		-->pin is input and pull up
 * 4-Input_enuHighImpedence	-->pin is input and high impedence
 **/
typedef enum
{
	Output_enuLow,
	Output_enuHigh,
	Input_enuPullup,
	Input_enuHighImpedence
}Port_tenuPinMode;

/*number of modes*/
#define NUMBER_OF_MODES		4


#define	PORT_u8HIGH  	1
#define PORT_u8LOW		0
#define PORT_u8OUTPUT 	1
#define PORT_u8INPUT 	0

/*AVR Ports*/
#define PORT_A 			0
#define PORT_B			1
#define PORT_C			2
#define PORT_D			3


/*AVR Pins*/
#define PORT_u8PIN_0		0
#define PORT_u8PIN_1		1
#define PORT_u8PIN_2		2
#define PORT_u8PIN_3		3
#define PORT_u8PIN_4		4
#define PORT_u8PIN_5		5
#define PORT_u8PIN_6		6
#define PORT_u8PIN_7		7
#define PORT_u8PIN_8		8
#define PORT_u8PIN_9		9
#define PORT_u8PIN_10	   10
#define PORT_u8PIN_11	   11
#define PORT_u8PIN_12	   12
#define PORT_u8PIN_13	   13
#define PORT_u8PIN_14	   14
#define PORT_u8PIN_15	   15
#define PORT_u8PIN_16	   16
#define PORT_u8PIN_17	   17
#define PORT_u8PIN_18	   18
#define PORT_u8PIN_19	   19
#define PORT_u8PIN_20	   20
#define PORT_u8PIN_21	   21
#define PORT_u8PIN_22	   22
#define PORT_u8PIN_23	   23
#define PORT_u8PIN_24	   24
#define PORT_u8PIN_25	   25
#define PORT_u8PIN_26	   26
#define PORT_u8PIN_27	   27
#define PORT_u8PIN_28	   28
#define PORT_u8PIN_29	   29
#define PORT_u8PIN_30	   30
#define PORT_u8PIN_31	   31


/***************Function prototypes****************/
/*Description: Function to set the direction of the pin at specific port
 *Input Paramaters:
 *					 1- Copy_u8PinNum is the pin number of the pin its range is from PIN0D to PIN31D
 * 		 			 2- Copy_u8PinDirection is the direction of the pin either PORT_u8OUTPUT or PORT_u8INUPT.
 *
 *Return type: Port_tenuErrorStatus --> to indicate the error status of the function
 *it has one of the following option: -
 *					 1- Port_enuPinError
					 2- Port_enuPortError
					 3- Port_enuModeError
				     4- Port_enuOk
 * */
Port_tenuErrorStatus Port_enuSetPinDir(u8 copy_u8PinNum, u8 copy_u8PinDir);

/**
 *Description: is used to set the direction and the value on the pin
 *Input parameters :
 *					 1- Copy_u8PinNum is the pin number of the pin its range is from PIN0D to PIN31D
 * 		   			 2- Copy_u8PinMode is the direction of the pin and its value its options are:
 * 		   					1- Output_enuLow
 * 		   					2- Output_enuHigh
 * 		   					3- Input_enuPullup
 * 		   					4- Input_enuHighImpedence
 *
 * Return: the error status of the function, it has the following options
 * 			 1- Port_enuPinError
 * 			 2- Port_enuPortError
 * 			 3- Port_enuModeError
 *			 4- Port_enuOk
 **/
Port_tenuErrorStatus PinMode(u8 copy_u8PinNum, Port_tenuPinMode enu_PinMode);

/**
 * Description: is used to set the initial value and mode for the 32 pins
 * Inputs: it takes no inputs.
 * Return: it has no returns.
 **/
void Port_vidInit(void);

#endif /* PORT_H_ */

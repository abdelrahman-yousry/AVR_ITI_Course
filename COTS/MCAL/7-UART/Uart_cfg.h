/*
 * Uart_cfg.h
 *
 *  Created on: May 19, 2022
 *      Author: U3
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_





/**********************************************************************/
//This configuration is for only the initialization
/**********************************************************************/
//**************************************
//RX  Enable:
//-----------------------------
#define RX_ENABLE								0x10
#define RX_DISABLE								0x00

#define UART_RX_CTRL							RX_ENABLE
//**************************************
//TX  Enable:
//-----------------------------
#define TX_ENABLE								0x08
#define TX_DISABLE								0x00

#define UART_TX_CTRL							TX_ENABLE

//**************************************
//BAUDE RATE:
//-----------------------------
#define UART_BAUDE_RATE_9600					9600
#define UART_BAUDE_RATE_4800					4800

#define UART_BAUDE_RATE							UART_BAUDE_RATE_9600

//**************************************
//RX Complete Interrupt Enable:
//-----------------------------
#define UART_NO_INTERRUPT 						1
#define UART_RX_COMPLETE_INTERRUPT_ENABLE 		2
/*Select one of the following options:
-------------------------------------
1- UART_NO_INTERRUPT
2- UART_RX_COMPLETE_INTERRUPT_ENABLE
*/
#define UART_RX_COMPLETE_INTERRUPT 				UART_NO_INTERRUPT
//**************************************

//**************************************
//TX Complete Interrupt Enable:
//-----------------------------
#define UART_NO_INTERRUPT 						1
#define UART_TX_COMPLETE_INTERRUPT_ENABLE 		2
/*Select one of the following options:
-------------------------------------
1- UART_NO_INTERRUPT
2- UART_TX_COMPLETE_INTERRUPT_ENABLE
*/
#define UART_TX_COMPLETE_INTERRUPT 				UART_NO_INTERRUPT
//**************************************

//**************************************
//UDRE Interrupt Enable:
//-----------------------------
#define UART_NO_INTERRUPT 						1
#define UART_UDRE_INTERRUPT_ENABLE 				2
/*Select one of the following options:
-------------------------------------
1- UART_NO_INTERRUPT
2- UART_UDRE_INTERRUPT_ENABLE
*/
#define UART_UDRE_INTERRUPT 					UART_NO_INTERRUPT
//**************************************

//**************************************
//UART Mode Select:
//-----------------------------
#define UART_ASYNCHRONOUS_OPERATION 			0x00
#define UART_SYNCHRONOUS_OPERATION 				0x40
/*Select one of the following options:
-------------------------------------
1- UART_ASYNCHRONOUS_OPERATION
2- UART_SYNCHRONOUS_OPERATION
*/
#define UART_MODE 								UART_ASYNCHRONOUS_OPERATION
//**************************************

//**************************************
//UART Parity Mode Select:
//-----------------------------
#define UART_PARITY_DISABLED 					0x00
#define UART_EVEN_PARITY 						0x20
#define UART_ODD_PARITY 						0x30
/*Select one of the following options:
-------------------------------------
1- UART_PARITY_DISABLED
2- UART_EVEN_PARITY
3- UART_ODD_PARITY
*/
#define UART_PARITY_MODE						 UART_PARITY_DISABLED
//**************************************

//**************************************
//UART Stop Bits Number:
//-----------------------------
#define UART_1_STOP_BIT 						0x00
#define UART_2_STOP_BIT 						0x08
/*Select one of the following options:
-------------------------------------
1- UART_1_STOP_BIT
2- UART_2_STOP_BIT
*/
#define UART_STOP_BIT_NUMBER UART_1_STOP_BIT
//**************************************

//**************************************
//UART Character Size:
//-----------------------------
#define UART_CHAR_SIZE_5_BITS 					1
#define UART_CHAR_SIZE_6_BITS 					2
#define UART_CHAR_SIZE_7_BITS 					3
#define UART_CHAR_SIZE_8_BITS 					4
#define UART_CHAR_SIZE_9_BITS 					5
/*Select one of the following options:
-------------------------------------
1- UART_CHAR_SIZE_5_BITS
2- UART_CHAR_SIZE_6_BITS
3- UART_CHAR_SIZE_7_BITS
4- UART_CHAR_SIZE_8_BITS
5- UART_CHAR_SIZE_9_BITS
*/
#define UART_CHAR_SIZE UART_CHAR_SIZE_8_BITS
//**************************************

//**************************************
//UART Clock Polarity:
//-----------------------------
#define UART_TRANSMIT_RISING_RECEIVE_FALLING 	0x00
#define UART_TRANSMIT_FALLING_RECEIVE_RISING 	0x01
/*Select one of the following options:
-------------------------------------
1- UART_TRANSMIT_RISING_RECEIVE_FALLING
2- UART_TRANSMIT_FALLING_RECEIVE_RISING
*/
#define UART_CLOCK_POLARITY 					UART_TRANSMIT_RISING_RECEIVE_FALLING
//**************************************


#endif /* UART_CFG_H_ */

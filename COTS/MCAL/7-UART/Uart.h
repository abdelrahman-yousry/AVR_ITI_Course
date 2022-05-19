/*
 * Uart.h
 *
 *  Created on: Apr 1, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef UART_H_
#define UART_H_

typedef void (*pcbf)(void);

typedef enum
{
	Uart_enuOk,
	Uart_enuNok,
	Uart_enuNullPtr,
}Uart_tenuErrorStatus;

typedef enum
{
	Tx_InterruptEnbaled,
	Tx_InterruptDisbaled,
	Rx_InterruptEnbaled,
	Rx_InterruptDisbaled,
}Uart_enuInterrCtrl;

void Uart_enuInit(void);
/*************Synchronous Function*******************/
Uart_tenuErrorStatus Uart_enuSendByteSync(u16 Copy_u16Byte);
Uart_tenuErrorStatus Uart_enuRecieveByteSync(pu16 Copy_u16Byte);
/************Asynchronous function******************/
void Uart_enuSendByteAsync(u16 Copy_u16Byte);
void Uart_enuRecieveByteAsync(pu16 Copy_pu16Byte);

Uart_tenuErrorStatus Uart_enuInterruptCtrl(Uart_enuInterrCtrl Copy_enuIntCtrl);


/**REG CALL BACK FUNCTION**/
Uart_tenuErrorStatus Uart_enuUdreRegCbf(pcbf);
Uart_tenuErrorStatus Uart_enuTxRegCbf(pcbf);
Uart_tenuErrorStatus Uart_enuRxRegCbf(pcbf);

#endif /* UART_H_ */

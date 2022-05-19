/*
 * Uart.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Bit_utils.h"
#include "Port.h"
#include <avr/interrupt.h>
#include "Registers_prv.h"
#include "Uart.h"
#include "Uart_cfg.h"
#include "Uart_prv.h"
#include "Gie.h"


pu16 Uart_gpRecievedVal=0;

pcbf Uart_TxCbf;
pcbf Uart_RxCbf;
pcbf Uart_UdreCbf;

void Uart_enuInit(void)
{
	u8 Reg_u8Data = 0b10000000;

#if UART_RX_CTRL == RX_ENABLE
	UCSRB |= RX_ENABLE;
#endif
#if UART_TX_CTRL == TX_ENABLE
	UCSRB |= TX_ENABLE;
#endif

#if UART_RX_COMPLETE_INTERRUPT == UART_RX_COMPLETE_INTERRUPT_ENABLE
	SET_BIT(SREG,7);
	SET_BIT(UCSRB,7);
#endif
#if UART_TX_COMPLETE_INTERRUPT == UART_TX_COMPLETE_INTERRUPT_ENABLE
	SET_BIT(SREG,7);
	SET_BIT(UCSRB,6);
#endif
#if UART_UDRE_INTERRUPT == UART_UDRE_INTERRUPT_ENABLE
	SET_BIT(SREG,7);
	SET_BIT(UCSRB,5);
#endif
	//UART Character Size
#if UART_CHAR_SIZE == UART_CHAR_SIZE_5_BITS
	CLR_BIT(UCSRB,2);
	CLR_BIT(Reg_u8Data,2);
	CLR_BIT(Reg_u8Data,1);
#elif UART_CHAR_SIZE == UART_CHAR_SIZE_6_BITS
	CLR_BIT(UCSRB,2);
	CLR_BIT(Reg_u8Data,2);
	SET_BIT(Reg_u8Data,1);
#elif UART_CHAR_SIZE == UART_CHAR_SIZE_7_BITS
	CLR_BIT(UCSRB,2);
	SET_BIT(Reg_u8Data,2);
	CLR_BIT(Reg_u8Data,1);
#elif UART_CHAR_SIZE == UART_CHAR_SIZE_8_BITS
	CLR_BIT(UCSRB,2);
	SET_BIT(Reg_u8Data,2);
	SET_BIT(Reg_u8Data,1);
#elif UART_CHAR_SIZE == UART_CHAR_SIZE_9_BITS
	SET_BIT(UCSRB,2);
	SET_BIT(Reg_u8Data,2);
	SET_BIT(Reg_u8Data,1);
#endif
	Reg_u8Data |=UART_MODE
			|UART_PARITY_MODE
			|UART_STOP_BIT_NUMBER
			|UART_CLOCK_POLARITY;
	UCSRC |= Reg_u8Data;
#if UART_BAUDE_RATE == UART_BAUDE_RATE_9600
	UBRRH = 0;
	UBRRL = 51;
#endif
#if UART_BAUDE_RATE == UART_BAUDE_RATE_4800
	UBRRH = 0;
	UBRRL = 103;
#endif
	Gie_vidInterruptEnable();
}
Uart_tenuErrorStatus Uart_enuSendByteSync(u16 Copy_u16Byte)
{
	Uart_tenuErrorStatus Loc_u8StatusError ;
	u16 TimeOut = 500 ;
	while (TimeOut-- && !(UCSRA &UART_GET_TXC_FLAG))
	{
		UDR = Copy_u16Byte;
	}
	if((UCSRA &UART_GET_TXC_FLAG) == 1)
	{
		Loc_u8StatusError = Uart_enuOk;
	}
	else
	{
		Loc_u8StatusError = Uart_enuNok;
	}
	return Loc_u8StatusError;
}
Uart_tenuErrorStatus Uart_enuRecieveByteSync(pu16 Copy_u16Byte)
{
	Uart_tenuErrorStatus Loc_u8StatusError ;
	u16 TimeOut = 500 ;
	while (TimeOut-- && !(UCSRA &UART_GET_RXC_FLAG))
	{
		*Copy_u16Byte = UDR;
	}
	if((UCSRA &UART_GET_RXC_FLAG) == 1)
	{
		Loc_u8StatusError = Uart_enuOk;
	}
	else
	{
		Loc_u8StatusError = Uart_enuNok;
	}
	return Loc_u8StatusError;
}
void Uart_enuSendByteAsync(u16 Copy_u16Byte)
{
	UDR = Copy_u16Byte;
	SET_BIT(SREG,7);
	SET_BIT(UCSRB,6);
}
void Uart_enuRecieveByteAsync(pu16 Copy_u16Byte)
{
	Uart_gpRecievedVal = Copy_u16Byte;
	SET_BIT(SREG,7);
	SET_BIT(UCSRB,7);
}
Uart_tenuErrorStatus Uart_enuInterruptCtrl(Uart_enuInterrCtrl Copy_enuIntCtrl)
{
	switch (Copy_enuIntCtrl)
	{
	case Tx_InterruptEnbaled:
		SET_BIT(SREG,7);
		SET_BIT(UCSRB,6);
		break;
	case Tx_InterruptDisbaled:
		CLR_BIT(UCSRB,6);
		break;
	case Rx_InterruptEnbaled:
		CLR_BIT(UCSRB,7);
		break;
	case Rx_InterruptDisbaled:

		break;
	}
}
/*************************Register the call back func****************************/
Uart_tenuErrorStatus Uart_enuUdreRegCbf(pcbf Uart_UdreCbfNotify)
{
	Uart_tenuErrorStatus Loc_ErrorStatus = Uart_enuOk;
	if(Uart_UdreCbfNotify)
	{
		Uart_UdreCbf = Uart_UdreCbfNotify;
	}
	else
	{
		Loc_ErrorStatus = Uart_enuNullPtr;
	}
	return Loc_ErrorStatus;
}
Uart_tenuErrorStatus Uart_enuTxRegCbf(pcbf Uart_TxCbfNotify)
{
	Uart_tenuErrorStatus Loc_ErrorStatus = Uart_enuOk;
	if(Uart_TxCbfNotify)
	{
		Uart_TxCbf = Uart_TxCbfNotify;
	}
	else
	{
		Loc_ErrorStatus = Uart_enuNullPtr;
	}
	return Loc_ErrorStatus;
}
Uart_tenuErrorStatus Uart_enuRxRegCbf(pcbf Uart_RxCbfNotify)
{
	Uart_tenuErrorStatus Loc_ErrorStatus = Uart_enuOk;
	if(Uart_RxCbfNotify)
	{
		Uart_RxCbf = Uart_RxCbfNotify;
	}
	else
	{
		Loc_ErrorStatus = Uart_enuNullPtr;
	}
	return Loc_ErrorStatus;
}


/*******************Call the call back funcs in the handlers*******************/
ISR(USART_RXC_vect)
{
	if(Uart_RxCbf != NULL)
	{
		Uart_RxCbf();
	}
}

ISR(USART_TXC_vect)
{
	if(Uart_TxCbf != NULL)
	{
		Uart_TxCbf();
	}
}

ISR(USART_UDRE_vect)
{
	if(Uart_UdreCbf != NULL)
	{
		Uart_UdreCbf();
	}
}

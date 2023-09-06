/*
 * UART_Interface.h
 *
 *  Created on: Jun 7, 2023
 *      Author: hikal
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void  UART_voidInit(void);

void  UART_voidTransmit(u8 *Copyu8_Frame,u8 Copyu8_BlockSize);

u8  UART_voidRecieve(void);

u8   USART_u8ReceiveTimeout(u32 Copy_u32Timeout);

void UART_voidReciveAsyn( u8 *Copy_pu8Reading   , u8 Copy_SizeIndex ,  void(*Copy_PvNotificationFunction)(void));

void USART1_IRQHandler(void);



#endif /* UART_INTERFACE_H_ */

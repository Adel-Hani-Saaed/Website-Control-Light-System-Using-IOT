/*
 * UART_Prog.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Dina
 */


#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"stm32f401xx.h"
#include "STM32F4xx_Device_Header.h"
#include "CORE_NVIC_Interface.h"
#include"MCAL_GPIO_Interface.h"

#include"UART_Config.h"
#include"UART_Interface.h"
#include"UART_Private.h"



/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u8 * UART1_pu16AsynchReading = NULL;

static u8 UART_u8ArraySize;				/*Global variable to carry Number of chars*/

static u8 UART_u8Index = 0;				/*Global variable to carry the current conversion index */
static void (* UART1_CallBack) (void) = NULL ;

u8  G_u8AMessage[10] = {0};

void  UART_voidInit(void)
{
	//Enable Tx
	SET_BIT(UART1->CR1,3);
	//Enable Rx
	SET_BIT(UART1->CR1,2);
	// select Word length (8-bit)
	CLEAR_BIT(UART1->CR1,12);
	//select Buad Rate (9600)->BRR - CLK ->16MHz
	//	UART1->BRR=0x683 ;



	//select Buad Rate (115200)->BRR - CLK ->16MHz
	UART1->BRR=0x8B ;

	//Enable UART
	SET_BIT(UART1->CR1,13);



}

void  UART_voidTransmit(u8 *Copyu8_Frame,u8 Copyu8_BlockSize)
{

	for(u8 i=0;i<Copyu8_BlockSize;i++)
	{
		while(!GET_BIT(UART1->SR,6));
		UART1->DR=Copyu8_Frame[i];
	}
}
u8  UART_voidRecieve(void)
{
	static u8 Copyu8_RChar;

	while((!GET_BIT(UART1->SR,5)));
	Copyu8_RChar=(UART1->DR & 0xFF);

	return  Copyu8_RChar;
}

u8   USART_u8ReceiveTimeout(u32 Copy_u32Timeout)
{
	u16 timeout = 0;
	u8 Loc_u8ReceiveData = 0;
	while((GET_BIT((UART1 -> SR), 5)) == 0)
	{
		timeout++;
		if(timeout == Copy_u32Timeout)
		{
			Loc_u8ReceiveData = 255;
			break;
		}
	}
	if(Loc_u8ReceiveData != 255)
	{
		Loc_u8ReceiveData = UART1 -> DR;
	}
	return Loc_u8ReceiveData;
}

void UART_voidReciveAsyn( u8 *Copy_pu8Reading   , u8 Copy_SizeIndex ,  void(*Copy_PvNotificationFunction)(void))
{
	if (Copy_pu8Reading != NULL || Copy_PvNotificationFunction != NULL)
	{

		UART1_pu16AsynchReading = Copy_pu8Reading;
		UART_u8ArraySize = Copy_SizeIndex;
		UART1_CallBack= Copy_PvNotificationFunction ;

		/*Enable NVIC*/
		COR_NVIC_vEnableInterrupt(USART1_IRQn);

		/*Enable Interrupt*/
		SET_BIT(UART1->CR1,5);
	}
}


void USART1_IRQHandler(void)
{

	UART1_pu16AsynchReading[UART_u8Index] = (UART1->DR);

	UART_u8Index++;

	if (UART_u8Index == UART_u8ArraySize)
	{
		UART_u8Index = 0 ;
		UART1_CallBack();
	}

	/*Clear flag RXEN*/
	CLEAR_BIT(UART1->SR,5);
}


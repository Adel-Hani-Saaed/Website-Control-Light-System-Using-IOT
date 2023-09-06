#include"LBIT_MATH.h"
#include"STD_TYPES.h"
#include <stdlib.h> // for itoa

#include "stm32f401xx.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_GPIO_Interface.h"
#include "MCAL_STK_Interface.h"
#include "UART_Interface.h"
#include "ESP_interface.h"


int main()
{
	u8 data;

	MCL_RCC_vInitSysClk(&RCC_G_Config); // Initialize the system clock

	MCL_RCC_vEnablePeriphClk(AHB1_BUS, 0 );	 //Enable POERTA

	MCL_RCC_vEnablePeriphClk(APB2_BUS, 4 );  //Enable UART

	MCL_STK_vInit(&STK_G_Config); // Initialize the SysTick timer


	GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_MODE_AF_PP);
	GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_MODE_AF_PP);
	GPIO_voidSetPinALTF(GPIO_PORTA, GPIO_PIN9, GPIO_AF7_USART1_USART2_SPI1);
	GPIO_voidSetPinALTF(GPIO_PORTA, GPIO_PIN10,GPIO_AF7_USART1_USART2_SPI1);

	UART_voidInit();

	GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUT_PP);

	ESP_voidInit();

	ESP_voidConnctEspRouter("write Your SSID","Write Your Password");

	ESP_voidConnectEspServer("TCP","Write Your IP Website","80");

	ESP_u8ExecuteHttpRequest("GET http://Write Your Name Domain /Write Name File will be have the Data" , &data );


	if (data == '1')
	{
		GPIO_voidSetPinVal(GPIO_PORTA, GPIO_PIN1, PIN_SET);
	}
	else if (data == '0')
	{
		GPIO_voidSetPinVal(GPIO_PORTA, GPIO_PIN1, PIN_RESET);
	}

	while(1)
	{


	}

	return 0;
}

/*
 * ESP_program.c
 *
 *  Created on: Sep 3, 2023
 *      Author: A-plus store
 */
#include "BIT_MATH.h"


#include "MCAL_GPIO_Interface.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_STK_Interface.h"
#include "UART_Interface.h"
#include "ESP_interface.h"


char Quotes	[]	 = "\""		;
char Comma 	[]	 = {","};
char Closing[]	 = "\r\n"	;
u8 Local_u8Response1[100] ={0};


void ESP_voidInit(void)
{
	u8 Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* Stop ECHO */
		UART_voidTransmit("ATE0\r\n" , 6);
		Local_u8Result = voidEspValidateCmd();
	}

	Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* Set station mode */
		UART_voidTransmit("AT+CWMODE=1\r\n",20);
		Local_u8Result = voidEspValidateCmd();
	}

}


void ESP_voidConnctEspRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword)
{
	u8 Local_u8ValidFlag = 0;

	char Router_Command[100];

	/* Empty the pointer that strcat was using last time as it saves at the same location and data may interference*/
	strcpy(Router_Command, "");

	/*catenating strings to be : "AT+CWJAP_CUR="Copy_u8StrSsid","Copy_u8StrPassword""*/
	strcat(Router_Command, "AT+CWJAP_CUR=");

	strcat(Router_Command, Quotes);
	strcat(Router_Command, Copy_u8StrSsid);
	strcat(Router_Command, Quotes);

	strcat(Router_Command, Comma);

	strcat(Router_Command, Quotes);
	strcat(Router_Command, Copy_u8StrPassword);
	strcat(Router_Command, Quotes);

	strcat(Router_Command, Closing);

	while(Local_u8ValidFlag == 0)
	{
		/*Connect to WiFi of name Copy_u8StrSsid and password Copy_u8StrPassword*/
		UART_voidTransmit(Router_Command , 100 );
		/*	Check command is done right
			AT+CWJAP_CUR="SSID","Pass" returns OK if all is okay*/
		Local_u8ValidFlag = voidEspValidateCmd2();
	}
}


void ESP_voidConnectEspServer(char* Copy_u8StrMode, char* Copy_u8StrIP, char* Copy_u8StrPort)
{
	u8 Local_u8ValidFlag = 0;

	char Server_Command[42];

	strcpy(Server_Command, "");

	strcat(Server_Command, "AT+CIPSTART=");

	strcat(Server_Command, Quotes);
	strcat(Server_Command, Copy_u8StrMode);
	strcat(Server_Command, Quotes);

	strcat(Server_Command, Comma);

	strcat(Server_Command, Quotes);
	strcat(Server_Command, Copy_u8StrIP);
	strcat(Server_Command, Quotes);

	strcat(Server_Command, Comma);

	strcat(Server_Command, Copy_u8StrPort);

	strcat(Server_Command, Closing);

	while(Local_u8ValidFlag == 0)
	{
		UART_voidTransmit(Server_Command , 42 );

		Local_u8ValidFlag = voidEspValidateCmd3();
	}
}







void ESP_u8ExecuteHttpRequest(char* Copy_u8StrRequest , char* Copy_u8Return )
{
	u8 Local_u8ValidFlag = 0;
	char Send_Command[25];
	char Request_Command[(strlen(Copy_u8StrRequest) + 2)];
	char Temp_str[2];

	/* Empty the pointer that strcat was using last time as it saves at the same location and data may interference*/
	strcpy(Send_Command, "AT+CIPSEND=");

	/* get length request and add 2 for \r\n */
	u8 NumberOfLetters = strlen(Copy_u8StrRequest) + 2;     //48


	/*Convert the number of the request letters to String  why convert to string ->> for can using the strcat() function this function must the argument is string */
	sprintf(Temp_str, "%d", NumberOfLetters);			    //"48"

	strcat(Send_Command, Temp_str);							//"AT+CIPSEND=48"

	strcat(Send_Command, Closing);							//"AT+CIPSEND=48\r\n"

	while(Local_u8ValidFlag == 0)
	{
		UART_voidTransmit(Send_Command,25);

		Local_u8ValidFlag = voidEspValidateCmd5();
	}


	/*********************************************************/
	/***********		SEND THE GET REQUEST 		  ********/
	/*********************************************************/

	Local_u8ValidFlag = 0;
	strcpy(Request_Command, "");
	strcat(Request_Command, Copy_u8StrRequest);
	strcat(Request_Command, Closing);

	while(Local_u8ValidFlag == 0)
	{
		UART_voidTransmit(Request_Command, 48);

		Local_u8ValidFlag = voidEspValidateCmd4();
	}

	u8 Temp_char;

	Temp_char = Local_u8Response1[50];

	(* Copy_u8Return) = Temp_char ;

}




u8 voidEspValidateCmd(void)
{
	u8 Local_u8Response[100] = {0};
	u8 Result = 0;


	while (1)
	{
		UART_voidReciveAsyn(Local_u8Response, 2 ,&Notifiactoin);

		/* Check if Ok */
		if (Local_u8Response[0] == 'O' && Local_u8Response[1] == 'K')
		{
			Result = 1;
			break;
		}
	}

	return Result;
}

u8 voidEspValidateCmd2(void)
{
	u8 Local_u8Response[100] = {0};
	u8 Result = 0;


	while (1)
	{
		UART_voidReciveAsyn(Local_u8Response,51,&Notifiactoin);

		/* Check if Ok */
		if (Local_u8Response[48] == 'O' && Local_u8Response[49] == 'K')
		{
			Result = 1;
			break;
		}
	}

	return Result;
}


u8 voidEspValidateCmd3(void)
{
	u8 Local_u8Response[100] = {0};
	u8 Result = 0;
	static u8 Local = 0 ;
	if (Local == 0)
	{
		while (1)
		{
			UART_voidReciveAsyn(Local_u8Response, 2 ,&Notifiactoin);

			/* Check if Ok */
			if (Local_u8Response[0] == 'O' && Local_u8Response[1] == 'K')
			{
				Result = 1;
				break;
			}
		}
		Local = 1 ;
	}

	else
	{
		while (1)
		{
			UART_voidReciveAsyn(Local_u8Response, 100 ,&Notifiactoin);

			/* Check if Ok */
			if (Local_u8Response[64] == 'O' && Local_u8Response[65] == 'K')
			{
				Result = 1;
				break;
			}
		}
	}
	return Result;
}



u8 voidEspValidateCmd5(void)
{
	u8 Local_u8Response[100] = {0};
	u8 Result = 0;


	while (1)
	{
		UART_voidReciveAsyn(Local_u8Response, 2 ,&Notifiactoin);

		/* Check if Ok */
		if (Local_u8Response[0] == 'O' && Local_u8Response[1] == 'K')
		{
			Result = 1;
			break;
		}
	}

	return Result;
}


u8 voidEspValidateCmd4(void)
{
	u8 Result = 0;


	while (1)
	{

		UART_voidReciveAsyn(Local_u8Response1,100,&Notifiactoin);

		/* Check if Ok */
		if (Local_u8Response1[50] == '1' || Local_u8Response1[50] == '0' )
		{
			Result = 1;
			break;
		}
	}

	return Result;
}


void Notifiactoin(void)
{
}



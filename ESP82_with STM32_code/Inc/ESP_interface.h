/*
 * ESP_interface.h
 *
 *  Created on: Sep 3, 2023
 *      Author: A-plus store
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_


/*define recieving timout for each command that if it exceeded it means no more data*/
/*It varies depending on the router and server and also Clock freq, you'll need to try it*/
#define ECHO_TIMEOUT		100
#define MODE_TIMEOUT		150
#define ROUTER_TIMEOUT		35000
#define SERVER_TIMEOUT		50000
#define PREREQUEST_TIMEOUT	200
#define REQUEST_TIMEOUT		50000



void ESP_voidInit(void);

void ESP_voidConnctEspRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword);

void ESP_voidConnectEspServer(char* Copy_u8StrMode, char* Copy_u8StrIP, char* Copy_u8StrPort);

void ESP_u8ExecuteHttpRequest(char* Copy_u8StrRequest , char* Copy_u8Return );

//u8 u8ValidateCmd(u32 Copy_u32timeout);

u8 voidEspValidateCmd(void);

u8 voidEspValidateCmd2(void);

u8 voidEspValidateCmd3(void);
u8 voidEspValidateCmd4(void);
u8 voidEspValidateCmd5(void);



void Notifiactoin(void);

#endif /* ESP_INTERFACE_H_ */

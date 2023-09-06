/*
 * stm32f401xx.h
 *
 *  Created on: May 29, 2023
 *      Author: dina
 */

#ifndef STM32F401XX_H_
#define STM32F401XX_H_

/*Define the peripheral base address*/
/*Where to find the peripheral
 * 1-core  peripheral
 * -->programming  manual
 * -->user guide
 *
 * 2-vendor peripheral(external)
 * -->Reference manual
 *
 * */
/***************RCC**********************/
#define RCC_u32_BASE_ADDRESS      0x40023800

typedef struct MRCC
{

volatile u32   CR;
volatile u32   PLLCFGR;
volatile u32   CFGR;
volatile u32   CIR;
volatile u32   AHB1RSTR;
volatile u32   AHB2RSTR;
volatile u32   Reserved1;
volatile u32   Reserved2;
volatile u32   APB1LPSTR;
volatile u32   APB2LPSTR;
volatile u32   Reserved3;
volatile u32   Reserved4;
volatile u32   AHB1ENR;
volatile u32   AHB2ENR;
volatile u32   Reserved5;
volatile u32   Reserved6;
volatile u32   APB1ENR;
volatile u32   APB2ENR;
volatile u32   Reserved7;
volatile u32   Reserved8;
volatile u32   AHB1LPENR;
volatile u32   AHB2LPENR;
volatile u32   Reserved9;
volatile u32   Reserved10;
volatile u32   APB1LPENR;
volatile u32   APB2LPENR;
volatile u32   Reserved11;
volatile u32   Reserved12;
volatile u32   BDCR;
volatile u32   CSR;
volatile u32   Reserved13;
volatile u32   Reserved14;
volatile u32   SSCGR;
volatile u32   PLLI2SCFGR;
volatile u32   Reserved15;
volatile u32   DCKCFGR;

}RCC_RegDef_t;

#define  RCC  ((RCC_RegDef_t*)RCC_u32_BASE_ADDRESS)


/***************GPIO***********************/
#define GPIOA_u32_BASE_ADDRESS      0x40020000
#define GPIOB_u32_BASE_ADDRESS      0x40020400
#define GPIOC_u32_BASE_ADDRESS      0x40020800



typedef struct GPIO
{

volatile u32   MODER ;
volatile u32   OTYPER;
volatile u32   OSPEEDER ;
volatile u32   PUPDR;
volatile u32   IDR;
volatile u32   ODR;
volatile u32   BSRR;
volatile u32   LCKR;
volatile u32   AFRL;
volatile u32   AFRH;

}GPIO_RegDef_t;

#define  GPIOA  ((GPIO_RegDef_t*)(GPIOA_u32_BASE_ADDRESS))
#define  GPIOB  ((GPIO_RegDef_t*)(GPIOB_u32_BASE_ADDRESS))
#define  GPIOC  ((GPIO_RegDef_t*)(GPIOC_u32_BASE_ADDRESS))

/***********************NVIC*********************/

#define NVIC_u32_BASE_ADRESS   0xE000E100
#define SCB_u32_BASE_ADRESS    0xE000E008
#define SCB_u32_AIRCR    (SCB_u32_BASE_ADRESS + 0x0C)

typedef struct MNVIC
{

volatile u32 ISER[8];
volatile u32 Reserved1[24];//because we have 96 bytes difference between ISER &ICER
volatile u32 ICER[8];
volatile u32 Reserved2[24];
volatile u32 ISPR[8];
volatile u32 Reserved3[24];
volatile u32 ICPR[8];
volatile u32 Reserved4[24];
volatile u32 IABR[8];
volatile u32 Reserved5[56];
volatile u8 IPR[240];
volatile u32 Reserved6[580];
volatile u32 STIR;



}NVIC_RegDef_t;

#define   NVIC   ((NVIC_RegDef_t*)(NVIC_u32_BASE_ADRESS))
#define   SCB       *((volatile u32*)SCB_u32_AIRCR)

#define   SCB_KEY    0xFA050000
/********************************EXTI****************/
#define EXTI_u32_BASE_ADDRESS      0x40013C00
//#define SYSCFG
typedef struct MEXTI
{
volatile u32 IMR;
volatile u32 EMR;
volatile u32 RTSR;
volatile u32 FTSR;
volatile u32 SWIER;
volatile u32 PR;
}EXTI_RegDef_t;
#define   EXTI   ((EXTI_RegDef_t*)(EXTI_u32_BASE_ADRESS))
/*************************SYSTICK**************************/
#define SYSTICK_u32_BASE_ADDRESS   0xE000E010



typedef struct MSYSTICK
{

volatile u32 CTRL;
volatile u32 LOAD;
volatile u32 VAL;
volatile u32 CALIB;

}SYSTICK_RegDef_t;

#define SYSTICK ((SYSTICK_RegDef_t*)SYSTICK_u32_BASE_ADDRESS)
/********************************DMA*******************************/
#define DMA1_BASE_ADDRESS  0x40026000
#define DMA2_BASE_ADDRESS  0x40026400

typedef struct stream
{
	volatile u32 CR;
	volatile u32 NDTR;
	volatile u32 PAR;
	volatile u32 M0AR;
	volatile u32 M1AR;
	volatile u32 FCR;

}channel;



typedef struct DMA
{
	volatile u32 LISR;
	volatile u32 HISR;
	volatile u32 LIFCR;
	volatile u32 HIFCR;
	channel s[8];

}DMA_Reg_Def;

#define DMA1 ((DMA_Reg_Def*)DMA1_BASE_ADDRESS)
#define DMA2 ((DMA_Reg_Def*)DMA2_BASE_ADDRESS)

/*************************UART**************/
#define UART1_BASE_ADDRESS   0x40011000
#define UART2_BASE_ADDRESS   0x40004400
#define UART6_BASE_ADDRESS   0x40011400

typedef struct  UART
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
    volatile u32 CR3;
    volatile u32 GTPR;

}UART_RegDef_t;

#define UART1 ((UART_RegDef_t*)UART1_BASE_ADDRESS)
#define UART2 ((UART_RegDef_t*)UART2_BASE_ADDRESS)
#define UART6 ((UART_RegDef_t*)UART6_BASE_ADDRESS)


#endif /* STM32F401XX_H_ */

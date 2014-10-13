
/***************************************************************************************
****************************************************************************************
* FILE		: mcu.h
* Description	: 
*			  
* Copyright (c) 2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		WANG SHAOWEI	2007/04/29	Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _MCU_H_
#define _MCU_H_
//#include "reg52x2.h"

/*���е�ģʽ�����ںܶ�51��Ƭ������6clockģʽ*/
#define SPEEDUP



typedef enum
{
#ifdef SPEEDUP
	TimerInterval35H = 0x04,			/*����ģʽ��*/
	TimerInterval33H = 0x10,
	TimerInterval25H = 0x4C,
	TimerInterval20H = 0x70,
	TimerInterval10H = 0xB8,
	TimerInterval5H = 0xDC	
#else
	TimerInterval35H = 0x10,			/*��ͨģʽ��*/
	TimerInterval33H = 0x4C,
	TimerInterval25H = 0x70,
	TimerInterval20H = 0xB8,
	TimerInterval10H = 0xDC,
	TimerInterval5H = 0xEE	
#endif
}TimerInterval;

typedef enum
{
	UART_RATE48 = 0xF4,		/*���岨����4800bps*/
	UART_RATE96 = 0xFA,		/*���岨����9600bps*/                
	UART_RATE192 = 0xFD,		/*���岨����19200bps*/	
	UART_RATE576 = 0xFF,		/*���岨����57600bps*/		
	UART_RATE1152 = 0x00		/*���岨����115200bps*/
}UartBaudrate;

typedef enum
{
	TimerMode0 = 0x00,			/*13bit ��ʱ��ģʽ*/
	TimerMode1 = 0x01,			/*16bit ��ʱ��ģʽ*/
	TimerMode2 = 0x02,			/*8bit �Զ�����ģʽ*/
	TimerMode3 = 0x03			/*8bit˫��ʱ��ģʽ*/
}TimerMode;



#define INT_EA	EA
#define INT_ET2	ET2
#define INT_ES	ES
#define INT_ET1	ET1
#define INT_EX1	EX1
#define INT_ET0	ET0
#define INT_EX0	EX0

#define INTERRUPT_ENABLE()		INT_EA = TRUE
#define INTERRUPT_DISABLE()		INT_EA = FALSE
#define INTERRUPT_GET()			INT_EA
#define INTERRUPT_SET(u1)		INT_EA = (u1>0)	



extern void port_init(void);

extern void Interrupt_priority_init(void);

extern void mode_init(void);

extern void uart_init(UartBaudrate BaudRate);

extern void uart_put(U8 u8);

void timer2_init(U8 Enable, TimerInterval eTimerInterval);


#endif /*_MCU_H_*/


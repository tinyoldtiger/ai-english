
/***************************************************************************************
****************************************************************************************
* FILE		: uart.c
* Description	: uart
*			  
* Copyright (c) 2003~2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   1.0		Wang Shaowei	2003/07/16	Initial Version (MCU System)
   2.0		Wang Shaowei	2005/06/01	MS2
   3.0		Wang Shaowei	2007/03/11	MS3
   
****************************************************************************************
****************************************************************************************/


/*
UART所需的定时器由T1或T2提供,而不是T0

	SCON:串行口控制寄存器
	SM0(9F),SM1(9E)
		SM0,SM1|工作方式|        说明 			|所用波特率 
        	   0,0     |  方式0       |同步移位寄存器|       Fosc/12                 
      		   0,1     |  方式1       | 10位异步收发       |由定时器控制 
       	   1,0     |  方式2       | 11位异步收发       |Fosc/32或Fosc/64     
       	   1,1     |  方式3       | 11位异步收发       |由定时器控制
       SM2(9D)		多机通信0:单机，1:多机
       REN(9C)		接收控制0:禁止接收，1:允许接收    
       TB8	(9B)		发送数据第九位
       RB8	(9A)		接收数据第九位
       TI	(99)		发送中断标记
       RI	(98)		接收中断标志
*/

#include "string.h"
#include "common.h"


/*==================================================================
* Function	: uart_put_char
* Description	: send U8 as char through uart
			  For example:val = 0xAB,the function will send 'A','B'
* Input Para	: U8 val	: the data to send
* Output Para	: void
* Return Value: void
==================================================================*/
void uart_put_char(U8 val)
{
	uart_put(uty_hex2ascii(val >> 4));
	uart_put(uty_hex2ascii(val & 0x0F));
	uart_put(' ');
}

/*==================================================================
* Function	: uart_send_string
* Description	: send string through uart, when len is 0, detect string length automatically
* Input Para	: U8* pData	: string to send
			  U8 len		: string length, when len is 0, detect string length automatically
* Output Para	: void
* Return Value: void
==================================================================*/
void uart_put_string(U8* pData, U8 len)
{
	U8 i;
	

	
	if(len)
	{
		i = len;
		while(i--)
		{
			uart_put(*pData++);
		}
	}
	else
	{
		i = strlen(pData);
		while(i--)
		{
			if(*pData == 0x0A)
			{
				uart_put(0x0D);
			}
			uart_put(*pData++);
		}
	}
}


/*==================================================================
* Function	: uart_process
* Description	: The UART process
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void uart_process(U8 u8)
{
	MSG_SEND_MSG(MSG_KEY, u8);
}




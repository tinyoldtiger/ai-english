
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
UART����Ķ�ʱ����T1��T2�ṩ,������T0

	SCON:���пڿ��ƼĴ���
	SM0(9F),SM1(9E)
		SM0,SM1|������ʽ|        ˵�� 			|���ò����� 
        	   0,0     |  ��ʽ0       |ͬ����λ�Ĵ���|       Fosc/12                 
      		   0,1     |  ��ʽ1       | 10λ�첽�շ�       |�ɶ�ʱ������ 
       	   1,0     |  ��ʽ2       | 11λ�첽�շ�       |Fosc/32��Fosc/64     
       	   1,1     |  ��ʽ3       | 11λ�첽�շ�       |�ɶ�ʱ������
       SM2(9D)		���ͨ��0:������1:���
       REN(9C)		���տ���0:��ֹ���գ�1:�������    
       TB8	(9B)		�������ݵھ�λ
       RB8	(9A)		�������ݵھ�λ
       TI	(99)		�����жϱ��
       RI	(98)		�����жϱ�־
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




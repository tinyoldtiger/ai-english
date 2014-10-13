
/***************************************************************************************
****************************************************************************************
* FILE		: uart.h
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


#ifndef _UART_H_
#define _UART_H_


#include "type.h"



extern void uart_put_char(U8 val);
extern void uart_put_string(U8* pData, U8 len);

extern void uart_process(U8 u8);





#endif


/***************************************************************************************
****************************************************************************************
* FILE		: trace.h
* Description	: 
*			  
* Copyright (c) 2007 by LIU YING. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		Liu Ying	2007/05/01	Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _TRACE_H_
#define _TRACE_H_




#define uprintf(A)		(uart_put_string(A, 0))
#define uputbyte(A)		(uart_put(A))
#define uputchar(A)		(uart_put_char(A))
#define uputarray(A,B)	(uart_put_string(A, B))

#define ERRprintf(A)		uprintf("\n>>>ERROR: "); uprintf(A); INTERRUPT_DISABLE(); while(1);


//extern void qprintf(const char *fmt, ...);

#endif /*_TRACE_H_*/


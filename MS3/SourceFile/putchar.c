/***********************************************************************/
/*  This file is part of the C51 Compiler package                      */
/*  Copyright KEIL ELEKTRONIK GmbH 1990 - 2002                         */
/***********************************************************************/
/*                                                                     */
/*  PUTCHAR.C:  This routine is the general character output of C51.   */
/*  You may add this file to a uVision2 project.                       */
/*                                                                     */
/*  To translate this file use C51 with the following invocation:      */
/*     C51 PUTCHAR.C <memory model>                                    */
/*                                                                     */
/*  To link the modified PUTCHAR.OBJ file to your application use the  */
/*  following Lx51 invocation:                                         */
/*     Lx51 <your object file list>, PUTCHAR.OBJ <controls>            */
/*                                                                     */
/***********************************************************************/

#include "reg52x2.h"

#define XON  0x11
#define XOFF 0x13


/*
 * putchar (full version):  expands '\n' into CR LF and handles
 *                          XON/XOFF (Ctrl+S/Ctrl+Q) protocol
 */


 #if 0						/*原为此函数*/
 char putchar (char c) 
{
	while (!TI);
	TI = 0;
	return (SBUF = c);
}
 
char putchar (char c)  
{

if (c == '\n')  
	{
    	if (RI)  
    		{
      		if (SBUF == XOFF)  
      			{
        		while (SBUF != XON) 
        			{
          			RI = 0;
         			 while (!RI);
        			}
        		RI = 0; 
      			}
    		}
    while (!TI);
    TI = 0;
    SBUF = 0x0d;                         /* output CR  */
  	}
if (RI)  
	{
    	if (SBUF == XOFF)  
    		{
      		while (SBUF != XON)
      			{
       		RI = 0;
        		while (!RI);
      			}
      		RI = 0; 
    		}
  	}
while (!TI);
TI = 0;
return (SBUF = c);
}
#endif


#if 0         /* comment out versions below	老版本，已不用*/

/*
 * putchar (basic version): expands '\n' into CR LF
 */
char putchar (char c)  
{
  if (c == '\n')  
  	{
    	while (!TI);
    	TI = 0;
    	SBUF = 0x0d;                         /* output CR  */
  	}
  while (!TI);
  TI = 0;
  return (SBUF = c);
}


/*
 * putchar (mini version): outputs charcter only
 */
char putchar (char c)  
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}
#endif

#if 1						
/******************************************************************************************
*函数名:		putchar
*参数:			c
*返回值:		无
*描述:			为配合UART中断接收而修改的函数，主要修改TI和ES
					支持Printf函数
*编写:			王绍伟
*版本信息:		V1.0			2003年8月15日
******************************************************************************************/
char putchar (char c)
{
	bit bES;
	bES=ES;			/*暂存ES内容*/
	ES=0;			/*若 想利用TI标志位,就必须先禁止串口中断,否则会冲突*/
	if (c == '\n') 	/*如果c为换行*/ 	
	{
		SBUF = 0x0d;
		while(!TI);	/*当TI为0时一直在循环*/
		TI=0;	/*当TI为1时跳出循环,再将TI置为0*/
	}
	SBUF = c;
	while(!TI);
	TI=0;
	ES=bES;			/*待字符发送完毕后,再恢复串口中断允许*/
	return(1);
}

#endif

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


 #if 0						/*ԭΪ�˺���*/
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


#if 0         /* comment out versions below	�ϰ汾���Ѳ���*/

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
*������:		putchar
*����:			c
*����ֵ:		��
*����:			Ϊ���UART�жϽ��ն��޸ĵĺ�������Ҫ�޸�TI��ES
					֧��Printf����
*��д:			����ΰ
*�汾��Ϣ:		V1.0			2003��8��15��
******************************************************************************************/
char putchar (char c)
{
	bit bES;
	bES=ES;			/*�ݴ�ES����*/
	ES=0;			/*�� ������TI��־λ,�ͱ����Ƚ�ֹ�����ж�,������ͻ*/
	if (c == '\n') 	/*���cΪ����*/ 	
	{
		SBUF = 0x0d;
		while(!TI);	/*��TIΪ0ʱһֱ��ѭ��*/
		TI=0;	/*��TIΪ1ʱ����ѭ��,�ٽ�TI��Ϊ0*/
	}
	SBUF = c;
	while(!TI);
	TI=0;
	ES=bES;			/*���ַ�������Ϻ�,�ٻָ������ж�����*/
	return(1);
}

#endif

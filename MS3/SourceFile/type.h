
/***************************************************************************************
****************************************************************************************
* FILE		: type.h
* Description	: The general purpose macro and function
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


/******************************************************************************
˵��:
һ�������ʹ��Keil-51�ṩ�����ͣ���������ʾ:
1:�˿�
	P0,P1,P2,P3
2:λ�˿�
   	P0^X
   	P1^X
   	P2^X
   	P3^X
3:������������
data type 	|   length(bit)  |  length(byte)   |data range
bit 				1			...			0,1
unsigned char		8			1			0~255
signed char		8			1			-128~127
unsigned int		16			2			0~65535
signed int			16			2			-32768~32767
unsigned long		32			4			0~4294967295
signed long		32			4			-2147483648~2147483647
float				32			4			+-1.176E-38~+-3.40E+38(6λ����)
double			64			8			+-1.176E-38~+-3.40E+38(10λ����)
һ��ָ��	24			3			����ռ�0~65535

4:���ô洢����
data				ֱ��ѰַƬ�����ݴ洢���������ٶȿ�(128�ֽ�)
bdata			��λѰַƬ�����ݴ洢��������λ���ֽڻ�ͷ���(16�ֽ�)
idata			���ѰַƬ�����ݴ洢�����ɷ���Ƭ��ȫ��RAM��ַ�ռ�(256�ֽ�)
pdata			��ҳѰַƬ��������(256�ֽ�)��MOVX@R0��@R1����
xdata			Ƭ�����ݴ洢��(64K)����MOVX@DPTR����
code				����洢��(64K),��MOVC@DPTR����

5:�洢ģʽ��˵��
small 			�������ֲ����������ֱ��Ѱַ��Ƭ�ڴ洢������DATA,
				��Ϊ����ʮ�ַ��㡣�������ж��󣬰���ջ��������Ǳ
				��Ƭ��RAM��ջ���ܹؼ�����Ϊʵ��ջ�������ڲ�ͬ�ĺ�
				��Ƕ�ײ���
				
compact			�������ֲ����������ҳƬ��洢��(���256�ֽڣ�Ĭ��
				�Ĵ洢������pdata),ͨ���Ĵ���R0��R1(@R0,R1)���Ѱַ��ջ��
				��λ��8051ϵͳ�ڲ����ݴ洢�С�
				
large			�������ֲ�����ֱ�ӷ���Ƭ�����ݴ洢��(���64k��Ĭ��
				�洢����Ϊxdata)ʹ������ָ��DPTR������Ѱַ���ô�����
				ָ����з���Ч�ʽϵͣ������Ƕ����������ֽڵı���
				�����������͵ķ��ʻ���ֱ��Ӱ�����ĳ��ȣ���һ������
				֮��������������ָ�벻�ܶԳƲ�����


��:Keil51�Դ���ͷ�ļ�keil51�ĵ��е�229ҳ
1:absacc.h			���Դ洢�����ʺ�
	1:CBYTE,		2:CWORD,	3:DBYTE,		4:DWORD,	5:FARRAY,	6:FCARRAY,	7:FVAR,	8:FCVAR,
	9:PBYTE,		10:PWORD,	11:XBYTE,	12:XWORD
	
2:assert.h
	1:assert

3:ctype.h
	1:isalnum,	2:isalpha,	3:iscntrl,		4:isdigit,		5:isgraph,	6:islower,	7:isprint,		8:ispunct,
	9:isspace,	10:isupper,	11:isxdigit,	12:toascii,	13:toint,		14:tolower,	15:_tolower,	16:toupper,
	17:_toupper
	
4:intrins.h
	1:_chkfloat,	2:_irol_,		3:_Iror_,		4:_crol_,		5:_iror_,		6:_nop_,		7:_cror_,		8:_Irol_,
	9:_testbit_
	
5:math.h
	1:abs,		2:exp		3:modf		4:acos		5:fabs		6:pow		7:asin		8:floor
	9:sin		10:atan		11:fmod		12sinh		13:atan2		14:fprestore	15:sqrt		16:cabs
	17:fpsave	18:tan		19:ceil		20:labs		21:tanh		22:cos		23:log		24:cosh
	25:log10

6:setjmp.h
	1:jmp_buf	2:setjmp		3:longjmp
	
7:stdarg.h
	1:va_arg		2:va_end		3:va_start	4:va_list

8:stddef.h
	1:offsetof		

9:stdio.h
	1:getchar		2:putchar		3:sscanf		4:_getkey	5:puts		6:ungetchar	7:gets	8:scanf
	9:vprintf		10:printf		11:sprintf		12:vsprintf	13:EOD

10:stdlib.h
	1:atof		2:init_menpool3:strtod		4atoi		5:malloc		6:strtol		7:atol	8:rand
	9:strtoul		10:calloc		11:realloc	12:free		13:srand
	
11:string.h	
	1:memccpy,	2:memchr,	3:memcmp,	4:memcpy,	5:memmove	6:memset	7:strcat	8:strchr
	9:strcmp		10:strcpy		11:strcspn	12:strlen   	13:strncat	14:strncmp	15:strncpy16:strpbrk
	17:strrpos	18:strrchr	19:strrpbrk	20:strrpos	21:strspn

��:�﷨
��C������Ƕ����
#pragma asm
������
...
#pragma endasm

��:���涨��İ�������ʹ�ã���:
U1, U8, U16, U32, S8, S16, S32��Щ��ұȽ���Ϥ�ı���������������������
������������������



��:������,������ͳһ��
1 :�ⲿ����ȫ�������ļ����Ӻ��������»������ӽṹ,��
extern void key_check(void);	���в���������������Ķ̸�ʽ����������͵�������.
2:�ڲ��������ö̸�ʽ,�ڲ��������ֽڵ�Ҳ���ö̸�ʽ,���ֽڵ�����ͨ����
i,j,kһ�����ں����ڲ���ѭ��������.


��:�Ĵ���˵��:
1	TCON:�жϱ�־�Ĵ���
	TF1(8F)		T1�жϱ�־λ
	TR1(8E)		T1��ͣλ	
	TF0(8D)		T0�жϱ�־λ
	TR0(8C)		T0��ͣλ
	IE1(8B)		~INT1�жϱ�־λ
	IT1(8A)		~INT1��������λ0Ϊ��ƽ������1Ϊ����Ե����
	IE0(89)		~INT0�жϱ�־λ
	IT0(88)		~INT0��������λ0Ϊ��ƽ������1Ϊ����Ե����

2	IE:�жϼĴ���
	EA(AF)		ȫ���жϿ���
	ET2(AD)		T2�жϿ���
	ES(AC)		���п��жϿ���
	ET1(AB)		T1�жϿ���
	EX1(AA)		~INT1�жϿ���
	ET0(A9)		T0�жϿ���
	EX0(A8)		~INT0�жϿ���
******************************************************************************/


#ifndef _TYPE_H_
#define _TYPE_H_


//#include "reg52x2.h"


#ifndef NULL
#define NULL ((void *) 0L)		/*Stdlib.h and String.h already include NULL */
#endif


//���Ͷ���
//typedef bit 			bool;
typedef unsigned char	byte;
typedef unsigned int 	word;
typedef unsigned long 	dword;

//typedef bit 			U1;
typedef unsigned char	U8;
typedef unsigned int 	U16;
typedef unsigned long 	U32;

typedef char			S8;
typedef int 			S16;
typedef long 			S32;

typedef void (*Function)(void);

#define FUNC(u16Adrr)	(*(Function)u16Adrr)()




/*���峣��*/
#define TRUE			(U1)1
#define FALSE		(U1)0

#define ERROR		0xFF

#define DP51


#endif


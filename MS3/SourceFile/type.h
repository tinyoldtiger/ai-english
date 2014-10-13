
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
说明:
一般基本上使用Keil-51提供的类型，如以下所示:
1:端口
	P0,P1,P2,P3
2:位端口
   	P0^X
   	P1^X
   	P2^X
   	P3^X
3:常用数据类型
data type 	|   length(bit)  |  length(byte)   |data range
bit 				1			...			0,1
unsigned char		8			1			0~255
signed char		8			1			-128~127
unsigned int		16			2			0~65535
signed int			16			2			-32768~32767
unsigned long		32			4			0~4294967295
signed long		32			4			-2147483648~2147483647
float				32			4			+-1.176E-38~+-3.40E+38(6位数字)
double			64			8			+-1.176E-38~+-3.40E+38(10位数字)
一般指针	24			3			储存空间0~65535

4:常用存储类型
data				直接寻址片内数据存储区，访问速度快(128字节)
bdata			可位寻址片内数据存储区，允许位与字节混和访问(16字节)
idata			间接寻址片内数据存储区，可访问片内全部RAM地址空间(256字节)
pdata			分页寻址片外数据区(256字节)由MOVX@R0或@R1访问
xdata			片外数据存储区(64K)，由MOVX@DPTR访问
code				代码存储区(64K),由MOVC@DPTR访问

5:存储模式及说明
small 			参数及局部变量放入可直接寻址的片内存储类型是DATA,
				因为访问十分方便。另外所有对象，包括栈，都必须潜
				入片内RAM。栈长很关键，因为实际栈长依赖于不同的函
				数嵌套层数
				
compact			参数及局部变量放入分页片外存储区(最大256字节，默认
				的存储类型是pdata),通过寄存器R0和R1(@R0,R1)间接寻址，栈空
				间位于8051系统内部数据存储中。
				
large			参数及局部变量直接放入片外数据存储区(最大64k，默认
				存储类型为xdata)使用数据指针DPTR来进行寻址，用此数据
				指针进行访问效率较低，尤其是对两个或多个字节的变量
				这种数据类型的访问机制直接影响代码的长度，另一不方便
				之处在于这种数据指针不能对称操作。


二:Keil51自带的头文件keil51文档中的229页
1:absacc.h			绝对存储器访问宏
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

三:语法
在C语言中嵌入汇编
#pragma asm
汇编语句
...
#pragma endasm

四:下面定义的按以下来使用，如:
U1, U8, U16, U32, S8, S16, S32这些大家比较熟悉的变量类型命名法来命名。
采用匈牙利命名法。



五:变量名,函数名统一化
1 :外部函数全部采用文件名加函数名的下划线联接结构,如
extern void key_check(void);	其中参数名采用有意义的短格式命名或带类型的数据名.
2:内部函数采用短格式,内部变量多字节的也采用短格式,单字节的用普通变量
i,j,k一般用于函数内部的循环计数器.


四:寄存器说明:
1	TCON:中断标志寄存器
	TF1(8F)		T1中断标志位
	TR1(8E)		T1启停位	
	TF0(8D)		T0中断标志位
	TR0(8C)		T0启停位
	IE1(8B)		~INT1中断标志位
	IT1(8A)		~INT1触发控制位0为电平触发，1为负边缘触发
	IE0(89)		~INT0中断标志位
	IT0(88)		~INT0触发控制位0为电平触发，1为负边缘触发

2	IE:中断寄存器
	EA(AF)		全部中断控制
	ET2(AD)		T2中断控制
	ES(AC)		串行口中断控制
	ET1(AB)		T1中断控制
	EX1(AA)		~INT1中断控制
	ET0(A9)		T0中断控制
	EX0(A8)		~INT0中断控制
******************************************************************************/


#ifndef _TYPE_H_
#define _TYPE_H_


//#include "reg52x2.h"


#ifndef NULL
#define NULL ((void *) 0L)		/*Stdlib.h and String.h already include NULL */
#endif


//类型定义
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




/*定义常量*/
#define TRUE			(U1)1
#define FALSE		(U1)0

#define ERROR		0xFF

#define DP51


#endif


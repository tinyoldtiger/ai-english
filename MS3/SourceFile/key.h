
/***************************************************************************************
****************************************************************************************
* FILE		: key.h
* Description	: key process
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


#ifndef _KEY_H_
#define _KEY_H_

#define KEY_PC_STYLE						/*PC 按键风格，长按时不停输出原按键*/
//#define KEY_MCU_STYLE						/*MCU 按键风格，长按时输出不同值的按键*/

#define KEY_SHORT_INTERVAL			2		/*短按按键间隔*/
#define KEY_LONG_INTERVAL			40		/*长按按键间隔*/
#define KEY_SAFEGUARD_INTERVAL	3		/*防误动按键间隔*/



#ifdef DP51
typedef enum
{
	KEY1 = 1,
	KEY2 = 2,
	KEY3 = 3,
	KEY4 = 4,
	KEY5 = 5,
	KEY6 = 6,
	KEY7 = 7,
	KEY8 = 8
};
#endif


extern void key_enable(void);
extern void key_disable(void);
extern void key_check(void);		/*return=1,2,3,4,5,6,7.		return=0 is no key .	return=ERROR means the PROCESS is ERROR	有待修改考虑*/

#endif


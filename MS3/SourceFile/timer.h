
/***************************************************************************************
****************************************************************************************
* FILE		: timer.h
* Description	: timer and MSTimer
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


#ifndef _TIMER_H_
#define _TIMER_H_


#include "type.h"

#define MSTIMER_NUMBER		0x04				/*max: 8*/


typedef enum {
	MSTIMERMODE_INT = 0,
	MSTIMERMODE_MSG = 1	
};

typedef U1 MSTimerHandelMode;



extern U8 MSTimerStart(MSTimerHandelMode Mode, U16 Delay, Function pCallBack);

#define SCH_Add_Task(Mode, Delay, Task) MSTimerStart(Mode, Delay, Task)

extern void MSTimerStop(U8 Id);

extern void system_process(void);

 

#endif

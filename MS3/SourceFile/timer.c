
/***************************************************************************************
****************************************************************************************
* FILE		: timer.c
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


/*
寄存器说明:
1	TCON:中断标志寄存器
	TF1(8F)		T1中断标志位
	TR1(8E)		T1启停位	
	TF0(8D)		T0中断标志位
	TR0(8C)		T0启停位
2	TMOD:定时器方式寄存器
	GATE	|	C/~T	|	M1,M0	|GATE	|	C/~T	|	M1,M0	|
	\______________________________/	0 ~INT0	 0	定时器	  0 , 0	-----方式0
				T1					无关	 1	计数器	  0 ,  1	-----方式1
	对应							1 ~INT0	    模式	 	  1 ,  0	-----方式2
	INT1								有关					  1 ,  1	-----方式3


3	工作方式:
	方式0:13位计数器TL的搞三位不用
	方式1:16位计数器
	方式2:可循环8位计数器,适用于UART
	方式3:T0与T1不同
	定时器1 只能按不需要中断的方式2工作
	此模式下定时器0 的TL0 及TH0 作为两个独立的8 位计数器/定时器
	TL0 占用定时器0 的TF0 TH0 
	TL1 占用定时器1 的TR1和TF1
	
*/


#include "common.h"






typedef struct 
{
	U16  delay;
	Function pCallBack;
}MSTIMER_T;


static U8  MSTimerID = 0;
static U8  MSTimerMode = 0;
//static MSTIMER_T idata MSTimerArray[MSTIMER_NUMBER];
static MSTIMER_T  MSTimerArray[MSTIMER_NUMBER];





/*==================================================================
* Function	: MSTimerService
* Description	: MSTimer service, will be called in Timer2InterruptService
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void MSTimerService(void)
{
	
	U8 i = 0;
	U8 MSTimerID_Map;
	MSTimerID_Map = MSTimerID;
	
	while(MSTimerID_Map)
	{
		if((MSTimerID_Map & 0x01) == 1)
		{
			if(!(--MSTimerArray[i].delay))/*倒计时*/
			{
				if(GETBIT(MSTimerMode, i))
				{
					/*抛出消息，在主循环中执行*/
					MSG_SEND_MSG(MSG_MSTIMER, i);
					MSG_SEND_DATA((U16)(MSTimerArray[i].pCallBack));
				}
				else
				{
					/*直接执行*/
					(*(MSTimerArray[i].pCallBack))();
				}
				RESETBIT(MSTimerID, i);
			}
		}
		
		MSTimerID_Map = MSTimerID_Map >> 1;
		i++;
	}
}


/*==================================================================
* Function	: timer_mstimer_start
* Description	: start a virtual timer base on system timer
			  make sure there is enough timer, that is MSTIMER_MAX is big enough
* Input Para	: U1 Mode		: 0: pCallBack will be executed in interrupt
							  1: pCallBack will be executed in message handling
			  U16 Delay	: delay time, in the unit of system timer (normally it is 20ms).
			  				  so the max delay time is 65535 * 20 ms
			  MSTimerCallbackFunc pCallBack	: callback function when MSTimer arrives
* Output Para	: void
* Return Value: U8	: return ID,if have no ID ,return 0xFF.
==================================================================*/
U8 MSTimerStart(MSTimerHandelMode Mode, U16 Delay, Function pCallBack)
{
	U8 EA_MAP;
	U8 i;
	
	EA_MAP = INTERRUPT_GET();
	INTERRUPT_DISABLE();/*关中断*/
	
	for(i = 0; i < MSTIMER_NUMBER; i++)/*查询并分配软件定时器*/
	{

		if(!GETBIT(MSTimerID, i))	
		{			
			MSTimerArray[i].delay = Delay;/*延时时间*/
			MSTimerArray[i].pCallBack = pCallBack;/*回调函数*/
			if(Mode)	/*运行模式*/
			{
				SETBIT(MSTimerMode, i);
			}
			else
			{
				RESETBIT(MSTimerMode, i);
			}
			
			SETBIT(MSTimerID, i);
			INTERRUPT_SET(EA_MAP);
			return(i);
		}
	}
	
	INTERRUPT_SET(EA_MAP);/*开中断*/
	ERRprintf("MSStartTimer\n");
	return 0xFF;
}


/*==================================================================
* Function	: MSTimerStop
* Description	: stop MSTimer
* Input Para	: U8 Id	: timer ID, should be less than MSTIMER_MAX
* Output Para	: void
* Return Value: void
==================================================================*/
void MSTimerStop(U8 Id)
{
	U8 EA_MAP;
	
	EA_MAP = INTERRUPT_GET();
	INTERRUPT_DISABLE();
	
	if(Id < MSTIMER_NUMBER)
	{
		RESETBIT(MSTimerID, Id);
	}
	else
	{
		ERRprintf("timer_mstimer_stop\n");
	}
	INTERRUPT_SET(EA_MAP);
}


#if 0
/*==================================================================
* Function	: timer0_process
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void timer0_process(void)
{

}
#endif


#if 0
/*==================================================================
* Function	: timer1_process
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void timer1_process(void)
{

}
#endif


/*==================================================================
* Function	: system_process
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void system_process(void)
{
	if(MSTimerID > 0)	/*识别有无软件定时器进程*/
	{
		MSTimerService();/*执行软件定时器进程*/
	}
	
	routine_process();/*运行例行任务程序*/
}


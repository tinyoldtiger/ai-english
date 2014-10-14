
/***************************************************************************************
****************************************************************************************
*								MCUSYSTEM3(MS3)
*
* Hardware Name	: MS3
* SoftWave Name	: MS3
* Complie		: Keil C Compile V7.10
* Version			: MS3.00
* Description		: -
* Created		: 2007.3.11 by wangsw
* Modefied 		: -
****************************************************************************************
****************************************************************************************/


/***************************************************************************************
****************************************************************************************
* FILE		: boot.c
* Description	: The main program
*			  
* Copyright (c) 2003~2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   1.0		Wang Shaowei	2003/07/16	Initial Version (MCU System)
   2.0		Wang Shaowei	2005/06/01	MS2
   3.0		Wang Shaowei	2007/03/11	MS3
   3.21		Wang Shaowei	2011/02/14	MS3.21
   
****************************************************************************************
****************************************************************************************/


//#include <stdio.h>

#include "common.h"


/*==================================================================
* Function	: Task
* Description	: 演示Task程序，会周期性的执行
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/

void Task(void)
{
	uprintf("Hellow World\n");
	SCH_Add_Task(MSTIMERMODE_MSG, 1020, Task);
}





/*==================================================================
* Function	: init_process
* Description	: System initialize entry
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void init_process(void)
{

	//port_init();
	
	ChipHalInit();//片内硬件初始化
	
	//Interrupt_priority_init();
	
	/*Flash 校验等，应用于系统比较严格的地方*/
	flash_init();
	
	/*等待外设准备好，比如一些继电器之类的设备*/
	uty_delay(0xF000);
	
	/*模式选择12clock与6clock切换*/
	//mode_init();
		
	//uart_init(UART_RATE576);

	LD3320_init();	  
	
  CH375_init();	
	
	mmi_init();
	/*消息队列初始化*/
	msg_init();
	
	rtc_soft_init(0, 0, 0);

	//Task();
		
	timer2_init(TRUE, TimerInterval5H);		/*system timer,importance*/

	INTERRUPT_ENABLE();									/*enable global interrupt*/
}

/*==================================================================
* Function	: main
* Description	: Program entry
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
int main(void)
{
	U8 i = 0;
	U16 Msg;

	init_process();	/*程序初始化*/
	
	while(TRUE)
	{
		MSG_GET_MSG(&Msg); /*获取消息*/
		
		switch(MSG_TYPE(Msg))						
		{
			case MSG_KEY:	/*按键消息*/
				KeyStore = MSG_VALUE(Msg);/*获取按键*/
				fMMIProc();  /*界面函数指针，界面入口*/
				break;
				
			case MSG_RTC:/*RTC消息*/
				display_time_routine();/*软件时钟执行消息*/
				break;
				
			case MSG_MSTIMER:/*软件定时器中断外处理消息*/
				MSG_GET_DATA(&Msg);	/*获取软件定时器的回调函数指针*/
				FUNC(Msg);/*执行回调函数*/
				break;
				
			case MSG_TEST:	/*测试用*/
				//special for test
				break;
				
			case MSG_NULL:
				break;
			
			case MSG_LD_IDENTIFY:	
				MSG_GET_DATA(&Msg);
			  LD3320_min(MSG_VALUE(Msg));
				break;
			
			default:			/*建议用于喂狗等*/
				//no msg, or error msg
				break;
		}
	}
}









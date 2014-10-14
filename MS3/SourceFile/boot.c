
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
* Description	: ��ʾTask���򣬻������Ե�ִ��
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
	
	ChipHalInit();//Ƭ��Ӳ����ʼ��
	
	//Interrupt_priority_init();
	
	/*Flash У��ȣ�Ӧ����ϵͳ�Ƚ��ϸ�ĵط�*/
	flash_init();
	
	/*�ȴ�����׼���ã�����һЩ�̵���֮����豸*/
	uty_delay(0xF000);
	
	/*ģʽѡ��12clock��6clock�л�*/
	//mode_init();
		
	//uart_init(UART_RATE576);

	LD3320_init();	  
	
  CH375_init();	
	
	mmi_init();
	/*��Ϣ���г�ʼ��*/
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

	init_process();	/*�����ʼ��*/
	
	while(TRUE)
	{
		MSG_GET_MSG(&Msg); /*��ȡ��Ϣ*/
		
		switch(MSG_TYPE(Msg))						
		{
			case MSG_KEY:	/*������Ϣ*/
				KeyStore = MSG_VALUE(Msg);/*��ȡ����*/
				fMMIProc();  /*���溯��ָ�룬�������*/
				break;
				
			case MSG_RTC:/*RTC��Ϣ*/
				display_time_routine();/*���ʱ��ִ����Ϣ*/
				break;
				
			case MSG_MSTIMER:/*�����ʱ���ж��⴦����Ϣ*/
				MSG_GET_DATA(&Msg);	/*��ȡ�����ʱ���Ļص�����ָ��*/
				FUNC(Msg);/*ִ�лص�����*/
				break;
				
			case MSG_TEST:	/*������*/
				//special for test
				break;
				
			case MSG_NULL:
				break;
			
			case MSG_LD_IDENTIFY:	
				MSG_GET_DATA(&Msg);
			  LD3320_min(MSG_VALUE(Msg));
				break;
			
			default:			/*��������ι����*/
				//no msg, or error msg
				break;
		}
	}
}









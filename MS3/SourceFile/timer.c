
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
�Ĵ���˵��:
1	TCON:�жϱ�־�Ĵ���
	TF1(8F)		T1�жϱ�־λ
	TR1(8E)		T1��ͣλ	
	TF0(8D)		T0�жϱ�־λ
	TR0(8C)		T0��ͣλ
2	TMOD:��ʱ����ʽ�Ĵ���
	GATE	|	C/~T	|	M1,M0	|GATE	|	C/~T	|	M1,M0	|
	\______________________________/	0 ~INT0	 0	��ʱ��	  0 , 0	-----��ʽ0
				T1					�޹�	 1	������	  0 ,  1	-----��ʽ1
	��Ӧ							1 ~INT0	    ģʽ	 	  1 ,  0	-----��ʽ2
	INT1								�й�					  1 ,  1	-----��ʽ3


3	������ʽ:
	��ʽ0:13λ������TL�ĸ���λ����
	��ʽ1:16λ������
	��ʽ2:��ѭ��8λ������,������UART
	��ʽ3:T0��T1��ͬ
	��ʱ��1 ֻ�ܰ�����Ҫ�жϵķ�ʽ2����
	��ģʽ�¶�ʱ��0 ��TL0 ��TH0 ��Ϊ����������8 λ������/��ʱ��
	TL0 ռ�ö�ʱ��0 ��TF0 TH0 
	TL1 ռ�ö�ʱ��1 ��TR1��TF1
	
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
			if(!(--MSTimerArray[i].delay))/*����ʱ*/
			{
				if(GETBIT(MSTimerMode, i))
				{
					/*�׳���Ϣ������ѭ����ִ��*/
					MSG_SEND_MSG(MSG_MSTIMER, i);
					MSG_SEND_DATA((U16)(MSTimerArray[i].pCallBack));
				}
				else
				{
					/*ֱ��ִ��*/
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
	INTERRUPT_DISABLE();/*���ж�*/
	
	for(i = 0; i < MSTIMER_NUMBER; i++)/*��ѯ�����������ʱ��*/
	{

		if(!GETBIT(MSTimerID, i))	
		{			
			MSTimerArray[i].delay = Delay;/*��ʱʱ��*/
			MSTimerArray[i].pCallBack = pCallBack;/*�ص�����*/
			if(Mode)	/*����ģʽ*/
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
	
	INTERRUPT_SET(EA_MAP);/*���ж�*/
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
	if(MSTimerID > 0)	/*ʶ�����������ʱ������*/
	{
		MSTimerService();/*ִ�������ʱ������*/
	}
	
	routine_process();/*���������������*/
}


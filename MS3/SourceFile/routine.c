
/***************************************************************************************
****************************************************************************************
* FILE		: routine.c
* Description	: ���г�������ϵͳ���ĵ��ð��������
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


#include "common.h"

U8 KeyStore;



/*==================================================================
* Function	: routine_process
* Description	: routine program
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void routine_process(void)
{
	static U8 RoutineCounter = 0;

	static U8 RTCCounter = 0;
	
	if(++RoutineCounter == 5)	/*ϵͳʱ�ӷ�Ϊ5��*/
	{
		RoutineCounter = 0;
	}
	switch(RoutineCounter)
	{
		case 0:
			key_check();			/*����ɨ��*/
			led_control(KeyStore);	/*LED����ʾ*/
			if(++RTCCounter == 40)
			{
				RTCCounter = 0;
				rtc_soft_routine(); 		/*���ʱ�����г���*/
			}
			break;
		case 1:						/*�ĸ��������ʾ*/
			LedDisplay_control(FALSE, 1, uty_hex2bcd(tTCMember.second) & 0x0F);
			break;
		case 2:			
			LedDisplay_control(FALSE, 2,  uty_hex2bcd(tTCMember.second) >> 4);
			break;
		case 3:
			LedDisplay_control(TRUE, 3, uty_hex2bcd(tTCMember.minute) & 0x0F);
			break;
		case 4:
			LedDisplay_control(FALSE, 4, uty_hex2bcd(tTCMember.minute) >> 4);
			break;
	}
}


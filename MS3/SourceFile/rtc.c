
/***************************************************************************************
****************************************************************************************
* FILE		: rtc.c
* Description	: real time counter
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


#include "rtc.h"
#include "message.h"


RTCMember tTCMember;


/*==================================================================
* Function	: rtc_soft_init
* Description	: rtc time initialize
* Input Para	: U8 hour, U8 minute, U8 second
* Output Para	: void
* Return Value: void
==================================================================*/
void rtc_soft_init(U8 hour, U8 minute, U8 second)
{
	tTCMember.hour = hour;
	tTCMember.minute = minute;
	tTCMember.second = second;
}


/*==================================================================
* Function	: rtc_soft_routine
* Description	: soft rtc counter 
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void rtc_soft_routine(void)
{
	if(++tTCMember.second > 59)
	{
		tTCMember.second = 0;
		tTCMember.minute++;
	}
	
	if(tTCMember.minute > 59)
	{
		tTCMember.minute = 0;
		tTCMember.hour++;
	}
	
	MSG_SEND_MSG(MSG_RTC, 0);
}


/*==================================================================
* Function	: rtc_soft_read
* Description	: Read current time 
* Input Para	: void
* Output Para	: void
* Return Value: RTCMember	: current time
==================================================================*/
RTCMember rtc_soft_read(void)
{
	return(tTCMember);
}


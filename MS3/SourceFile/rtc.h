
/***************************************************************************************
****************************************************************************************
* FILE		: rtc.h
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


#ifndef _RTC_H_
#define _RTC_H_


#include "type.h"


typedef struct 
{
	U8 second;
	U8 minute;
	U8 hour;
} RTCMember;

extern RTCMember tTCMember;

extern void rtc_soft_init(U8 hour, U8 minute, U8 second);
extern void rtc_soft_routine(void);
extern RTCMember rtc_soft_read(void);

#endif

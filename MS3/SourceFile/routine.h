
/***************************************************************************************
****************************************************************************************
* FILE		: routine.h
* Description	: 例行程序，利用系统节拍调用按键处理等
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


#ifndef _ROUTINE_H_
#define _ROUTINE_H_


#include "type.h"

extern U8 KeyStore;
extern void routine_process(void);


#endif

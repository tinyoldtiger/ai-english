
/***************************************************************************************
****************************************************************************************
* FILE		: mcu_ext.h
* Description	: 
*			  
* Copyright (c) 2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		WANG SHAOWEI	2007/05/09	Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _MCU_EXT_H_
#define _MCU_EXT_H_





extern U8 key_read(void);

extern void led_control(U8 LedIndex);

extern void LedDisplay_control(U1 boDp, U8 LedDisplayIndex, U8 value);


#endif /*_MCU_EXT_H_*/


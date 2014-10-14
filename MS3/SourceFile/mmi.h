
/***************************************************************************************
****************************************************************************************
* FILE		: mmi.h
* Description	: man machine interface
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


#ifndef _MMI_H_
#define _MMI_H_


extern Function fMMIProc;

extern void mmi_init(void);
extern void mmi_process(U8 key);
extern void display_time_routine(void);

#endif

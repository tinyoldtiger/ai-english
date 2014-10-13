
/***************************************************************************************
****************************************************************************************
* FILE		: flash.c
* Description	: 
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


/*==================================================================
* Function	: FlashCodeCRC
* Description	: 工控项目，尤其是对系统安全性要求非常严格
			  的地方，需要做Flash中的Code进行校验
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void FlashCodeCRC(void)
{
	
}


/*==================================================================
* Function	: FlashDataCRC
* Description	: 工控项目，尤其是对系统安全性要求非常严格
			  的地方，需要做Flash中的Data进行校验
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void FlashDataCRC(void)
{
	
}


/*==================================================================
* Function	: flash_init
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void flash_init(void)
{
	FlashCodeCRC();
	FlashDataCRC();
}



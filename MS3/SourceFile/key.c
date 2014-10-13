
/***************************************************************************************
****************************************************************************************
* FILE		: key.c
* Description	: key process
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








static U1 KeyEnable = TRUE;





/*==================================================================
* Function	: key_enable
* Description	: enable key check
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void key_enable(void)
{
	KeyEnable = TRUE;
}


/*==================================================================
* Function	: key_disable
* Description	: disable key check
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void key_disable(void)
{
	KeyEnable = FALSE;
}

#ifdef DP51
U8 KeyMap(U8 val)
{
	return(val + 1);
}





#ifdef KEY_MCU_STYLE

/*==================================================================
* Function	: LongKeyMap
* Description	: 长按键值映射表
* Input Para	: U8 val	: key value
* Output Para	: void
* Return Value: U8		: key name
==================================================================*/
static U8 LongKeyMap(U8 val)
{
	return(0x31 + val);		
}

#endif
#endif


#ifdef KEY_PC_STYLE	
/*==================================================================
* Function	: key_check
* Description	: 按键检测，采用扫面方式，利用P1口，4 * 4扫描
			  采用此方式，相对中断来说，具有简单方便，
			  硬件成本低，按键数多，外接元器件少等优点
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void key_check(void)			
{
	U8 data  KeyRead;
	/*防止按键接触不良引起的多重触发*/
	static U8 data KeySafeguardInterval = 0;
	static U8 data KeyCounter = 0;
	static U8 data KeySave = 0;

	
	if(!KeyEnable)	/*按键功能是否开启*/
		return;

	KeyRead = key_read();	/*读取按键值*/
	
	
	if(KeyRead == ERROR)	/*按键值是否有效*/
	{
		if(KeySafeguardInterval)/*防止按键接触不良引起的多重触发*/	
		{
			KeySafeguardInterval--;
		}
		KeyCounter = 0;
		return;
	}

	KeyCounter++;	/*当有效按键，自加*/
	/*当自加超过短按键门限，认为有效*/
	if(KeyCounter == KEY_SHORT_INTERVAL)
	{	
		if((!KeySafeguardInterval) && (KeySave == KeyRead))
		{
			MSG_SEND_MSG(MSG_KEY, KeyMap(KeyRead));/*发送消息*/
		}
		/*设置多重触发的门限，防止按键不良的多重触发*/
		KeySafeguardInterval = KEY_SAFEGUARD_INTERVAL;
	}

	
	if(KeyCounter == KEY_LONG_INTERVAL)
	{
		if(KeySave == KeyRead)
		{
			MSG_SEND_MSG(MSG_KEY, KeyMap(KeyRead));
		}
		KeyCounter -= 4;
	}

	KeySave = KeyRead;

}

#elif defined KEY_MCU_STYLE

/*==================================================================
* Function	: key_check
* Description	: 
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void key_check(void)			
{
	U8 data  KeyRead;
	static U8 data KeySave;
	static U8 data KeyCounter = 0;

	
	if(!KeyEnable)
		return;

	KeyRead = key_read();
	
	
	if(KeyRead == ERROR)
	{
		if(KeyCounter == KEY_LONG_INTERVAL)
		{
			KeyCounter = 0;
			MSG_SEND_MSG(MSG_KEY, LongKeyMap(KeySave));			
		}
		else if(KeyCounter > KEY_SHORT_INTERVAL)
		{
			KeyCounter = 0;
			MSG_SEND_MSG(MSG_KEY, KeyMap(KeySave));	
		}

	}
	else
	{
		KeyCounter++;
		
		if(KeyCounter == 1)
		{
			KeySave = KeyRead;
		}
		else if(KeyCounter == 2)
		{
			if(KeySave != KeyRead)
			{
				KeyCounter = 0;
			}
		}
		else if(KeyCounter > KEY_LONG_INTERVAL)
		{
			KeyCounter = KEY_LONG_INTERVAL;
		}
	}

	
}

#endif


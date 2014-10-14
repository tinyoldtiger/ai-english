
/***************************************************************************************
****************************************************************************************
* FILE		: utility.c
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


//#include <intrins.h>

#include "common.h" 

#include "utility.h"




/*==================================================================
* Function	: uty_delay
* Description	: general purpose  function for delay
* Input Para	: U16 u16Val	: delay time
* Output Para	: void
* Return Value: void
==================================================================*/
void uty_delay(U16 u16Val)
{
	while(u16Val--)
	{
	#ifdef SPEEDUP

		_nop_();
		_nop_();
		_nop_();
	#else
		_nop_();
	#endif
	}
}


/*==================================================================
* Function	: uty_dec2bcd
* Description	: 2 digit decimal number to bcd, such as 12 to 0x12
* Input Para	: U8 val		: hex number
* Output Para	: void
* Return Value: U8		: bcd number
==================================================================*/
U8 uty_dec2bcd(U8 val)
{
	if(val < 100)
	{
		return(((val / 10) << 4)+ (val % 10));
	}
	else
	{
		ERRprintf("uty_dec2bcd\n");
		return 0xff;
	}
}


/*==================================================================
* Function	: uty_bcd2dec
* Description	: bcd to decimal number, such as 0x12 to 12
* Input Para	: U8 val		: bcd number
* Output Para	: void
* Return Value: U8		: hex number
==================================================================*/
U8 uty_bcd2dec(U8 val)
{
	return(((val >> 4) * 10) + (val & 0x0F));
}

U8 uty_hex2bcd(U8 val)
{		
	return(((val / 10) << 4) | (val % 10));
}

/*==================================================================
* Function	: uty_hex_to_ascii
* Description	: Convert number to ASCII 
* Input Para	: U8 val		: number
* Output Para	: void
* Return Value: U8		: ascii code
==================================================================*/
U8 uty_hex2ascii(U8 val)
{
	if(val < 10)
	{
		return('0' + val);
	}
	else if(val < 16)
	{
		return('A' - 10 + val);
	}
	else
	{
		ERRprintf("uty_hex_to_ascii\n");
		return 0xff;
	}	
}


/*==================================================================
* Function	: uty_ascii_to_hex
* Description	: Convert ASCII to number
* Input Para	: U8 val		: ascii code
* Output Para	: void
* Return Value: U8		: number
==================================================================*/
U8 uty_ascii2hex(U8 val)
{
	if(val <= '9')
	{
		if(val >= '0')
		{
			return(val - '0');
		}
	}
	else if(val <= 'F')
	{
		if(val >= 'A')
		{
			return(val - 'A' + 10);
		}
	}
	else if(val <= 'f')
	{
		if(val >= 'a')
		{
			return(val - 'a' + 10);
		}
	}
	else
	{
		ERRprintf("uty_ascii_to_hex\n");
		return 0xff;
	}
}




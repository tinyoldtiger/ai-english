
/***************************************************************************************
****************************************************************************************
* FILE		: utility.h
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


#ifndef _UTILITY_H_
#define _UTILITY_H_


#include "type.h"


#define SETBIT(u8Val, u8Offset)    		u8Val |= 1 << u8Offset
#define RESETBIT(u8Val, u8Offset)  	u8Val &= ~(1 << u8Offset)
#define GETBIT(u8Val, u8Offset)	   	((u8Val >> u8Offset) & 0x01)


#define HBYTE(u16)			((U8 *)(&u16))[0]
#define LBYTE(u16)			((U8 *)(&u16))[1]

#define pHBYTE(pu16)			((U8 *)pu16)[0]
#define pLBYTE(pu16)			((U8 *)pu16)[1]


extern void uty_delay(U16 u16Val);

extern U8 uty_dec2bcd(U8 val);
extern U8 uty_bcd2dec(U8 val);
extern U8 uty_hex2bcd(U8 val);
extern U8 uty_hex2ascii(U8 val);
extern U8 uty_ascii2hex(U8 val);


#endif /*_UTILITY_H_*/


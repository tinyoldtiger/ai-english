
/***************************************************************************************
****************************************************************************************
* FILE		: message.h
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


#ifndef _MESSAGE_H_
#define _MESSAGE_H_


#include "type.h"


#define MSG_ARRAY_SIZE	4


typedef enum
{
	MSG_NULL		= 0x00,					/*have no message*/
	MSG_KEY		= 0x01,					/*key message*/
	MSG_UART		= 0x02,					/*uart message*/
	MSG_RTC		= 0x03,					/*real time counter message*/
	MSG_MSTIMER	= 0x04,					/*timer message*/
	MSG_TEST		= 0x0F,					/*special for test message*/
	MSG_LD_IDENTIFY =0x05,
};


extern void msg_init(void);
extern void msg_put_in(U16 u16);
extern void msg_send_msg(U8 MsgType, U8 Val);
extern void msg_get_out(U16 *pU16);




#define MSG_SEND_MSG(MsgType, Val)		msg_send_msg(MsgType, Val)

#define MSG_SEND_DATA(u16) 				msg_put_in(u16)

#define MSG_GET_MSG(pU16)					msg_get_out(pU16)
#define MSG_TYPE(u16)						((U8 *)(&u16))[0]
#define MSG_VALUE(u16)						((U8 *)(&u16))[1]
#define MSG_GET_DATA(pU16)				msg_get_out(pU16)


#endif

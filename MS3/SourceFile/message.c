
/***************************************************************************************
****************************************************************************************
* FILE		: message.c
* Description	: FIFO message queue
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





static U8 data u8MsgHead;		/*position that msg will be put in*/
static U8 data u8MsgTail;		/*position that msg will be get out*/
static U8 data u8MsgNum;		/*msg number*/
static U16 data u16MsgArray[MSG_ARRAY_SIZE];	/*msg queue*/


/*==================================================================
* Function	: msg_init
* Description	: init message
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void msg_init(void)
{
	u8MsgHead = 0;
	u8MsgTail = 0;
	u8MsgNum = 0;
}


/*==================================================================
* Function	: msg_put_in
* Description	: Put in a U16 data in msg queue.
			  Because there is no return value to indicate success or fail, 
			  make sure msg queue is large enough, that is MSG_ARRAY_SIZE is big enough!!!
			  You can get a suitable MSG_ARRAY_SIZE with the debug message.
* Input Para	: U16 u16Val	: data to be put in
* Output Para	: void
* Return Value: void
==================================================================*/
void msg_put_in(U16 u16)	
{
	U8 EA_MAP;

	EA_MAP = INTERRUPT_GET();
	INTERRUPT_DISABLE();
	
	if (u8MsgNum >= MSG_ARRAY_SIZE)
	{
		INTERRUPT_SET(EA_MAP);
		return;
	}
	
	//first put in data, then increase u8MsgHead
	u16MsgArray[ u8MsgHead] = u16;	
	u8MsgHead++;
	if (u8MsgHead >= MSG_ARRAY_SIZE)
	{
		u8MsgHead = 0;
	}	
	u8MsgNum++;

	INTERRUPT_SET(EA_MAP);
	return;
}

void msg_send_msg(U8 MsgType, U8 Val)
{
	U8 EA_MAP;

	EA_MAP = INTERRUPT_GET();
	INTERRUPT_DISABLE();
	if (u8MsgNum >= MSG_ARRAY_SIZE)
	{
		INTERRUPT_SET(EA_MAP);
		return;
	}

	//first put in data, then increase u8MsgHead
	((U8 *)(&(u16MsgArray[ u8MsgHead])))[0] = MsgType;	
	((U8 *)(&(u16MsgArray[ u8MsgHead])))[1] = Val;	
	
	u8MsgHead++;
	if (u8MsgHead >= MSG_ARRAY_SIZE)
	{
		u8MsgHead = 0;
	}	
	u8MsgNum++;

	INTERRUPT_SET(EA_MAP);
	return;
}

/*==================================================================
* Function	: msg_get_out
* Description	: get a U16 data out of the msg queue.
			  If the msg queue is empty, get MSG_NULL
* Input Para	: void
* Output Para	: U16 * pu16Val	: pointer to hold data
* Return Value: void
==================================================================*/
void msg_get_out(U16 *pU16)
{
	U8 EA_MAP;

	
	
	if (u8MsgNum == 0)
	{
		* pU16 = 0x0000;
		return;
	}

	EA_MAP = INTERRUPT_GET();
	INTERRUPT_DISABLE();

	//first get out data, then increase u8MsgTail
	*pU16 = u16MsgArray[u8MsgTail];
	u8MsgTail++;
	if (u8MsgTail >= MSG_ARRAY_SIZE)
	{
		u8MsgTail = 0;
	}
	u8MsgNum--;

	INTERRUPT_SET(EA_MAP);
	return;
}


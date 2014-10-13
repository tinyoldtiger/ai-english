
/***************************************************************************************
****************************************************************************************
* FILE		: mmi.c
* Description	: man machine interface
*			  
* Copyright (c) 2003~2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   1.0		Wang Shaowei	2003/07/16	Initial Version (MCU System)
   2.0		Wang Shaowei	2005/06/01	MS2
   3.0		Wang Shaowei	2007/03/11	MS3
   4.0		Wang Shaowei	2011/02/01	MS4
   
****************************************************************************************
****************************************************************************************/


#include "common.h"

#define Key_BackSpace	0x08

Function idata fMMIProc;

bool bTimer = FALSE;


static void mmi_idle_setup(void);
static void mmi_idle_proc(void);
static void mmi_designeasy_setup(void);
static void mmi_designeasy_proc(void);
static void mmi_huayu_setup(void);
static void mmi_huayu_proc(void);
static void display_time_setup(void);
static void display_time_proc(void);

/*==================================================================
* Function	: mmi_init
* Description	: init mmi
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void mmi_init(void)
{
	mmi_idle_setup();
	fMMIProc = mmi_idle_proc;
}



void mmi_idle_setup(void)
{
	uprintf("\nMS3.21 Start\n");
	uprintf("\nHardware Plat:MCU 51Series\n");
	uprintf("\nSoftware Version:MS3.21-2011.2.14\n");
	uprintf("\Author: wangsw\n");
	uprintf("\Blog: www.eefocus\\wangsw\\blog\n");
	uprintf("\n\n");
	
	uprintf("1:���׵���\n");
	uprintf("2:������\n");
	uprintf("3:��ʾʱ��\n");
	
	uprintf("Menu = idle\n");
	uprintf("Please press 1 , 2 or 3  to select menu\n");
}

void mmi_idle_proc(void)
{
	switch(KeyStore)
	{
		case '1':
			mmi_designeasy_setup();
			fMMIProc = mmi_designeasy_proc;
			break;
		case '2':
			mmi_huayu_setup();
			fMMIProc = mmi_huayu_proc;
			break;
		case '3':
			display_time_setup();
			fMMIProc = display_time_proc;
			break;
			
	}
	
}


void display_time_setup(void)
{
	uprintf("\nMS3.21 Start\n");
	uprintf("\nHardware Plat:MCU 51Series\n");
	uprintf("\nSoftware Version:MS3.21-2011.2.14\n");
	uprintf("\Author: wangsw\n");
	uprintf("\Blog: www.eefocus\\wangsw\\blog\n");
	uprintf("\n\n");

	uprintf("0:�˻��ϼ�Ŀ¼\n");
	uprintf("1:���׵���\n");
	uprintf("2:������\n");
	uprintf("3:Timer Display On\n");
	uprintf("4:Timer Display Stop\n");
	
	uprintf("Menu = Timer\n");
	uprintf("Please press 1 , 2 , 3 or 4 to select menu\n");

	bTimer = TRUE;
}

void display_time_proc(void)
{
	switch(KeyStore)
	{
		case '0':
			mmi_idle_setup();
			fMMIProc = mmi_idle_proc;
			break;
		case '1':
			mmi_designeasy_setup();
			fMMIProc = mmi_designeasy_proc;
			break;
		case '2':
			mmi_huayu_setup();
			fMMIProc = mmi_huayu_proc;
			break;
		case '3':
			bTimer = TRUE;
			return;
	}
	
	bTimer = FALSE;
}

void display_time_routine(void)
{
	U8 i;

	if(!bTimer)
	{
		return;
	}
	/*��������ڴ���ԭλ��ʾ*/
	for(i = 0; i < 25; i++)
	{
		uputbyte(Key_BackSpace);
	}
	/*��ʾ*/
	printf("timer is = %d :%d :%d",(U16)tTCMember.hour,(U16)tTCMember.minute,(U16)tTCMember.second);
}

void mmi_designeasy_setup(void)
{
	uprintf("\n52edk.taobao.com\n");
	uprintf("\n���׵���\n");
	uprintf("a:��ɫ������ݵ����Ʒ��\n");
	uprintf("b:�䵥ҵ��\n");
	uprintf("c:���������ҵ��\n");

	uprintf("0:�˻��ϼ�Ŀ¼\n");
	uprintf("2:���뻪��Ŀ¼\n");
}

void mmi_designeasy_proc(void)
{
	switch(KeyStore)
	{
		case '0':
			mmi_idle_setup();
			fMMIProc = mmi_idle_proc;
			break;
		case '2':
			mmi_huayu_setup();
			fMMIProc = mmi_huayu_proc;
			break;
	}
}
void mmi_huayu_setup(void)
{
	uprintf("\nwww.huayusoft.com\n");
	uprintf("\n������\n");
	uprintf("a:����001�ֻ�����ģ��\n");
	uprintf("b:P1220�ֳ�PDA\n");
	uprintf("c:쫷�001����PDA\n");
	
	uprintf("0:�˻��ϼ�Ŀ¼\n");
	uprintf("1:���봴��Ŀ¼\n");
}

void mmi_huayu_proc(void)
{
	switch(KeyStore)
	{
		case '0':
			mmi_idle_setup();
			fMMIProc = mmi_idle_proc;
			break;
		case '1':
			mmi_designeasy_setup();
			fMMIProc = mmi_designeasy_proc;
			break;
	}
}



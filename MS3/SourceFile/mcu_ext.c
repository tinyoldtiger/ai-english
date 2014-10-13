
/***************************************************************************************
****************************************************************************************
* FILE		: mcu_ext.c
* Description	: 
*			  
* Copyright (c) 2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		WANG SHAOWEI	2007/05/09	Initial Version
   
****************************************************************************************
****************************************************************************************/

//this file is related with cpu'peripheral such as key,led,lcd
//add by huihui @2014��10��11��15:30:58


#include "common.h"













#ifdef DP51
sbit SDA = P1^0;			/*ģ�⴮��ת���пڣ��½�����Ч�����Ϊ�͵�ƽ�ɿص���*/
sbit SCL = P1^1;			/*ģ�⴮����ת����ʱ���ź���*/

sbit KEY = P1^2;			/*���̣��͵�ƽ��Ч�����λ*/

sbit DISPLAY0 = P1^3;		/*EBIT4, �͵�ƽ��Ч*/
sbit DISPLAY1 = P1^4;		/*EBIT3*/
sbit DISPLAY2 = P1^5;		/*EBIT2*/
sbit DISPLAY3 = P1^6;		/*EBIT1*/

sbit LED = P1^7;			/*EBIT0���͵�ƽ��Ч*/

U8 code LedDisplayMap[2][16] =
{
	{0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E},
	{0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E}
};






U8 key_read(void)
{
	U8 i;
	U8 KeySave;
	P1 = 0xFF;
	SDA = 0;			/*ע��,ԭ������Ϊ0,����Ϊ1*/
	for(i = 0; i < 8; i++)			/*r�Ƚ�ɨ�����϶���Ϊ�ߵ�ƽ*/
	{
		SCL = 0;		
		SCL = 1;
	}
	uty_delay(1);
	if(KEY)
	{
		return(ERROR);
	}

	
	SDA = 1;			/*ע��,ԭ������Ϊ0,����Ϊ1*/
	for(i = 0; i < 8; i++)			/*r�Ƚ�ɨ�����϶���Ϊ�ߵ�ƽ*/
	{
		SCL = 0;	
		SCL = 1;
		uty_delay(1);
		if(KEY)
		{
			KeySave = i;
			break;
		}

	}
	SDA = 0;			/*ע��,ԭ������Ϊ0,����Ϊ1*/
	for(i = 0; i < 8; i++)			/*r�Ƚ�ɨ�����϶���Ϊ�ߵ�ƽ*/
	{
		SCL = 0;	
		SCL = 1;
		uty_delay(1);
		if(!KEY)
		{
			if(KeySave == i)
			{
				return(i);
			}
			else
			{
				return(ERROR);
			}
		}
	}


	return(ERROR);				/*r��û��ɨ�赽���¼��ͷ���ERROR*/
}


void SendData(U8 Val)
{
	U8 i;
	
	SCL = 1;
	for(i = 0; i < 8; i++)
	{
		if(Val & 0x80)  	/*�ж�����*/
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;					/*����ʱ�Ӷ���*/
		SCL = 1;
		Val = Val << 1;
	}
}


void led_control(U8 LedIndex)
{
	P1 = 0xFF;
	if((LedIndex > 0) && (LedIndex < 9))
	{
		LedIndex = 1 << (LedIndex - 1);		/*r��1����(LedIndex-1)λ��,���͵�������ת����·*/
		SendData(~LedIndex);
		LED = 0;							/*r����DP-51��Q1������,�����Ϳ��Կ���LED�ܵ���*/
	}
	
	
}


 void LedDisplay_control(U1 boDp, U8 LedDisplayIndex, U8 value)
{
	U1 i;
	i = boDp;
	P1 = 0xFF;
	SendData(LedDisplayMap[i][value]);		/*r����LED��ʾ���ݵ�����ת����·*/

	P1 &= ~(0x04 << LedDisplayIndex);
}

#else

/*==================================================================
* Function	: key_read
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
U8 key_read(void)
{
	U8 KeyRead;
	U8 KeySave;
	
	P1 = 0x0F;
	uty_delay(1);	/*�����ʱ���ö˿ڵ�ƽ�ȶ�������׼ȷ*/
	KeyRead = P1 & 0x0F;
	if((KeyRead & 0x0F) == 0x0F)
	{
		return(ERROR);
	}
	
	P1 = 0xF0;
	uty_delay(1);	/*�����ʱ���ö˿ڵ�ƽ�ȶ�������׼ȷ*/
	KeyRead = KeyRead |( P1 & 0xF0);
	
	return(KeyRead);
}




#endif


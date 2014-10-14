/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : main.c
��Ʒ����:�������ݴ��䵽U���ļ�,����"�����Ĺ���ʦ����","���ƵĹ���ʦ����"
����:���Ӱײ�

�汾��:V1.0
ʱ��:2009-4-14
����:ͨ�����ڷ��͵�����,��U���������ļ�������.ʹ��CH375��ΪUSB HOSTоƬ,STM32Ϊ����CPU
	USB���벿�ֲ���CH375�ٷ���,������һ���̶ȵķ�װ.�˿⹦����΢����,
	ͬһʱ��ֻ֧��һ���ļ��Ĵ򿪶�д.
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "STM32Lib\\stm32f10x.h"

#include "hal.h"
//#include "yd.h"
#include "my375lib.h"

int CH375_init(void)
{
	u8 i;
  
  
	ChipHalInit();//Ƭ��Ӳ����ʼ��
  
	ChipOutHalInit();//Ƭ��Ӳ����ʼ��
	
	//ϵͳ��ʼ����ʶ-�������ƻ���
	for(i=0;i<4;i++)
	{
		SET_FILE_LED;
		CLR_COPY_LED;
		Timer1=100;
		while(Timer1);
		SET_COPY_LED;
		CLR_FILE_LED;
		Timer1=200;
		while(Timer1);
	}
	CLR_COPY_LED;

	
	USART1_Puts("\r\n�����U��\r\n");
	//����Ҫ����һ�´��ڷ��ö�����ж�
	SetUartFileDis();

	//1.��ʼ��U��Ӳ��
init_u_again:	
	if(InitUDisk()!=0)
	{
		USART1_Puts("U�̳�ʼ��ʧ��\r\n");
		goto init_u_again;
	}
	else
	{
		USART1_Puts("U�̳�ʼ���ɹ�,Ҫ�����ļ��ɰ��°���\r\n");
	}

wait_key:
	while(!GET_KEY);
	for(i=0;i<5;i++)
	{
		Timer1=10;
		while(Timer1);
		if(!GET_KEY)
		{
			goto wait_key;
		}
	}
	
	//�����ļ��кͽ�ҪCOPY���ļ�����
	if(InitFile()==0)
	{
		//�ɹ�����
		USART1_Puts("�ļ�ϵͳ�Ѿ�׼������,����5���ڴ����ļ�,������Ϻ��ٰ��°���׼����һ���ļ�\r\n");
	}
	else
	{
		//ʧ��
		USART1_Puts("�ļ�ϵͳ��ʼ��ʧ��,����������Դ\r\n");
		goto wait_key;
	}

	//�򿪴��ڽ����ж�
	SetUartFileEn();
	//�������̶��ڵȴ��ļ��������
	while(UartToFile()==FALSE);
	USART1_Puts("\r\n�ļ����������ʱ�޵�,���Ҫ�ٴ��ļ�,�밴�°���\r\n");
	//�����ļ�
	goto wait_key;

}



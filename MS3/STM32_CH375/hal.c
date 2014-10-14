/***************************************************
**HAL.c
**��Ҫ����оƬӲ�����ڲ���Χ���ⲿ��Χ�ĳ�ʼ��������INIT����
**��MAIN�е��ã�ʹMAIN�����о�����Ӳ�����޹�
***************************************************/

#include "STM32Lib\\stm32f10x.h"


//�����ڲ�Ӳ��ģ������ú���
extern void GPIO_Configuration(void);			//GPIO
extern void NVIC_Configuration(void);			//NVIC
extern void RCC_Configuration(void);			//RCC
extern void USART_Configuration(void);			//USART


//�����ⲿӲ��ģ������ú���

/*******************************
**������:ChipHalInit()
**����:Ƭ��Ӳ����ʼ��
*******************************/
extern void WL_Debug(void);
void  ChipHalInit(void)
{
	//��ʼ��ʱ��Դ
	RCC_Configuration();
	  
	//��ʼ���ж�
	NVIC_Configuration();
	
	//��ʼ��GPIO
	GPIO_Configuration();
	
	//����
	USART_Configuration();
}


/*********************************
**������:ChipOutHalInit()
**����:Ƭ��Ӳ����ʼ��
*********************************/
void  ChipOutHalInit(void)
{

}

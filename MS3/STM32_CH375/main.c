/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : main.c
产品代码:串口数据传输到U盘文件,又名"淫荡的工程师利器","郁闷的工程师利器"
作者:电子白菜

版本号:V1.0
时间:2009-4-14
功能:通过串口发送的数据,在U盘上生成文件并保存.使用CH375作为USB HOST芯片,STM32为主控CPU
	USB代码部分采用CH375官方库,并加以一定程度的封装.此库功能稍微有限,
	同一时间只支持一个文件的打开读写.
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "STM32Lib\\stm32f10x.h"

#include "hal.h"
//#include "yd.h"
#include "my375lib.h"

int CH375_init(void)
{
	u8 i;
  
  
	ChipHalInit();//片内硬件初始化
  
	ChipOutHalInit();//片外硬件初始化
	
	//系统初始化标识-让两个灯互闪
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

	
	USART1_Puts("\r\n请插入U盘\r\n");
	//这里要屏蔽一下串口放置额外的中断
	SetUartFileDis();

	//1.初始化U盘硬件
init_u_again:	
	if(InitUDisk()!=0)
	{
		USART1_Puts("U盘初始化失败\r\n");
		goto init_u_again;
	}
	else
	{
		USART1_Puts("U盘初始化成功,要传输文件可按下按键\r\n");
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
	
	//生成文件夹和将要COPY的文件对象
	if(InitFile()==0)
	{
		//成功生成
		USART1_Puts("文件系统已经准备好了,请在5秒内传输文件,传输完毕后再按下按键准备下一个文件\r\n");
	}
	else
	{
		//失败
		USART1_Puts("文件系统初始化失败,建议重启电源\r\n");
		goto wait_key;
	}

	//打开串口接收中断
	SetUartFileEn();
	//整个过程都在等待文件传输完成
	while(UartToFile()==FALSE);
	USART1_Puts("\r\n文件传输结束或时限到,如果要再传文件,请按下按键\r\n");
	//结束文件
	goto wait_key;

}



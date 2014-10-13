
/***************************************************************************************
****************************************************************************************
* FILE		: mcu.c
* Description	: 
*			  
* Copyright (c) 2007 by WANG SHAOWEI. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		WANG SHAOWEI	2007/04/29	Initial Version
   
****************************************************************************************
****************************************************************************************/

//this file is related with cpu//add by huihui @2014��10��11��15:30:58

#include "common.h"



/*==================================================================
* Function	: port_init
* Description	: Port init
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void port_init(void)
{
	/*
	P0 = 0xFF;
	P1 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	*/
}



/*==================================================================
* Function	: Interrupt_priority_init
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Interrupt_priority_init(void)
{
/*

	//UART
	PS = 1;
	SETBIT(IPH, 4);		

//TIMER2
	PT2 = 0;
	SETBIT(IPH, 5);		
	
//TIMER1
	PT1 = 0;
	RESETBIT(IPH, 3);	

//INT1
	PX1 = 0;
	RESETBIT(IPH, 2);	

//TIMER0
	PT0 = 0;
	RESETBIT(IPH, 1);	
	
//INT0
	PX0 = 0;
	RESETBIT(IPH, 0);	
*/

}


/*==================================================================
* Function	: extern_interrupt0_init
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void extern_interrupt0_init(U8 Enable, U8 EdgeEnable)
{
	
	//IE0 = 0;						/*�жϱ��λ*/
	/*
	IT0 = EdgeEnable;
	EX0 = Enable;
	*/
}


/*==================================================================
* Function	: extern_interrupt1_init
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void extern_interrupt1_init(U8 Enable, U8 EdgeEnable)
{
	
	//IE1 = 0;						/*�жϱ��λ*/
	/*
	IT1 = EdgeEnable;
	EX1 = Enable;
	*/
}



/*==================================================================
* Function	: mode_init
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void mode_init(void)
{
#ifdef SPEEDUP
	SETBIT(CKCON, 0);						
#else
	RESETBIT(CKCON, 0);
#endif
}


/*==================================================================
* Function	: timer0_init
* Description	: Timer0 initialize
* Input Para	: bStart				Enable Timer0
			  bInt0Relation		Relation with Int0
			  bTimerMode			0:timer mode, 1:counter mode
			  bInterruptEnable		Interrupt enable
			  WorkMode			work mode setting,It has 0,1,2,3 four work mode,
								the counter value difference
								0: 13bit counter
								1: 16bit counter
								2: auto load 8bit counter
								3: two 8bit counter
			  TH0Data			High counter value
			  TL0Data				Low counter value
* Output Para	: void
* Return Value: void
==================================================================*/
void timer0_init(U1 Enable,
				U8 WorkMode,
				U8 TH0Data,
				U8 TL0Data)
{	
	TF0 = 0;					/*��ʱ���жϱ�־λ*/

	RESETBIT(TMOD, 3);		/*����INT0����*/

	SETBIT(TMOD, 2);		/*��ʱ��������ģʽ,TRUEΪ��ʱ��,FALSEΪ������*/

	

	
	if(WorkMode & 0x02)		/*��ʱ/������0������ʽ�趨*/
	{
		SETBIT(TMOD, 1);		
	}
	else
	{
		RESETBIT(TMOD, 1);
	}
	
	if(WorkMode & 0x01)
	{
		SETBIT(TMOD, 0);
	}
	else
	{
		RESETBIT(TMOD, 0);
	}
	TH0 = TH0Data;
	TL0 = TL0Data;

	ET0 = (U1)1;				/*�ж�����*/
	TR0 = Enable;

}


/*==================================================================
* Function	: timer2_init
* Description	: The timer2 as system timer,so it only initialize  for system time
* Input Para	: bStart				Enable Timer2
			  TH2Data			High counter value
* Output Para	: void
* Return Value: void
==================================================================*/
void timer2_init(U1 Enable, TimerInterval eTimerInterval)
{
	TH2 = eTimerInterval;
	RCAP2H = eTimerInterval;

	
	TL2 = 0x00;
	RCAP2L = 0x00;
	
	T2MOD = 0x00;
	if(Enable)
	{
		T2CON = 0x04;
	}
	else
	{
		T2CON = 0x00;
	}

	ET2 = 1;
}


/*==================================================================
* Function	: uart_init
* Description	: UART initialize,use timer1
* Input Para	: UartBaudrate eBaudRate	: baud rate
* Output Para	: void
* Return Value: void
==================================================================*/
void uart_init(UartBaudrate BaudRate)
{
	ES = 0;			/*�ش��п��ж�*/	

#ifdef SPEEDUP			/*�����ٶȼӱ�*/
	RESETBIT(PCON, 7);
#else
	SETBIT(PCON, 7);
#endif

	if(BaudRate == UART_RATE1152)
	{
		BaudRate = UART_RATE576;
		SETBIT(PCON, 7);
	}

	TMOD &= 0x0F;
	TMOD |= 0x20;
	ET1 = 0;				/*�ж���Ч*/
	TH1 = BaudRate;
	TL1 = BaudRate;
	TR1 = 1;				/*��ʱ������*/
	SCON = 0x50;

	RI = 0;
	
	ES = 1;				/*���п��ж�printf��Ҫ���ڹر�*/
}


/*==================================================================
* Function	: extern_interrupt0
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void extern_interrupt0(void) interrupt 0
{

}


/*==================================================================
* Function	: extern_interrupt1
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void extern_interrupt1(void) interrupt 2
{

}


/*==================================================================
* Function	: uart_put
* Description	: send U8 as raw data through uart
* Input Para	: U8 val	: the data to send
* Output Para	: void
* Return Value: void
==================================================================*/
void uart_put(U8 u8)
{
	U8 ES_MAP;
	
	ES_MAP = ES;	
	
	ES = 0;
	SBUF = u8;
	while(!TI);
	TI = 0;
	

	ES = ES_MAP;
}


/*==================================================================
* Function	: UartInterruptService
* Description	: The UART interrupt server
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
static void UartInterruptService(void) interrupt 4
{
	ES = 0;
	RI = 0;
	uart_process(SBUF);

	ES=1;
}


#if 0
/*==================================================================
* Function	: Timer0InterruptService
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Timer0InterruptService(void) interrupt 1
{
	timer0_process();
}
#endif


#if 0		/*ȱʡ���ڴ���*/
/*==================================================================
* Function	: Timer1InterruptService
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Timer1InterruptService(void) interrupt 3
{

}
#endif


/*==================================================================
* Function	: Timer2InterruptService
* Description	: Timer2 interrupt as system timer,It is importance
* Input Para	: void
* Output Para	: void
* Return Value: void
==================================================================*/
void Timer2InterruptService(void) interrupt 5 
{
	ET2 = 0;							/*close interrupt*/
	TF2 = 0;							/*clear interrupt flag*/

	system_process();

	ET2 = 1;
}










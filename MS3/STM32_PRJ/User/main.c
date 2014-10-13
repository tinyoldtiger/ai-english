#include "stm32f10x.h"
#include "usart.h"
#include "LD3320.h"

/******************************************************************************/
extern void boot_main(void);

int main(void)
{
	port_init();
	
	USART_init();
	
	Interrupt_priority_init();
	
	/*Flash У��ȣ�Ӧ����ϵͳ�Ƚ��ϸ�ĵط�*/
	flash_init();

	
	LD3320_init();	  
	
  CH375_init();	
	
	init_process();	/*�����ʼ��*/
	
	//printf("\r\n ��ʼ����LD3320���Գ��� \r\n");	
	
	LD3320_main();				//LD3320ִ�к���
	
	for(;;)
	{
			boot_main();
	}
}
/*********************************************END OF FILE**********************/

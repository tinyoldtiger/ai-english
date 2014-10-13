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
	
	/*Flash 校验等，应用于系统比较严格的地方*/
	flash_init();

	
	LD3320_init();	  
	
  CH375_init();	
	
	init_process();	/*程序初始化*/
	
	//printf("\r\n 开始运行LD3320测试程序 \r\n");	
	
	LD3320_main();				//LD3320执行函数
	
	for(;;)
	{
			boot_main();
	}
}
/*********************************************END OF FILE**********************/

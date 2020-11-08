#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	HAL_Init();		/* 初始化HAL库 	*/
	
	/* 初始化M4内核时钟 */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}

	led_init();		/* 初始化LED  	*/
	beep_init();	/* 初始化蜂鸣器 */
	key_init();		/* 初始化按键 	*/
	
	while(1) 
	{
		LED0(0);
		delay(100);
		LED0(1);
		delay(100);
	}
}

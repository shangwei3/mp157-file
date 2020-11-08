#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	HAL_Init();		/* 初始化HAL库 	*/
	led_init();		/* 初始化LED  	*/
	beep_init();	/* 初始化蜂鸣器 */

	while(1) 
	{
		LED0(0);	/* 打开LED0 	*/
		BEEP(0);	/* 打开蜂鸣器 	*/
		delay(100);
		LED0(1);	/* 关闭LED0 	*/
		BEEP(1);	/* 关闭蜂鸣器 	*/
		delay(100);
	}
}

#include "./SYSTEM/sys/sys.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	HAL_Init();	/* 初始化HAL库 */
	led_init();	/* 初始化LED  */

	while(1) 
	{
		LED0(0);	/* 打开LED0 */
		LED1(1);	/* 关闭LED1 */
		delay(100);
		LED0(1);	/* 关闭LED0 */
		LED1(0);	/* 打开LED1 */
		delay(100);
	}
}

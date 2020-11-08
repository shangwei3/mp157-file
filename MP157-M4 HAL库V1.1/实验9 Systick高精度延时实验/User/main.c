#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	HAL_Init();		/* 初始化HAL库 	*/
	
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 */
	delay_init(209);        /* 延时初始化 */
	led_init();				/* 初始化LED  	*/
	beep_init();			/* 初始化蜂鸣器 */
	extix_init();			/* 初始化中断 	*/

	while(1) 
	{
		LED0_TOGGLE();
		delay_ms(500);
	}
}

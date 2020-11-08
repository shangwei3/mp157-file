/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       窗口看门狗 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32MP1开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/WWDG/wwdg.h"

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
	LED0(0);               	/* 点亮LED0(红灯) */
    delay_ms(300);        	/* 延时100ms再初始化看门狗,LED0的变化"可见" */
	wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_16); /* 计数器值为7f,窗口寄存器为5f,分频数为16 */
	
	while(1) 
	{
		LED0(1);                        /* 关闭红灯 */
	}
}

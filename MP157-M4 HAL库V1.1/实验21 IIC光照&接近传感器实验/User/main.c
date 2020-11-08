/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brie        APC3216C光照和接近传感器实验
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
#include "math.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/AP3216C/ap3216c.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	uint16_t ir,als,ps; 
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* 串口初始化为115200 			*/
	delay_init(209);        	/* 延时初始化 					*/
	led_init();					/* 初始化LED  					*/
	key_init();            		/* 初始化按键 					*/
    adc_init();             	/* 初始化ADC 					*/

	while(ap3216c_init())		/* 检测不到AP3216C 				*/
	{
		printf("AP3216C Check Failed!\r\n");
		delay_ms(500);
		LED0_TOGGLE();/* DS0闪烁 						*/
	}			
	
    while(1)
    {
        ap3216c_read_data(&ir,&ps,&als);	//读取数据 
		printf("ir = %d, ps = %d, als = %d\r\n", ir, ps, als);
		LED0_TOGGLE();/* DS0闪烁 						*/
        delay_ms(120); 
	}	
}

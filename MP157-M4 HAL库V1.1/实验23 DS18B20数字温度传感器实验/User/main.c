/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brie        DS18B20数字温度传感器 实验
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
#include "./BSP/DS18B20/ds18b20.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint8_t t = 0;
    short temperature;
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* 串口初始化为115200 	*/
	delay_init(209);        	/* 延时初始化 			*/
	usmart_dev.init(209);		/* 初始化USMART 		*/
	led_init();					/* 初始化LED  			*/
	key_init();            		/* 初始化按键 			*/
	
    while (ds18b20_init())    	/* DS18B20初始化 		*/
    {
		printf("DS18B20 Error!\r\n");
        delay_ms(1000);
    }	
	
    while (1)
    {
        t++;

        if (t == 20)
        {
            t = 0;
			 temperature = ds18b20_get_temperature();
			printf("DS18B20 Temp=%.1f\r\n", temperature / 10.0f);
            LED0_TOGGLE();  /* LED0闪烁 */
        }
		delay_ms(10);
    }	
}

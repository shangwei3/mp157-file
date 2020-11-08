/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-12
 * @brie        硬件随机数(RNG) 实验
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
#include "./USMART/usmart.h"
#include "./BSP/RNG/rng.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint32_t random;
    uint8_t t = 0, key;
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 	*/
	delay_init(209);        /* 延时初始化 			*/
	usmart_dev.init(209);   /* 初始化USMART 		*/
	led_init();				/* 初始化LED  			*/
	key_init();            	/* 初始化按键 			*/
	rng_init();				/* 初始化随机数发生器 */

    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)
        {
            random = rng_get_random_num();
			printf("Random Num:%u\r\n", random);
        }

        if ((t % 100) == 0)
        {
			t = 0;
            LED0_TOGGLE();                       /* 每200ms,翻转一次LED0 */
            random = rng_get_random_range(0, 9); /* 取[0,9]区间的随机数 */
			printf("Random Num[0-9]:%u\r\n", random);
        }

        delay_ms(10);
        t++;
    }
}

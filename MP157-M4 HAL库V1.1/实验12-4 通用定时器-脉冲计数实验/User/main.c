/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brie      	通用定时器脉冲计数 实验
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
#include "./BSP/TIMER/gtim.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint32_t curcnt = 0;
    uint32_t oldcnt = 0;
    uint8_t key = 0;
    uint8_t t = 0;
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 	*/
	delay_init(209);        /* 延时初始化 			*/
	led_init();				/* 初始化LED  			*/
	key_init();            	/* 初始化按键 			*/
    gtim_timx_cnt_chy_init(0);          /* 定时器计数初始化, 不分频 */
    gtim_timx_cnt_chy_restart();        /* 重启计数 */
	
	while(1) 
	{
        key = key_scan(0);      /* 扫描按键 */

        if (key == KEY0_PRES)   /* KEY0按键按下,重启计数 */
        {
            gtim_timx_cnt_chy_restart();        /* 重新启动计数 */
        }

        curcnt = gtim_timx_cnt_chy_get_count(); /* 获取计数值 */

        if (oldcnt != curcnt)
        {
            oldcnt = curcnt;
            printf("CNT:%d\r\n", oldcnt);       /* 打印脉冲个数 */
        }

        t++;

        if (t > 20)         /* 200ms进入一次 */
        {
            t = 0;
            LED0_TOGGLE();  /* LED0闪烁 ,提示程序运行 */
        }

        delay_ms(10);
	}
}

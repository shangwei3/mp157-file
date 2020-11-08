/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brie      	通用定时器输入捕获 实验
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

extern uint8_t  g_timxchy_cap_sta;  /* 输入捕获状态 */
extern uint16_t g_timxchy_cap_val;  /* 输入捕获值 */

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	unsigned int i = 0;
	long long temp = 0;
	
	HAL_Init();		/* 初始化HAL库 	*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 	*/
	delay_init(209);        /* 延时初始化 			*/
	led_init();				/* 初始化LED  			*/
	key_init();            	/* 初始化按键 			*/
	gtim_timx_cap_chy_init(0XFFFF, 209 - 1);  	/* 以1Mhz的频率计数 捕获 */

	while(1) 
	{
        delay_ms(10);
		
        if (g_timxchy_cap_sta & 0X80)             /* 成功捕获到了一次高电平 */
        {
            temp = g_timxchy_cap_sta&0X3F; 
            temp *= 65536;                        /* 溢出时间总和 */
            temp += g_timxchy_cap_val;            /* 得到总的高电平时间 */
            printf("HIGH:%lld us\r\n",temp);      /* 打印总的高点平时间 */
            g_timxchy_cap_sta = 0;                /* 开启下一次捕获 */
        }
		i++;
		if(i == 50) 
		{
			i = 0;
			LED0_TOGGLE();
		}
	}
}

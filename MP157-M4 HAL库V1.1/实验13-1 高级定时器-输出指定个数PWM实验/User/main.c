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
#include "./BSP/TIMER/atim.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
  uint8_t key = 0;
	
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
    gtim_timx_npwm_chy_init(5000 - 1, 20900 - 1);   /* 10Khz的计数频率,2hz的PWM频率. */
    GTIM_TIMX_NPWM_CHY_CCRX = 2500; /* 设置PWM占空比,50%,这样可以控制每一个PWM周期,LED1
                                     * 有一半时间是亮的,一半时间是灭的,LED1亮灭一次,表示一个PWM波
                                     */
    gtim_timx_npwm_chy_set(5);      /* 输出5个PWM波(控制LED1闪烁5次) */
	
	while(1) 
	{
        key = key_scan(0);

        if (key == KEY0_PRES)   /* KEY0按下 */
        {
            gtim_timx_npwm_chy_set(5);  /* 输出5个PWM波(控制LED2(BLUE)闪烁5次) */
        }

        delay_ms(10);
	}
}

/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-16
 * @brie        DAC输出 实验
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
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/DAC/dac.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint8_t t = 0; 
    uint8_t key;
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* 串口初始化为115200 	*/
	delay_init(209);        	/* 延时初始化 			*/
	led_init();					/* 初始化LED  			*/
	key_init();            		/* 初始化按键 			*/
    adc_init();             	/* 初始化ADC 			*/
	dac_init(DAC_CHANNEL_1);  	/* 初始化DAC1_OUT1通道 	*/
	
    while (1)
    {	
        t++;
        key = key_scan(0);  /* 按键扫描 */

        if (key == KEY0_PRES)       /* 高采样率 , 约100hz波形 */
        {
            dac_triangular_wave(4095, 5, 2000, 100);    /* 幅值4095, 采样点间隔5us, 2000个采样点, 100个波形 */
       }
        else if (key == KEY1_PRES)  /* 低采样率 , 约100hz波形 */
        {
            dac_triangular_wave(4095, 500, 20, 100);    /* 幅值4095, 采样点间隔500us, 20个采样点, 100个波形 */ 
        }

        if (t == 10 )       /* 定时时间到了 */
        { 
            LED0_TOGGLE();  /* LED0闪烁 */
            t = 0;
        }

        delay_ms(10);
    }
}

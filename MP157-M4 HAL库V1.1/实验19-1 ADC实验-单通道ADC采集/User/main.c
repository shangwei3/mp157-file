/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        单通道ADC采集 实验
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

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint16_t adcx;
    float temp;
	uint8_t i = 0;
	
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
	adc_init();           	/* 初始化ADC 			*/
	
    while (1)
    {
		i++;
        adcx = adc_get_result_average(ADC_ADCX_CHY, 10); /* 获取通道19的转换值，10次取平均 */
        temp = (float)adcx * (3.3 / 65536);              /* 获取计算后的带小数的实际电压值，比如3.1111 */
		
        printf("ADC Value = %d, Voltage = %.3fV\r\n", adcx, temp);
		if(i == 5) 
		{
			i = 0;
			LED0_TOGGLE();
		}
        delay_ms(100);
    }
}

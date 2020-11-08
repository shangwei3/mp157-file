/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        单通道ADC过采样(26位分辨率) 实验
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
    uint32_t adcx;
    float temp;
	
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

    /* 初始化ADC, 1024x过采样, 不移位 
     * 26位ADC分辨率最大值为:67108864, 实际上由于分辨率太高 ,低位值已经不准确
     * 一般我们可以设置 ovss=4, 缩小16倍, 即22位分辨率, 低位值会相对稳定一些.
     * 这里我们为了演示26位过采样ADC转换效果, 把分辨率调到最大, 24位,并且不移位. 
     */
    adc_oversample_init(1024 - 1, ADC_RIGHTBITSHIFT_NONE);
   
	while (1)
    {	
		adcx = adc_get_result_average(ADC_ADCX_CHY, 10);/* 获取转换值，10次取平均 */
		temp = (float)adcx * (3.3 / 67108864); 	/* 转换电压值 */
		printf("ADC Value = %d, Voltage = %.3fV\r\n", adcx, temp);
		
		LED0_TOGGLE();
        delay_ms(100);
    }
}

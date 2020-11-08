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
    uint16_t adcx, dacx;
    float adc_temp, dac_temp;
    uint8_t t = 0;
    uint16_t dacval = 0;
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
    adc_init();             	/* 初始化ADC */
    dac_init(DAC_CHANNEL_1);  	/* 初始化DAC1_OUT1通道 	*/
	
	HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);/* 初始值为0 */

    while (1)
    {	
        t++;
        key = key_scan(0);          /* 按键扫描 */

        if (key == KEY0_PRES)
        {
            if (dacval < 4000)dacval += 200;

            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacval);/* 输出增大200 */
        }
        else if (key == KEY1_PRES)
        {
            if (dacval > 200)dacval -= 200;
            else dacval = 0;

            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacval);/* 输出减少200 */
        }

        if (t == 10 || key == KEY1_PRES || key == KEY0_PRES)    /* WKUP/KEY1按下了,或者定时时间到了 */
        {
			printf("\r\n");
            dacx = HAL_DAC_GetValue(&g_dac_handle, DAC_CHANNEL_1);/* 读取前面设置DAC1_OUT1的值 */
			dac_temp = (float)dacx * (3.3f / 4096);                  /* 得到DAC电压值 */
			printf("DAC Output Value = %d, DAC Output Voltage = %.2f\r\n", dacx, dac_temp);
			
            adcx=adc_get_result_average(ADC_ADCX_CHY, 10);      /* 得到ADC通道19的转换结果 */
            adc_temp = (float)adcx * (3.3 / 65536);          	/* 得到ADC电压值(adc是16bit的) */
			printf("ADC Input Value  = %d, ADC Input Voltage  = %.2f\r\n", adcx, adc_temp);
            
            LED0_TOGGLE();  /* LED0闪烁 */
            t = 0;
        }

        delay_ms(10);
    }
}

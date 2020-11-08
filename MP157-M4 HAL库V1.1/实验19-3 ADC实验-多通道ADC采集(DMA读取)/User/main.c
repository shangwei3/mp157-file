/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        多通道ADC采集(DMA读取) 实验
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

#define ADC_DMA_BUF_SIZE        50 * 6      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint16_t i,j;
    uint16_t adcx;
    uint32_t sum;
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
	adc_nch_dma_init((uint32_t)&ADC1->DR, (uint32_t)&g_adc_dma_buf);    /* 初始化ADC DMA采集 */ 
	adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA采集 */
   
	while (1)
    {	
		if (g_adc_dma_sta == 1)
        {
            /* 循环显示通道14~通道19的结果 */
            for(j = 0; j < 6; j++)  /* 遍历6个通道 */
            {
                sum = 0; /* 清零 */
                for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++)  /* 每个通道采集了10次数据,进行10次累加 */
                {
                    sum += g_adc_dma_buf[(6 * i) + j];  /* 相同通道的转换数据累加 */
                }
                adcx = sum / (ADC_DMA_BUF_SIZE / 6);    /* 取平均值 */
                temp = (float)adcx * (3.3 / 65536); /* 获取计算后的带小数的实际电压值，比如3.1111 */
				printf("Ch %d : ADC Value = %d, Voltage = %.3fV\r\n", 14 + j, adcx, temp);
            }
 
            g_adc_dma_sta = 0;  /* 清除DMA采集完成状态标志 */
            adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动下一次ADC DMA采集 */
        }
		LED0_TOGGLE();
        delay_ms(100);
    }
}

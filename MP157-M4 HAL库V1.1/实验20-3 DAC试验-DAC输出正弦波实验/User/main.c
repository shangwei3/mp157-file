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
#include "math.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/DAC/dac.h"

uint16_t g_dac_sin_buf[4096];    /* 发送数据缓冲区 */

/**
 * @brief       产生正弦波函序列
 *   @note      需保证: maxval > samples/2
 *
 * @param       maxval : 最大值(0 < maxval < 2048)
 * @param       samples: 采样点的个数
 *
 * @retval      无
 */
void dac_creat_sin_buf(uint16_t maxval, uint16_t samples)
{
    uint8_t i;
    float inc = (2 * 3.1415962) / samples;      /* 计算增量（一个周期DAC_SIN_BUF个点）*/
    float outdata = 0;

    for (i = 0; i < samples; i++)
    {
        outdata = maxval * (1 + sin(inc * i));  /* 计算以dots个点为周期的每个点的值，放大maxval倍，并偏移到正数区域 */
        if (outdata > 4095) outdata = 4095;     /* 上限限定 */ 
        //printf("%f\r\n",outdata);
        g_dac_sin_buf[i] = outdata;
    }
}


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
	usart_init(115200); 		/* 串口初始化为115200 			*/
	delay_init(209);        	/* 延时初始化 					*/
	led_init();					/* 初始化LED  					*/
	key_init();            		/* 初始化按键 					*/
    adc_init();             	/* 初始化ADC 					*/
    dac_dma_wave_init();      	/* 初始化DAC通道1 DMA波形输出 	*/
    dac_creat_sin_buf(2048, 100);
    HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 100, DAC_ALIGN_12B_R);

    while (1)
    {	
        t++;
        key = key_scan(0);  /* 按键扫描 */

        if (key == KEY0_PRES)                                   /* 高采样率 , 约1Khz波形 */
        {
            dac_creat_sin_buf(2048, 100);                       /* 产生正弦波函序列 */
            HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* 先停止之前的传输 */

            /* 500Khz触发频率, 100个点, 得到最高5KHz的正弦波. */
            HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 100, DAC_ALIGN_12B_R);
        }
        else if (key == KEY1_PRES)                              /* 低采样率 , 约1Khz波形 */
        {
            dac_creat_sin_buf(2048, 10);                        /* 产生正弦波函序列 */
            HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* 先停止之前的传输 */

            /* 500Khz触发频率, 10个点, 可以得到最高50KHz的正弦波. */
            HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 10, DAC_ALIGN_12B_R);
        }
		
        if (t == 10 )       /* 定时时间到了 */
        { 
            LED0_TOGGLE();  /* LED0闪烁 */
            t = 0;
        }

        delay_ms(10);
    }
}

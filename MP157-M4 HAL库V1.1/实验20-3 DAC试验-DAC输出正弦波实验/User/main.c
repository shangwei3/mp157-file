/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-16
 * @brie        DAC��� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32MP1������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
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

uint16_t g_dac_sin_buf[4096];    /* �������ݻ����� */

/**
 * @brief       �������Ҳ�������
 *   @note      �豣֤: maxval > samples/2
 *
 * @param       maxval : ���ֵ(0 < maxval < 2048)
 * @param       samples: ������ĸ���
 *
 * @retval      ��
 */
void dac_creat_sin_buf(uint16_t maxval, uint16_t samples)
{
    uint8_t i;
    float inc = (2 * 3.1415962) / samples;      /* ����������һ������DAC_SIN_BUF���㣩*/
    float outdata = 0;

    for (i = 0; i < samples; i++)
    {
        outdata = maxval * (1 + sin(inc * i));  /* ������dots����Ϊ���ڵ�ÿ�����ֵ���Ŵ�maxval������ƫ�Ƶ��������� */
        if (outdata > 4095) outdata = 4095;     /* �����޶� */ 
        //printf("%f\r\n",outdata);
        g_dac_sin_buf[i] = outdata;
    }
}


/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint8_t t = 0;
    uint8_t key;
	
	HAL_Init();				/* ��ʼ��HAL�� 			*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* ���ڳ�ʼ��Ϊ115200 			*/
	delay_init(209);        	/* ��ʱ��ʼ�� 					*/
	led_init();					/* ��ʼ��LED  					*/
	key_init();            		/* ��ʼ������ 					*/
    adc_init();             	/* ��ʼ��ADC 					*/
    dac_dma_wave_init();      	/* ��ʼ��DACͨ��1 DMA������� 	*/
    dac_creat_sin_buf(2048, 100);
    HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 100, DAC_ALIGN_12B_R);

    while (1)
    {	
        t++;
        key = key_scan(0);  /* ����ɨ�� */

        if (key == KEY0_PRES)                                   /* �߲����� , Լ1Khz���� */
        {
            dac_creat_sin_buf(2048, 100);                       /* �������Ҳ������� */
            HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* ��ֹ֮ͣǰ�Ĵ��� */

            /* 500Khz����Ƶ��, 100����, �õ����5KHz�����Ҳ�. */
            HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 100, DAC_ALIGN_12B_R);
        }
        else if (key == KEY1_PRES)                              /* �Ͳ����� , Լ1Khz���� */
        {
            dac_creat_sin_buf(2048, 10);                        /* �������Ҳ������� */
            HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* ��ֹ֮ͣǰ�Ĵ��� */

            /* 500Khz����Ƶ��, 10����, ���Եõ����50KHz�����Ҳ�. */
            HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, 10, DAC_ALIGN_12B_R);
        }
		
        if (t == 10 )       /* ��ʱʱ�䵽�� */
        { 
            LED0_TOGGLE();  /* LED0��˸ */
            t = 0;
        }

        delay_ms(10);
    }
}

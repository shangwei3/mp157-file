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
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint16_t adcx, dacx;
    float adc_temp, dac_temp;
    uint8_t t = 0;
    uint16_t dacval = 0;
    uint8_t key;
	
	HAL_Init();				/* ��ʼ��HAL�� 			*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* ���ڳ�ʼ��Ϊ115200 	*/
	delay_init(209);        	/* ��ʱ��ʼ�� 			*/
	led_init();					/* ��ʼ��LED  			*/
	key_init();            		/* ��ʼ������ 			*/
    adc_init();             	/* ��ʼ��ADC */
    dac_init(DAC_CHANNEL_1);  	/* ��ʼ��DAC1_OUT1ͨ�� 	*/
	
	HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);/* ��ʼֵΪ0 */

    while (1)
    {	
        t++;
        key = key_scan(0);          /* ����ɨ�� */

        if (key == KEY0_PRES)
        {
            if (dacval < 4000)dacval += 200;

            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacval);/* �������200 */
        }
        else if (key == KEY1_PRES)
        {
            if (dacval > 200)dacval -= 200;
            else dacval = 0;

            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacval);/* �������200 */
        }

        if (t == 10 || key == KEY1_PRES || key == KEY0_PRES)    /* WKUP/KEY1������,���߶�ʱʱ�䵽�� */
        {
			printf("\r\n");
            dacx = HAL_DAC_GetValue(&g_dac_handle, DAC_CHANNEL_1);/* ��ȡǰ������DAC1_OUT1��ֵ */
			dac_temp = (float)dacx * (3.3f / 4096);                  /* �õ�DAC��ѹֵ */
			printf("DAC Output Value = %d, DAC Output Voltage = %.2f\r\n", dacx, dac_temp);
			
            adcx=adc_get_result_average(ADC_ADCX_CHY, 10);      /* �õ�ADCͨ��19��ת����� */
            adc_temp = (float)adcx * (3.3 / 65536);          	/* �õ�ADC��ѹֵ(adc��16bit��) */
			printf("ADC Input Value  = %d, ADC Input Voltage  = %.2f\r\n", adcx, adc_temp);
            
            LED0_TOGGLE();  /* LED0��˸ */
            t = 0;
        }

        delay_ms(10);
    }
}

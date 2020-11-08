/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        ��ͨ��ADC������(26λ�ֱ���) ʵ��
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

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint32_t adcx;
    float temp;
	
	HAL_Init();				/* ��ʼ��HAL�� 			*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 	*/
	delay_init(209);        /* ��ʱ��ʼ�� 			*/
	led_init();				/* ��ʼ��LED  			*/
	key_init();            	/* ��ʼ������ 			*/

    /* ��ʼ��ADC, 1024x������, ����λ 
     * 26λADC�ֱ������ֵΪ:67108864, ʵ�������ڷֱ���̫�� ,��λֵ�Ѿ���׼ȷ
     * һ�����ǿ������� ovss=4, ��С16��, ��22λ�ֱ���, ��λֵ������ȶ�һЩ.
     * ��������Ϊ����ʾ26λ������ADCת��Ч��, �ѷֱ��ʵ������, 24λ,���Ҳ���λ. 
     */
    adc_oversample_init(1024 - 1, ADC_RIGHTBITSHIFT_NONE);
   
	while (1)
    {	
		adcx = adc_get_result_average(ADC_ADCX_CHY, 10);/* ��ȡת��ֵ��10��ȡƽ�� */
		temp = (float)adcx * (3.3 / 67108864); 	/* ת����ѹֵ */
		printf("ADC Value = %d, Voltage = %.3fV\r\n", adcx, temp);
		
		LED0_TOGGLE();
        delay_ms(100);
    }
}

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
    uint8_t t = 0; 
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
    adc_init();             	/* ��ʼ��ADC 			*/
	dac_init(DAC_CHANNEL_1);  	/* ��ʼ��DAC1_OUT1ͨ�� 	*/
	
    while (1)
    {	
        t++;
        key = key_scan(0);  /* ����ɨ�� */

        if (key == KEY0_PRES)       /* �߲����� , Լ100hz���� */
        {
            dac_triangular_wave(4095, 5, 2000, 100);    /* ��ֵ4095, ��������5us, 2000��������, 100������ */
       }
        else if (key == KEY1_PRES)  /* �Ͳ����� , Լ100hz���� */
        {
            dac_triangular_wave(4095, 500, 20, 100);    /* ��ֵ4095, ��������500us, 20��������, 100������ */ 
        }

        if (t == 10 )       /* ��ʱʱ�䵽�� */
        { 
            LED0_TOGGLE();  /* LED0��˸ */
            t = 0;
        }

        delay_ms(10);
    }
}

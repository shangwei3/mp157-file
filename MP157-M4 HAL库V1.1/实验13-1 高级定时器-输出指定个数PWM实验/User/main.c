/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brie      	ͨ�ö�ʱ��������� ʵ��
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
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/atim.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
  uint8_t key = 0;
	
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
    gtim_timx_npwm_chy_init(5000 - 1, 20900 - 1);   /* 10Khz�ļ���Ƶ��,2hz��PWMƵ��. */
    GTIM_TIMX_NPWM_CHY_CCRX = 2500; /* ����PWMռ�ձ�,50%,�������Կ���ÿһ��PWM����,LED1
                                     * ��һ��ʱ��������,һ��ʱ�������,LED1����һ��,��ʾһ��PWM��
                                     */
    gtim_timx_npwm_chy_set(5);      /* ���5��PWM��(����LED1��˸5��) */
	
	while(1) 
	{
        key = key_scan(0);

        if (key == KEY0_PRES)   /* KEY0���� */
        {
            gtim_timx_npwm_chy_set(5);  /* ���5��PWM��(����LED2(BLUE)��˸5��) */
        }

        delay_ms(10);
	}
}

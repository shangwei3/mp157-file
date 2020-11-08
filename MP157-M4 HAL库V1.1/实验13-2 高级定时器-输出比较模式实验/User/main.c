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

extern TIM_HandleTypeDef g_timx_comp_pwm_handle;

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	uint8_t t = 0;
	
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
    atim_timx_comp_pwm_init(1000, 209);  /* 1Mhz�ļ���Ƶ�� 1Khz������. */
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle,TIM_CHANNEL_3);
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle,TIM_CHANNEL_4);
	
	while(1) 
	{
        delay_ms(10);
        t++;

        if (t >= 20)
        {
            LED0_TOGGLE();  /* LED0(RED)��˸ */
            t = 0;
        }
	}
}

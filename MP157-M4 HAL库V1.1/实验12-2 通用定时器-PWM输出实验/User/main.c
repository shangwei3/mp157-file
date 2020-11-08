/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       ͨ�ö�ʱ��PWM��� ʵ��
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
#include "./BSP/TIMER/gtim.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
	
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 	*/
	delay_init(209);        /* ��ʱ��ʼ�� 			*/
	led_init();				/* ��ʼ��LED  			*/
	beep_init();			/* ��ʼ�������� 		*/
	gtim_timx_pwm_chy_init(500 - 1, 209 - 1); /* 209M/209=1M�ļ���Ƶ�ʣ��Զ���װ��Ϊ500����ôPWMƵ��Ϊ1M/500=2kHZ */
	
	while(1) 
	{
        delay_ms(10);

        if (dir)ledrpwmval++;               /* dir==1 ledrpwmval���� */
        else ledrpwmval--;                  /* dir==0 ledrpwmval�ݼ� */

        if (ledrpwmval > 300)dir = 0;       /* ledrpwmval����300�󣬷���Ϊ�ݼ� */
        if (ledrpwmval == 0)dir = 1;        /* ledrpwmval�ݼ���0�󣬷����Ϊ���� */

        GTIM_TIMX_PWM_CHY_CCRX = ledrpwmval;/* �޸ıȽ�ֵ���޸�ռ�ձ� */
	}
}

/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       ���ڿ��Ź� ʵ��
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
#include "./BSP/WWDG/wwdg.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 */
	delay_init(209);        /* ��ʱ��ʼ�� */
	led_init();				/* ��ʼ��LED  	*/
	beep_init();			/* ��ʼ�������� */
	LED0(0);               	/* ����LED0(���) */
    delay_ms(300);        	/* ��ʱ100ms�ٳ�ʼ�����Ź�,LED0�ı仯"�ɼ�" */
	wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_16); /* ������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ16 */
	
	while(1) 
	{
		LED0(1);                        /* �رպ�� */
	}
}

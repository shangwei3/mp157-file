/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brie      	ͨ�ö�ʱ�����벶�� ʵ��
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

extern uint8_t  g_timxchy_cap_sta;  /* ���벶��״̬ */
extern uint16_t g_timxchy_cap_val;  /* ���벶��ֵ */

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	unsigned int i = 0;
	long long temp = 0;
	
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 	*/
	delay_init(209);        /* ��ʱ��ʼ�� 			*/
	led_init();				/* ��ʼ��LED  			*/
	key_init();            	/* ��ʼ������ 			*/
	gtim_timx_cap_chy_init(0XFFFF, 209 - 1);  	/* ��1Mhz��Ƶ�ʼ��� ���� */

	while(1) 
	{
        delay_ms(10);
		
        if (g_timxchy_cap_sta & 0X80)             /* �ɹ�������һ�θߵ�ƽ */
        {
            temp = g_timxchy_cap_sta&0X3F; 
            temp *= 65536;                        /* ���ʱ���ܺ� */
            temp += g_timxchy_cap_val;            /* �õ��ܵĸߵ�ƽʱ�� */
            printf("HIGH:%lld us\r\n",temp);      /* ��ӡ�ܵĸߵ�ƽʱ�� */
            g_timxchy_cap_sta = 0;                /* ������һ�β��� */
        }
		i++;
		if(i == 50) 
		{
			i = 0;
			LED0_TOGGLE();
		}
	}
}

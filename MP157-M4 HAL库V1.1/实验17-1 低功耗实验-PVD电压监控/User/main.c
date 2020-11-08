/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        PVD��ѹ��� ʵ��
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
#include "./USMART/usmart.h"
#include "./BSP/RNG/rng.h"
#include "./BSP/PWR/pwr.h"


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
	usmart_dev.init(209);   /* ��ʼ��USMART 		*/
	led_init();				/* ��ʼ��LED  			*/
	key_init();            	/* ��ʼ������ 			*/
	pwr_pvd_init(PWR_PVDLEVEL_5);       /* PVD 2.7V��� */
	/* Ĭ�������ѹ���� */
	printf("PVD Voltage OK! \r\n");
	
    while (1)
    {
        if ((t % 20) == 0)
        {
            LED0_TOGGLE();  /* ÿ200ms,��תһ��LED0 */
        }

        delay_ms(10);
        t++;
    }
}

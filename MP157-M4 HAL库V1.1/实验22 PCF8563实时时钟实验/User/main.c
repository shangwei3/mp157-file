/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brie        APC3216C���պͽӽ�������ʵ��
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
#include "./BSP/PCF8563/pcf8563.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	pcf8563_date date;
	
	HAL_Init();				/* ��ʼ��HAL�� 			*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* ���ڳ�ʼ��Ϊ115200 	*/
	delay_init(209);        	/* ��ʱ��ʼ�� 			*/
	usmart_dev.init(209);		/* ��ʼ��USMART 		*/
	led_init();					/* ��ʼ��LED  			*/
	key_init();            		/* ��ʼ������ 			*/
	pcf8563_init();				/* ��ʼ��PCF8563 		*/		
	
    while(1)
    {
        pcf8563_get_date(&date);
		printf("%d/%d/%d,%d:%d:%d,week=%d\r\n", date.year, date.month, date.day, \
									date.hour, date.min, date.sec, date.week+1);
		LED0_TOGGLE();/* DS0��˸ 						*/
        delay_ms(1000); 
	}	
}

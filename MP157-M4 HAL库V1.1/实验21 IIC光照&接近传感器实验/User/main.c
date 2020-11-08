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
#include "./BSP/ADC/adc.h"
#include "./BSP/AP3216C/ap3216c.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	uint16_t ir,als,ps; 
	
	HAL_Init();				/* ��ʼ��HAL�� 			*/
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 		/* ���ڳ�ʼ��Ϊ115200 			*/
	delay_init(209);        	/* ��ʱ��ʼ�� 					*/
	led_init();					/* ��ʼ��LED  					*/
	key_init();            		/* ��ʼ������ 					*/
    adc_init();             	/* ��ʼ��ADC 					*/

	while(ap3216c_init())		/* ��ⲻ��AP3216C 				*/
	{
		printf("AP3216C Check Failed!\r\n");
		delay_ms(500);
		LED0_TOGGLE();/* DS0��˸ 						*/
	}			
	
    while(1)
    {
        ap3216c_read_data(&ir,&ps,&als);	//��ȡ���� 
		printf("ir = %d, ps = %d, als = %d\r\n", ir, ps, als);
		LED0_TOGGLE();/* DS0��˸ 						*/
        delay_ms(120); 
	}	
}

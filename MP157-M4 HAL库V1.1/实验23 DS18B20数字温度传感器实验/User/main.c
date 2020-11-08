/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brie        DS18B20�����¶ȴ����� ʵ��
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
#include "./BSP/DS18B20/ds18b20.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint8_t t = 0;
    short temperature;
	
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
	
    while (ds18b20_init())    	/* DS18B20��ʼ�� 		*/
    {
		printf("DS18B20 Error!\r\n");
        delay_ms(1000);
    }	
	
    while (1)
    {
        t++;

        if (t == 20)
        {
            t = 0;
			 temperature = ds18b20_get_temperature();
			printf("DS18B20 Temp=%.1f\r\n", temperature / 10.0f);
            LED0_TOGGLE();  /* LED0��˸ */
        }
		delay_ms(10);
    }	
}

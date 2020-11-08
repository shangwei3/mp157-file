/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brie        DHT11������ʪ�ȴ����� ʵ��
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
#include "./BSP/DHT11/dht11.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint8_t t = 0;
    uint8_t temperature;
    uint8_t humidity;
	
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
	
    while (dht11_init())    	/* DHT11��ʼ�� 			*/
    {
		printf("DHT11 Error!\r\n");
        delay_ms(1000);
    }	
	
    while (1)
    {
        t++;

        if (t == 20)
        {
            t = 0;
			dht11_read_data(&temperature, &humidity);  
			printf("DHT11 Temp=%d, Humi=%d%%\r\n", temperature, humidity);
            LED0_TOGGLE();  /* LED0��˸ */
        }
		delay_ms(10);
    }	
}

/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-11
 * @brie      	OLED ʵ��
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
#include "./BSP/OLED/oled.h"


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
    oled_init();                        /* ��ʼ��OLED */
    oled_show_string(0, 0, "ALIENTEK", 24);
    oled_show_string(0, 24, "0.96' OLED TEST", 16);
    oled_show_string(0, 40, "ATOM 2020/5/11", 12);
    oled_show_string(0, 52, "ASCII:", 12);
    oled_show_string(64, 52, "CODE:", 12);
    oled_refresh_gram();    /* ������ʾ��OLED */
    
    t = ' '; 
    while (1)
    {
        oled_show_char(36, 52, t, 12, 1);/* ��ʾASCII�ַ� */
        oled_show_num(94, 52, t, 3, 12); /*��ʾASCII�ַ�����ֵ */
        oled_refresh_gram();    /*������ʾ��OLED */
        t++;

        if (t > '~')t = ' ';

        delay_ms(500);
        LED0_TOGGLE();  /* LED0��˸ */
    }
}

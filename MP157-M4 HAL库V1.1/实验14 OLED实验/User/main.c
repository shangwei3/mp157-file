/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-11
 * @brie      	OLED 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32MP1开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	uint8_t t = 0;
	
	HAL_Init();				/* 初始化HAL库 			*/
	/* 初始化M4内核时钟,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 	*/
	delay_init(209);        /* 延时初始化 			*/
	led_init();				/* 初始化LED  			*/
	key_init();            	/* 初始化按键 			*/
    oled_init();                        /* 初始化OLED */
    oled_show_string(0, 0, "ALIENTEK", 24);
    oled_show_string(0, 24, "0.96' OLED TEST", 16);
    oled_show_string(0, 40, "ATOM 2020/5/11", 12);
    oled_show_string(0, 52, "ASCII:", 12);
    oled_show_string(64, 52, "CODE:", 12);
    oled_refresh_gram();    /* 更新显示到OLED */
    
    t = ' '; 
    while (1)
    {
        oled_show_char(36, 52, t, 12, 1);/* 显示ASCII字符 */
        oled_show_num(94, 52, t, 3, 12); /*显示ASCII字符的码值 */
        oled_refresh_gram();    /*更新显示到OLED */
        t++;

        if (t > '~')t = ' ';

        delay_ms(500);
        LED0_TOGGLE();  /* LED0闪烁 */
    }
}

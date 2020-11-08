#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	uint8_t t;
    uint8_t len;
    uint16_t times = 0; 
	
	HAL_Init();		/* 初始化HAL库 	*/
	
	/* 初始化M4内核时钟 */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* 串口初始化为115200 */
	led_init();				/* 初始化LED  	*/
	beep_init();			/* 初始化蜂鸣器 */
	extix_init();			/* 初始化中断 	*/
	
	printf("\r\n正点原子 STM32MP1 开发板 串口实验\r\n");
	while(1) 
	{
        if (g_usart_rx_sta & 0x8000)        /* 接收到了数据 */
        {
            len = g_usart_rx_sta & 0x3fff;  /* 得到此次接收到的数据长度 */
            printf("\r\n您发送的消息为:\r\n");

            for (t = 0; t < len; t++)
            {
                USART_UX->TDR = g_usart_rx_buf[t];
                
                while ((USART_UX->ISR & 0X40) == 0);  /* 等待发送结束 */
            }

            printf("\r\n\r\n"); /* 插入换行 */
            g_usart_rx_sta = 0;
        }
        else
        {
            times++;

            if (times % 5000 == 0)
            {
                printf("\r\n正点原子 STM32MP1 开发板 串口实验\r\n");
                printf("正点原子@ALIENTEK\r\n\r\n\r\n");
            }

            if (times % 200 == 0) printf("请输入数据,以回车键结束\r\n");

            if (times % 30  == 0) LED0_TOGGLE(); /* 闪烁LED,提示系统正在运行. */

            delay(10);
        }
	}
}

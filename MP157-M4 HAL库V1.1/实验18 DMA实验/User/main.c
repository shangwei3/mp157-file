/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        待机模式 实验
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
#include "./USMART/usmart.h"
#include "./BSP/DMA/dma.h"

const uint8_t TEXT_TO_SEND[] = {"正点原子 STM32MP1 DMA 串口实验"};   /* 要循环发送的字符串 */

#define SEND_BUF_SIZE       (sizeof(TEXT_TO_SEND) + 2) * 200   /* 发送数据长度, 等于sizeof(TEXT_TO_SEND) + 2的200倍. */

uint8_t g_sendbuf[SEND_BUF_SIZE];       /* 发送数据缓冲区 */


/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
    uint8_t  key = 0;
    uint16_t i, k;
    uint16_t len;
    uint8_t  mask = 0;
	
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
	dma_init(DMA2_Stream7, DMA_REQUEST_UART4_TX);  /* 初始化DMA */
	
	len = sizeof(TEXT_TO_SEND);
    k = 0;
    
    for (i = 0; i < SEND_BUF_SIZE; i++) /* 填充ASCII字符集数据 */
    {
        if (k >= len)   /* 入换行符 */
        {
            if (mask)
            {
                g_sendbuf[i] = 0x0a;
                k = 0;
            }
            else
            {
                g_sendbuf[i] = 0x0d;
                mask++;
            }
        }
        else     /* 复制TEXT_TO_SEND语句 */
        {
            mask = 0;
            g_sendbuf[i] = TEXT_TO_SEND[k];
            k++;
        }
    }
 
    i = 0;
	
    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)	/* 进入睡眠模式 */
        {
            printf("\r\nDMA DATA:\r\n");
            HAL_UART_Transmit_DMA(&g_uart4_handle,g_sendbuf,SEND_BUF_SIZE); /* 开始一次DMA传输！ */

            /* 等待DMA传输完成，此时我们来做另外一些事情，比如点灯  
             * 实际应用中，传输数据期间，可以执行另外的任务 
             */
            while (1)
            {
                if (__HAL_DMA_GET_FLAG(&g_dma_handle, DMA_FLAG_TCIF3_7)) /* 等待DMA1_Steam7传输完成 */
                {
                    __HAL_DMA_CLEAR_FLAG(&g_dma_handle, DMA_FLAG_TCIF3_7); /* 清除DMA1_Steam7传输完成标志 */
                    HAL_UART_DMAStop(&g_uart4_handle);      /* 传输完成以后关闭串口DMA */
                    break;
                }
            } 
			printf("\r\nTransimit Finished!\r\n");/* 提示传送完成 */
        }
        i++;
        delay_ms(10);

        if (i == 20)
        {
            LED0_TOGGLE();  /* LED0闪烁,提示系统正在运行 */
            i = 0;
        }
    }
}

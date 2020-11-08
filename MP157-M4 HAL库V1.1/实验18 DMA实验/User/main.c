/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brie        ����ģʽ ʵ��
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
#include "./BSP/DMA/dma.h"

const uint8_t TEXT_TO_SEND[] = {"����ԭ�� STM32MP1 DMA ����ʵ��"};   /* Ҫѭ�����͵��ַ��� */

#define SEND_BUF_SIZE       (sizeof(TEXT_TO_SEND) + 2) * 200   /* �������ݳ���, ����sizeof(TEXT_TO_SEND) + 2��200��. */

uint8_t g_sendbuf[SEND_BUF_SIZE];       /* �������ݻ����� */


/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
    uint8_t  key = 0;
    uint16_t i, k;
    uint16_t len;
    uint8_t  mask = 0;
	
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
	dma_init(DMA2_Stream7, DMA_REQUEST_UART4_TX);  /* ��ʼ��DMA */
	
	len = sizeof(TEXT_TO_SEND);
    k = 0;
    
    for (i = 0; i < SEND_BUF_SIZE; i++) /* ���ASCII�ַ������� */
    {
        if (k >= len)   /* �뻻�з� */
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
        else     /* ����TEXT_TO_SEND��� */
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

        if (key == KEY0_PRES)	/* ����˯��ģʽ */
        {
            printf("\r\nDMA DATA:\r\n");
            HAL_UART_Transmit_DMA(&g_uart4_handle,g_sendbuf,SEND_BUF_SIZE); /* ��ʼһ��DMA���䣡 */

            /* �ȴ�DMA������ɣ���ʱ������������һЩ���飬������  
             * ʵ��Ӧ���У����������ڼ䣬����ִ����������� 
             */
            while (1)
            {
                if (__HAL_DMA_GET_FLAG(&g_dma_handle, DMA_FLAG_TCIF3_7)) /* �ȴ�DMA1_Steam7������� */
                {
                    __HAL_DMA_CLEAR_FLAG(&g_dma_handle, DMA_FLAG_TCIF3_7); /* ���DMA1_Steam7������ɱ�־ */
                    HAL_UART_DMAStop(&g_uart4_handle);      /* ��������Ժ�رմ���DMA */
                    break;
                }
            } 
			printf("\r\nTransimit Finished!\r\n");/* ��ʾ������� */
        }
        i++;
        delay_ms(10);

        if (i == 20)
        {
            LED0_TOGGLE();  /* LED0��˸,��ʾϵͳ�������� */
            i = 0;
        }
    }
}

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/usart/usart.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	uint8_t t;
    uint8_t len;
    uint16_t times = 0; 
	
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	
	/* ��ʼ��M4�ں�ʱ�� */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 */
	led_init();				/* ��ʼ��LED  	*/
	beep_init();			/* ��ʼ�������� */
	extix_init();			/* ��ʼ���ж� 	*/
	
	printf("\r\n����ԭ�� STM32MP1 ������ ����ʵ��\r\n");
	while(1) 
	{
        if (g_usart_rx_sta & 0x8000)        /* ���յ������� */
        {
            len = g_usart_rx_sta & 0x3fff;  /* �õ��˴ν��յ������ݳ��� */
            printf("\r\n�����͵���ϢΪ:\r\n");

            for (t = 0; t < len; t++)
            {
                USART_UX->TDR = g_usart_rx_buf[t];
                
                while ((USART_UX->ISR & 0X40) == 0);  /* �ȴ����ͽ��� */
            }

            printf("\r\n\r\n"); /* ���뻻�� */
            g_usart_rx_sta = 0;
        }
        else
        {
            times++;

            if (times % 5000 == 0)
            {
                printf("\r\n����ԭ�� STM32MP1 ������ ����ʵ��\r\n");
                printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
            }

            if (times % 200 == 0) printf("����������,�Իس�������\r\n");

            if (times % 30  == 0) LED0_TOGGLE(); /* ��˸LED,��ʾϵͳ��������. */

            delay(10);
        }
	}
}

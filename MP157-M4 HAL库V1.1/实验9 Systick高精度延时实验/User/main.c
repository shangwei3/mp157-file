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
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	
	/* ��ʼ��M4�ں�ʱ��,209M */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}
	usart_init(115200); 	/* ���ڳ�ʼ��Ϊ115200 */
	delay_init(209);        /* ��ʱ��ʼ�� */
	led_init();				/* ��ʼ��LED  	*/
	beep_init();			/* ��ʼ�������� */
	extix_init();			/* ��ʼ���ж� 	*/

	while(1) 
	{
		LED0_TOGGLE();
		delay_ms(500);
	}
}

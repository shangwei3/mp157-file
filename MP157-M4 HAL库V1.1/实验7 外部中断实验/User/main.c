#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	
	/* ��ʼ��M4�ں�ʱ�� */
	if(IS_ENGINEERING_BOOT_MODE())
	{
		sys_stm32_clock_init(34, 2, 2, 17, 6826);
	}

	led_init();		/* ��ʼ��LED  	*/
	beep_init();	/* ��ʼ�������� */
	extix_init();	/* ��ʼ���ж� 	*/
	
	while(1) 
	{
		delay(100);
	}
}

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	led_init();		/* ��ʼ��LED  	*/
	beep_init();	/* ��ʼ�������� */

	while(1) 
	{
		LED0(0);	/* ��LED0 	*/
		BEEP(0);	/* �򿪷����� 	*/
		delay(100);
		LED0(1);	/* �ر�LED0 	*/
		BEEP(1);	/* �رշ����� 	*/
		delay(100);
	}
}

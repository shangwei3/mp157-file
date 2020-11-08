#include "./SYSTEM/sys/sys.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	HAL_Init();	/* ��ʼ��HAL�� */
	led_init();	/* ��ʼ��LED  */

	while(1) 
	{
		LED0(0);	/* ��LED0 */
		LED1(1);	/* �ر�LED1 */
		delay(100);
		LED0(1);	/* �ر�LED0 */
		LED1(0);	/* ��LED1 */
		delay(100);
	}
}

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"

/**
 * @brief       ������
 * @param       ��
 * @retval      ��
 */
int main(void)
{
	uint8_t key;
	
	HAL_Init();		/* ��ʼ��HAL�� 	*/
	led_init();		/* ��ʼ��LED  	*/
	beep_init();	/* ��ʼ�������� */
	key_init();		/* ��ʼ������ 	*/
	LED0(0);       	/* �ȵ���LED0 	*/

	while(1) 
	{
		key = key_scan(0);	 /* �õ���ֵ */
        if (key)
        {
            switch (key)
            {
                case WKUP_PRES:         /* ����LED0(RED)��ת */
                    LED0_TOGGLE();      /* LED0״̬ȡ�� */
                    break;

                case KEY1_PRES:         /* ����LED1(GREEN)��ת */
                    LED1_TOGGLE();      /* LED1״̬ȡ�� */
                    break;

                case KEY0_PRES:         /* ���Ʒ��������� */
                    BEEP_TOGGLE();      /* ������״̬ȡ�� */
                    break;
            } 
        }
        else
        {
            delay(10);
        }
	}
}

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"

/**
 * @brief       主函数
 * @param       无
 * @retval      无
 */
int main(void)
{
	uint8_t key;
	
	HAL_Init();		/* 初始化HAL库 	*/
	led_init();		/* 初始化LED  	*/
	beep_init();	/* 初始化蜂鸣器 */
	key_init();		/* 初始化按键 	*/
	LED0(0);       	/* 先点亮LED0 	*/

	while(1) 
	{
		key = key_scan(0);	 /* 得到键值 */
        if (key)
        {
            switch (key)
            {
                case WKUP_PRES:         /* 控制LED0(RED)翻转 */
                    LED0_TOGGLE();      /* LED0状态取反 */
                    break;

                case KEY1_PRES:         /* 控制LED1(GREEN)翻转 */
                    LED1_TOGGLE();      /* LED1状态取反 */
                    break;

                case KEY0_PRES:         /* 控制蜂鸣器开关 */
                    BEEP_TOGGLE();      /* 蜂鸣器状态取反 */
                    break;
            } 
        }
        else
        {
            delay(10);
        }
	}
}

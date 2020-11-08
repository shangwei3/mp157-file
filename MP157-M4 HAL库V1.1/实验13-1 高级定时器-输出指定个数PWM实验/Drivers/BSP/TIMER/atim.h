/**
 ****************************************************************************************************
 * @file        atim.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       �߼���ʱ�� ��������
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
 * �޸�˵��
 * V1.0 20200506
 * ��һ�η��� 
 *
 ****************************************************************************************************
 */

#ifndef __ATIM_H
#define __ATIM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* �߼���ʱ�� ���� */

/* TIMX ���ָ������PWM ���� 
 * ���������PWM����BEEP�Ŀ���,����һ�α�ʾһ�����ڵ�PWM����
 * Ĭ�������TIM1��TIM8 
 * ע��: ͨ���޸���8���궨��,����֧��TIM1��TIM8������һ��IO�����PWM
 */
#define GTIM_TIMX_NPWM_CHY_GPIO_PORT            GPIOC
#define GTIM_TIMX_NPWM_CHY_GPIO_PIN             GPIO_PIN_7
#define GTIM_TIMX_NPWM_CHY_GPIO_AF              GPIO_AF3_TIM8                              	/* AF����ѡ�� */
#define GTIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)	/* PC��ʱ��ʹ�� */

#define GTIM_TIMX_NPWM                          TIM8                       
#define GTIM_TIMX_NPWM_IRQn                     TIM8_UP_IRQn
#define GTIM_TIMX_NPWM_IRQHandler               TIM8_UP_IRQHandler
#define GTIM_TIMX_NPWM_CHY                      TIM_CHANNEL_2     /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_NPWM_CHY_CCRX                 TIM8->CCR2       /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_NPWM_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)  /* TIMX ʱ��ʹ�� */

/******************************************************************************************/

void gtim_timx_npwm_chy_init(uint16_t arr, uint16_t psc); /* ͨ�ö�ʱ�� ���ָ������PWM��ʼ������ */
void gtim_timx_npwm_chy_gpio_init(void);                  /* ͨ�ö�ʱ�� ���ָ������PWM GPIO��ʼ������ */
void gtim_timx_npwm_chy_set(uint32_t npwm);               /* ͨ�ö�ʱ�� �������PWM�ĸ��� */

#endif


















/**
 ****************************************************************************************************
 * @file        gtim.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       ͨ�ö�ʱ�� ��������
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

#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ͨ�ö�ʱ�� ���� */

/* TIMX �ж϶��� 
 * Ĭ�������TIM2~TIM5, TIM12~TIM17.TIM2��TIM5Ϊ32λ��������ͨ��
 * ��ʱ��Ϊ16λ��
 * ע��: ͨ���޸���4���궨��,����֧��TIM2~TIM5��TIM12~TIM17����һ����ʱ��.
 */
 
#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)  /* TIM3 ʱ��ʹ�� */

/* TIMX PWM������� 
 * ���������PWM����LED0(RED)������
 * Ĭ�������TIM2~TIM5, TIM12~TIM17.
 * ע��: ͨ���޸���8���궨��,����֧��TIM1~TIM17����һ����ʱ��,����һ��IO�����PWM
 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOI
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIMX_PWM_CHY_GPIO_AF           GPIO_AF2_TIM5                                   /* AF����ѡ�� */
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)     /* PI��ʱ��ʹ�� */

#define GTIM_TIMX_PWM                       TIM5 
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_4      /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM5->CCR4         /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)      /* TIM3 ʱ��ʹ�� */

/******************************************************************************************/

void gtim_timx_int_init(uint16_t arr, uint16_t psc);      /* ͨ�ö�ʱ�� ��ʱ�жϳ�ʼ������ */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);  /* ͨ�ö�ʱ�� PWM��ʼ������ */
void gtim_timx_comp_pwm_gpio_init(void);                  /* ͨ�ö�ʱ�� PWM-GPIO��ʼ������ */

#endif


















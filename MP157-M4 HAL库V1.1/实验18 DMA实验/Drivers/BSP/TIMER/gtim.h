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


/* TIMX ���벶���� 
 * ��������벶��ʹ�ö�ʱ��TIM5_CH1,����WK_UP����������
 * Ĭ�������TIM2~TIM5, TIM12~TIM17. 
 * ע��: ͨ���޸���8���궨��,����֧��TIM1~TIM17����һ����ʱ��,����һ��IO�������벶��
 *       �ر�Ҫע��:Ĭ���õ�PA0,���õ�����������!���������IO,��Ӧ����������ʽ/AF���ܵ�Ҳ�ø�!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT            GPIOA
#define GTIM_TIMX_CAP_CHY_GPIO_PIN             GPIO_PIN_0
#define GTIM_TIMX_CAP_CHY_GPIO_AF              GPIO_AF2_TIM5                                 /* AF����ѡ�� */
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define GTIM_TIMX_CAP                          TIM5                       
#define GTIM_TIMX_CAP_IRQn                     TIM5_IRQn
#define GTIM_TIMX_CAP_IRQHandler               TIM5_IRQHandler
#define GTIM_TIMX_CAP_CHY                      TIM_CHANNEL_1     /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX                 TIM5->CCR1        /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)    /* TIMX ʱ��ʹ�� */

/* TIMX �����������
* ������������ʹ�ö�ʱ��TIM2_CH1,����WK_UP����������
* Ĭ�������TIM2~TIM5, TIM12~TIM17.  ֻ��CH1��CH2ͨ�����������������, CH3/CH4��֧��!
* ע��: ͨ���޸���9���궨��,����֧��TIM1~TIM17����һ����ʱ��,CH1/CH2��ӦIO�����������
*       �ر�Ҫע��:Ĭ���õ�PA0,���õ�����������!���������IO,��Ӧ����������ʽ/AF���ܵ�Ҳ�ø�!
*/
#define GTIM_TIMX_CNT_CHY_GPIO_PORT            GPIOA
#define GTIM_TIMX_CNT_CHY_GPIO_PIN             GPIO_PIN_0
#define GTIM_TIMX_CNT_CHY_GPIO_AF              GPIO_AF1_TIM2                               /* AF����ѡ�� */
#define GTIM_TIMX_CNT_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PA��ʱ��ʹ�� */

#define GTIM_TIMX_CNT                          TIM2
#define GTIM_TIMX_CNT_IRQn                     TIM2_IRQn
#define GTIM_TIMX_CNT_IRQHandler               TIM2_IRQHandler
#define GTIM_TIMX_CNT_CHY                      TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=2 */
#define GTIM_TIMX_CNT_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)  /* TIMX ʱ��ʹ�� */

/******************************************************************************************/

void gtim_timx_int_init(uint16_t arr, uint16_t psc);      /* ͨ�ö�ʱ�� ��ʱ�жϳ�ʼ������ */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);  /* ͨ�ö�ʱ�� PWM��ʼ������ */
void gtim_timx_comp_pwm_gpio_init(void);                  /* ͨ�ö�ʱ�� PWM-GPIO��ʼ������ */

void set_timx_comparey(uint32_t compare);                 /* ����TIMͨ����ռ�ձȺ��� */
uint32_t get_timx_capture(void);                          /* ��ȡtimx����/�ȽϼĴ���ֵ */
void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc);  /* ͨ�ö�ʱ�� ���벶���ʼ������ */
void gtim_timx_cap_chy_gpio_init(void);   

void gtim_timx_cnt_chy_init(uint16_t psc);                /* ͨ�ö�ʱ�� ���������ʼ������ */
void gtim_timx_cnt_chy_gpio_init(void);                   /* ͨ�ö�ʱ�� �������GPIO��ʼ������ */
uint32_t gtim_timx_cnt_chy_get_count(void);               /* ͨ�ö�ʱ�� ��ȡ������� */
void gtim_timx_cnt_chy_restart(void);                     /* ͨ�ö�ʱ�� ���������� */

#endif


















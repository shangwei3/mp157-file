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

/* TIMX ����Ƚ�ģʽ ���� 
 * ����ͨ��TIM1������Ƚ�ģʽ,����PE13,PE14���2·PWM,ռ�ձ�50%,����ÿһ·PWM֮�����λ��Ϊ25%
 * �޸�CCRx�����޸���λ.
 * Ĭ�������TIM1/TIM8
 * ע��: ͨ���޸���Щ�궨��,����֧��TIM1~TIM17����һ����ʱ��,����һ��IO��ʹ������Ƚ�ģʽ,���PWM
 */
#define ATIM_TIMX_COMP_CH3_GPIO_PORT            GPIOE
#define ATIM_TIMX_COMP_CH3_GPIO_PIN             GPIO_PIN_13
#define ATIM_TIMX_COMP_CH3_GPIO_AF              GPIO_AF1_TIM1                                 /* AF����ѡ�� */
#define ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define ATIM_TIMX_COMP_CH4_GPIO_PORT            GPIOE
#define ATIM_TIMX_COMP_CH4_GPIO_PIN             GPIO_PIN_14
#define ATIM_TIMX_COMP_CH4_GPIO_AF              GPIO_AF1_TIM1                                 /* AF����ѡ�� */
#define ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */


#define ATIM_TIMX_COMP                          TIM1            
#define ATIM_TIMX_COMP_CH3_CCRX                 TIM_CHANNEL_3        /* ͨ��3������ȽϼĴ��� */
#define ATIM_TIMX_COMP_CH4_CCRX                 TIM_CHANNEL_4        /* ͨ��4������ȽϼĴ��� */
#define ATIM_TIMX_COMP_CLK_ENABLE()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)   /* TIM1 ʱ��ʹ�� */

/* TIMX �������ģʽ ���� 
 * �������û���������Ӳ������, CHY���������, CHYN���������
 * �޸�CCRx�����޸�ռ�ձ�.
 * Ĭ�������TIM1/TIM8
 */

/* ���ͨ������ */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT            GPIOE
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN             GPIO_PIN_12
#define ATIM_TIMX_CPLM_CHY_GPIO_AF              GPIO_AF1_TIM1                          		/* AF����ѡ�� */
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)	/* PE��ʱ��ʹ�� */

/* �������ͨ������ */
#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT           GPIOE
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN            GPIO_PIN_13
#define ATIM_TIMX_CPLM_CHYN_GPIO_AF             GPIO_AF1_TIM1                           	/* AF����ѡ�� */
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)	/* PE��ʱ��ʹ�� */

/* ɲ���������� */
#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOA
#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_6
#define ATIM_TIMX_CPLM_BKIN_GPIO_AF             GPIO_AF1_TIM1                           	/* AF����ѡ�� */
#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)	/* PE��ʱ��ʹ�� */

/* �������ʹ�õĶ�ʱ�� */
#define ATIM_TIMX_CPLM                          TIM1            
#define ATIM_TIMX_CPLM_CHY                      GPIO_AF1_TIM1           
#define ATIM_TIMX_CPLM_CHY_CCRY                 TIM_CHANNEL_3       
#define ATIM_TIMX_CPLM_CLK_ENABLE()             do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)   /* TIM1 ʱ��ʹ�� */

/* TIMX PWM����ģʽ ���� 
 * ��������벶��ʹ�ö�ʱ��TIM1_CH3,
 * Ĭ�������TIM1/TIM8�ȸ߼���ʱ�� 
 */
#define ATIM_TIMX_PWMIN_CHY_GPIO_PORT           GPIOI
#define ATIM_TIMX_PWMIN_CHY_GPIO_PIN            GPIO_PIN_5
#define ATIM_TIMX_PWMIN_CHY_GPIO_AF             GPIO_AF3_TIM8                           	  /* AF����ѡ�� */
#define ATIM_TIMX_PWMIN_CHY_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)   /* PI��ʱ��ʹ�� */

#define ATIM_TIMX_PWMIN                         TIM8                       
#define ATIM_TIMX_PWMIN_IRQn                    TIM8_UP_IRQn
#define ATIM_TIMX_PWMIN_IRQHandler              TIM8_UP_IRQHandler
#define ATIM_TIMX_PWMIN_CHY                     TIM_CHANNEL_1                           /* ͨ��Y,  1<= Y <=2*/ 
#define ATIM_TIMX_PWMIN_CHY_CLK_ENABLE()        do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)   /* TIMX ʱ��ʹ�� */

 /* TIM1 / TIM8 �ж����Ĳ����жϷ�����,��Ҫ��������,����TIM2~5/TIM12/TIM15��,����Ҫ���¶��� */
#define ATIM_TIMX_PWMIN_CC_IRQn                 TIM8_CC_IRQn
#define ATIM_TIMX_PWMIN_CC_IRQHandler           TIM8_CC_IRQHandler

/******************************************************************************************/

void gtim_timx_npwm_chy_init(uint16_t arr, uint16_t psc); /* ͨ�ö�ʱ�� ���ָ������PWM��ʼ������ */
void gtim_timx_npwm_chy_gpio_init(void);                  /* ͨ�ö�ʱ�� ���ָ������PWM GPIO��ʼ������ */
void gtim_timx_npwm_chy_set(uint32_t npwm);               /* ͨ�ö�ʱ�� �������PWM�ĸ��� */

void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc);   /* �߼���ʱ�� ����Ƚ�ģʽ���PWM ��ʼ������ */
void atim_timx_comp_pwm_gpio_init(void);                    /* ��ʱ��ͨ�����ų�ʼ������ */

void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc);   /* �߼���ʱ�� ������� ��ʼ������ */
void atim_timx_cplm_pwm_gpio_init(void);                    /* ��ʱ���������ģʽͨ�����ų�ʼ������ */

void atim_timx_pwmin_chy_init(void);                        /* �߼���ʱ�� PWM����ģʽ��ʼ�� */
void atim_timx_pwmin_chy_restart(void);                     /* �߼���ʱ�� ����PWM����ģʽ��� */
void atim_timx_pwmin_chy_gpio_init(void);                   /* ��ʱ��PWM����ģʽͨ�����ų�ʼ������ */

#endif


















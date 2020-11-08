/**
 ****************************************************************************************************
 * @file        rng.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-12
 * @brief       RNG(�����������) ��������
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
 * V1.0 20200325
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __RNG_H
#define __RNG_H 

#include "./SYSTEM/sys/sys.h"

#define RNG_PORT                  RNG2
#define RNG_CLK_ENABLE()          do{ __HAL_RCC_RNG2_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */


uint8_t rng_init(void);             /* RNG��ʼ�� */
uint32_t rng_get_random_num(void);  /* �õ������ */
int rng_get_random_range(int min,int max);  /* �õ�����ĳ����Χ�ڵ������ */

#endif


















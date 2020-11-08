/**
 ****************************************************************************************************
 * @file        dac.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-16
 * @brief       DAC ��������
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
 * V1.0 20200516
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __DAC_H
#define __DAC_H

#include "./SYSTEM/sys/sys.h"

/* DAC������ ���� */

#define DAC_DACX_CHY_GPIO_PORT              GPIOA
#define DAC_DACX_CHY_GPIO_PIN               GPIO_PIN_4
#define DAC_DACX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define DAC_DACX                            DAC1 
#define DAC_DACX_CHY                        DAC_CHANNEL_1                                /* ͨ��Y,  0 <= Y <= 19 */ 
#define DAC_DACX_CHY_CLK_ENABLE()           do{ __HAL_RCC_DAC12_CLK_ENABLE(); }while(0)   /* DAC1ʱ��ʹ�� */

extern DAC_HandleTypeDef g_dac_handle;  /* DAC��� */
extern DAC_HandleTypeDef g_dac_dma_handle;

void dac_init(uint32_t outx);           /* DACͨ��1��ʼ�� */ 
void dac_set_voltage(uint16_t vol);     /* ����ͨ��1�����ѹ */ 
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n);   /* ������ǲ� */
void dac_dma_wave_init(void);           /* DAC DMA������Ҳ���ʼ������ */


#endif


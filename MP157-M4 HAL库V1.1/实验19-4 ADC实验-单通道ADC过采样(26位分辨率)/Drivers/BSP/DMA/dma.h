/**
 ****************************************************************************************************
 * @file        dma.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brief       DMA ��������
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
 * V1.0 20200513
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __DMA_H
#define __DMA_H

#include "./SYSTEM/sys/sys.h"

extern DMA_HandleTypeDef  g_dma_handle;                  /* DMA��� */

void dma_init(DMA_Stream_TypeDef *dma_stream_handle, uint32_t ch);  /* ����DMAx_CHx */
void dma_mux_init(DMA_Stream_TypeDef *DMA_Streamx, uint8_t ch);     /* DMA����������ʼ�� */
void dma_enable(DMA_Stream_TypeDef *DMA_Streamx, uint16_t ndtr);    /* ʹ��һ��DMA���� */
#endif

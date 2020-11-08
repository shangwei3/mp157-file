/**
 ****************************************************************************************************
 * @file        iic.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brief       IIC ��������
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
 * V1.0 20200520
 * ��һ�η���
 *
 ****************************************************************************************************
 */
#ifndef _IIC_H
#define _IIC_H
#include "./SYSTEM/sys/sys.h"

extern I2C_HandleTypeDef g_i2c5_handle;

void iic5_init(void);
#endif


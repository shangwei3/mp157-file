/**
 ****************************************************************************************************
 * @file        iic.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brief       IIC 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32MP1开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200520
 * 第一次发布
 *
 ****************************************************************************************************
 */
#ifndef _IIC_H
#define _IIC_H
#include "./SYSTEM/sys/sys.h"

extern I2C_HandleTypeDef g_i2c5_handle;

void iic5_init(void);
#endif


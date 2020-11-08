/**
 ****************************************************************************************************
 * @file        dac.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-16
 * @brief       DAC 驱动代码
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
 * V1.0 20200516
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __DAC_H
#define __DAC_H

#include "./SYSTEM/sys/sys.h"

/* DAC及引脚 定义 */

#define DAC_DACX_CHY_GPIO_PORT              GPIOA
#define DAC_DACX_CHY_GPIO_PIN               GPIO_PIN_4
#define DAC_DACX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define DAC_DACX                            DAC1 
#define DAC_DACX_CHY                        DAC_CHANNEL_1                                /* 通道Y,  0 <= Y <= 19 */ 
#define DAC_DACX_CHY_CLK_ENABLE()           do{ __HAL_RCC_DAC12_CLK_ENABLE(); }while(0)   /* DAC1时钟使能 */

extern DAC_HandleTypeDef g_dac_handle;  /* DAC句柄 */

void dac_init(uint32_t outx);           /* DAC通道1初始化 */ 
void dac_set_voltage(uint16_t vol);     /* 设置通道1输出电压 */ 
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n);   /* 输出三角波 */

#endif


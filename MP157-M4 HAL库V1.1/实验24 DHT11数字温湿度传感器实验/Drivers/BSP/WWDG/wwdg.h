/**
 ****************************************************************************************************
 * @file        wdg.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       窗口看门狗 驱动代码
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
 * V1.0 20200506
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __WWDG_H
#define __WWDG_H

#include "./SYSTEM/sys/sys.h"

void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer);

#endif





























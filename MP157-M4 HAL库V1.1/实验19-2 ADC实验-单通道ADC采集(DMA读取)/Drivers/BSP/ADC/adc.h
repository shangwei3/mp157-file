/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brief       ADC 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200513
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC及引脚 定义 */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_5
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_19                                /* 通道Y,  0 <= Y <= 19 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC12_CLK_ENABLE(); }while(0)   /* ADC1 & ADC2 时钟使能 */

/* ADC单通道/多通道 DMA采集 DMA数据流相关 定义
 * 注意: 这里我们的通道还是使用上面的定义.
 */
#define ADC_ADCX_DMASx                      DMA1_Stream7 
#define ADC_ADCX_DMASx_REQ                  DMA_REQUEST_ADC1                              /* ADC1_DMA请求源 */
#define ADC_ADCX_DMASx_IRQn                 DMA1_Stream7_IRQn 
#define ADC_ADCX_DMASx_IRQHandler           DMA1_Stream7_IRQHandler 

#define ADC_ADCX_DMASx_IS_TC()              ( __HAL_DMA_GET_FLAG(&g_dma_adc_handle, DMA_FLAG_TCIF3_7) )  /* 判断DMA1 Stream7传输完成标志, 这是一个假函数形式,
                                                                                                          * 不能当函数使用, 只能用在if等语句里面 
                                                                                                          */
#define ADC_ADCX_DMASx_CLR_TC()             do{ __HAL_DMA_CLEAR_FLAG(&g_dma_adc_handle, DMA_FLAG_TCIF3_7); }while(0)   /* 清除DMA1 Stream7传输完成标志 */


/******************************************************************************************/

void adc_init(void);                                           /* ADC初始化函数 */
void adc_gpio_init(void);                                      /* ADC的gpio初始化函数 */
uint32_t adc_get_result(uint32_t ch);                          /* 获得某个通道值  */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);   /* 得到某个通道给定次数采样的平均值 */

void adc_dma_init(uint32_t par, uint32_t mar); /* ADC DMA采集初始化 */
void adc_dma_enable( uint16_t ndtr);           /* 使能一次ADC DMA采集传输 */


#endif 















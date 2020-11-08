/**
 ****************************************************************************************************
 * @file        iic.c
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
 * V1.1 20200521
 * 第二次发布
 * 添加I2C4初始化代码
 *
 ****************************************************************************************************
 */
#include "./BSP/IIC/iic.h"
#include "./SYSTEM/delay/delay.h"

I2C_HandleTypeDef g_i2c5_handle;  /* I2C5句柄 */
I2C_HandleTypeDef g_i2c4_handle;  /* I2C4句柄 */

/**
 * @brief       IIC初始化函数
 *   @note      本函数支持I2C1~6,IIC时钟源为PCLK1=104.5Mhz
 *				Timing负责I2C速度设置，对应I2CX_TIMINGR寄存器，比寄存器各位描述如下：
 *				bit[31:28] PRESC  : 时间分频值，时钟周期tPRESC = (PRESC+1)*tI2CCLK
 *				bit[23:20] SCLDEL : 数据建立时间，也就是SDA跳变沿与SCL上升沿之间的延时，tSCLDEL = (SCLDEL+1)*tPRESC
 *				bit[19:16] SDADEL : 数据保持时间，也就是SCL下降沿与SDA跳变沿之间的延时，tSDADEL = (SDADEL+1)*tPRESC
 *				bit[15:8]  SCLH   : SCL高电平周期，tSCLH=(SCLH+1)*tPRESC
 *				bit[7:0]   SCLL	  : SCL低电平周期，tSCLL=(SCLL+1)*tPRESC
 *				通过PRESC、SCLH和SCLL即可确定I2C时钟频率，比如：
 *				400KHz时：I2CX_TIMINGR寄存器=0XC0000809，PRESEC=1100=12，tPRESC=(12+1)*(1/104500000)=124.4ns.
 *						  SCLH=1000=8, tSCLH=(8+1)*124.4ns=1119.6ns，
 *						  SCLL=1001=9, tSCLL=(9+1)*124.4ns=1244ns，
 *						  SCL周期为tSCLH+tSCLL=1119.6+1244=2363.6ns约等于423KHz。
 *			    注意！0XC0000809是STM32CubeMX计算出来的，因此在实际使用中Timing属性最好是直接用CubeMX来计算
 * @param       无
 * @retval      无
 */
void iic5_init(void)
{
	g_i2c5_handle.Instance = I2C5;									/* I2C5 */
	g_i2c5_handle.Init.Timing = 0xC0000809; 						/* 高速模式400KHz */
	g_i2c5_handle.Init.OwnAddress1 = 0x00;							/* I2C主机地址1(自定义,不要和从机冲突即可) */
	g_i2c5_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;	/* 7位地址模式 */
	g_i2c5_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;	/* 关闭双地址模式 */
	g_i2c5_handle.Init.OwnAddress2 = 0x00;							/* I2C主机地址2(自定义,不要和从机冲突即可) */
	g_i2c5_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;	/* 关闭通用呼叫寻址模式 */
	g_i2c5_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		/* 关闭No-Stretch模式 */
	HAL_I2C_Init(&g_i2c5_handle);
	
	HAL_I2CEx_ConfigAnalogFilter(&g_i2c5_handle, I2C_ANALOGFILTER_ENABLE); /* 配置模拟噪声滤波器 */
	HAL_I2CEx_ConfigDigitalFilter(&g_i2c5_handle, 0);				/* 配置数字噪声滤波器 */
}

/**
 * @brief       IIC4初始化函数
 *   @note      本函数支持I2C4,IIC4时钟源为HSI=64Mhz
 *				Timing负责I2C速度设置，对应I2CX_TIMINGR寄存器，比寄存器各位描述如下：
 *				bit[31:28] PRESC  : 时间分频值，时钟周期tPRESC = (PRESC+1)*tI2CCLK
 *				bit[23:20] SCLDEL : 数据建立时间，也就是SDA跳变沿与SCL上升沿之间的延时，tSCLDEL = (SCLDEL+1)*tPRESC
 *				bit[19:16] SDADEL : 数据保持时间，也就是SCL下降沿与SDA跳变沿之间的延时，tSDADEL = (SDADEL+1)*tPRESC
 *				bit[15:8]  SCLH   : SCL高电平周期，tSCLH=(SCLH+1)*tPRESC
 *				bit[7:0]   SCLL	  : SCL低电平周期，tSCLL=(SCLL+1)*tPRESC
 *				通过PRESC、SCLH和SCLL即可确定I2C时钟频率，比如：
 *				400KHz时：I2CX_TIMINGR寄存器=0XC0000809，PRESEC=1100=12，tPRESC=(12+1)*(1/104500000)=203.125ns.
 *						  SCLH=0110=6, tSCLH=(5+1)*203.125ns=1218.75ns，
 *						  SCLL=0111=7, tSCLL=(6+1)*203.125ns=1421.875ns，
 *						  SCL周期为tSCLH+tSCLL=1218.75+1421.875=2640.625ns约等于378.698KHz。
 *			    注意！0XC0000809是STM32CubeMX计算出来的，因此在实际使用中Timing属性最好是直接用CubeMX来计算
 * @param       无
 * @retval      无
 */
void iic4_init(void)
{
	g_i2c4_handle.Instance = I2C4;									/* I2C4 */
	g_i2c4_handle.Init.Timing = 0xC0000607; 						/* 高速模式400KHz，实际为378.698KHz */
	g_i2c4_handle.Init.OwnAddress1 = 0x00;							/* I2C主机地址1(自定义,不要和从机冲突即可) */
	g_i2c4_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;	/* 7位地址模式 */
	g_i2c4_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;	/* 关闭双地址模式 */
	g_i2c4_handle.Init.OwnAddress2 = 0x00;							/* I2C主机地址2(自定义,不要和从机冲突即可) */
	g_i2c4_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;	/* 关闭通用呼叫寻址模式 */
	g_i2c4_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		/* 关闭No-Stretch模式 */
	HAL_I2C_Init(&g_i2c4_handle);
	
	HAL_I2CEx_ConfigAnalogFilter(&g_i2c4_handle, I2C_ANALOGFILTER_ENABLE); /* 配置模拟噪声滤波器 */
	HAL_I2CEx_ConfigDigitalFilter(&g_i2c4_handle, 0);				/* 配置数字噪声滤波器 */
}

/**
 * @brief       IIC底层驱动，时钟配置
 * @param       hrtc:IIC句柄
 * @note        此函数会被HAL_I2C_Init()调用
 * @retval      无
 */

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;
	
	if(hi2c->Instance == I2C5)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();				/* 使能PA时钟 	*/
		__HAL_RCC_I2C5_CLK_ENABLE();				/* 使能I2C5时钟 */
		
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C35;		/* 配置I2C3,5时钟源 */
		PeriphClkInit.I2c35ClockSelection = RCC_I2C35CLKSOURCE_PCLK1;	/* I2C3,5时钟源位PCLK1=104.5MHz */
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11;	/* PA11和PA12  */
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C5;		/* 复用位I2C5 */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else if(hi2c->Instance == I2C4)
	{
		__HAL_RCC_GPIOZ_CLK_ENABLE();				/* 使能PZ时钟 	*/
		__HAL_RCC_I2C4_CLK_ENABLE();				/* 使能I2C4时钟 */
		
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C46;		/* 配置I2C4,6时钟源 */
		PeriphClkInit.I2c46ClockSelection = RCC_I2C46CLKSOURCE_HSI;		/* I2C4,6时钟源为HSI=64MHz */
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

		GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;	/* PZ4和PZ5  */
		GPIO_InitStruct.Alternate = GPIO_AF6_I2C4;		/* 复用位I2C4 */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOZ, &GPIO_InitStruct);
	}
}


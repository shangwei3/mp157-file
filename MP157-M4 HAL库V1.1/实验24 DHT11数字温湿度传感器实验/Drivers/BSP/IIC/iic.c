/**
 ****************************************************************************************************
 * @file        iic.c
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
 * V1.1 20200521
 * �ڶ��η���
 * ���I2C4��ʼ������
 *
 ****************************************************************************************************
 */
#include "./BSP/IIC/iic.h"
#include "./SYSTEM/delay/delay.h"

I2C_HandleTypeDef g_i2c5_handle;  /* I2C5��� */
I2C_HandleTypeDef g_i2c4_handle;  /* I2C4��� */

/**
 * @brief       IIC��ʼ������
 *   @note      ������֧��I2C1~6,IICʱ��ԴΪPCLK1=104.5Mhz
 *				Timing����I2C�ٶ����ã���ӦI2CX_TIMINGR�Ĵ������ȼĴ�����λ�������£�
 *				bit[31:28] PRESC  : ʱ���Ƶֵ��ʱ������tPRESC = (PRESC+1)*tI2CCLK
 *				bit[23:20] SCLDEL : ���ݽ���ʱ�䣬Ҳ����SDA��������SCL������֮�����ʱ��tSCLDEL = (SCLDEL+1)*tPRESC
 *				bit[19:16] SDADEL : ���ݱ���ʱ�䣬Ҳ����SCL�½�����SDA������֮�����ʱ��tSDADEL = (SDADEL+1)*tPRESC
 *				bit[15:8]  SCLH   : SCL�ߵ�ƽ���ڣ�tSCLH=(SCLH+1)*tPRESC
 *				bit[7:0]   SCLL	  : SCL�͵�ƽ���ڣ�tSCLL=(SCLL+1)*tPRESC
 *				ͨ��PRESC��SCLH��SCLL����ȷ��I2Cʱ��Ƶ�ʣ����磺
 *				400KHzʱ��I2CX_TIMINGR�Ĵ���=0XC0000809��PRESEC=1100=12��tPRESC=(12+1)*(1/104500000)=124.4ns.
 *						  SCLH=1000=8, tSCLH=(8+1)*124.4ns=1119.6ns��
 *						  SCLL=1001=9, tSCLL=(9+1)*124.4ns=1244ns��
 *						  SCL����ΪtSCLH+tSCLL=1119.6+1244=2363.6nsԼ����423KHz��
 *			    ע�⣡0XC0000809��STM32CubeMX��������ģ������ʵ��ʹ����Timing���������ֱ����CubeMX������
 * @param       ��
 * @retval      ��
 */
void iic5_init(void)
{
	g_i2c5_handle.Instance = I2C5;									/* I2C5 */
	g_i2c5_handle.Init.Timing = 0xC0000809; 						/* ����ģʽ400KHz */
	g_i2c5_handle.Init.OwnAddress1 = 0x00;							/* I2C������ַ1(�Զ���,��Ҫ�ʹӻ���ͻ����) */
	g_i2c5_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;	/* 7λ��ַģʽ */
	g_i2c5_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;	/* �ر�˫��ַģʽ */
	g_i2c5_handle.Init.OwnAddress2 = 0x00;							/* I2C������ַ2(�Զ���,��Ҫ�ʹӻ���ͻ����) */
	g_i2c5_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;	/* �ر�ͨ�ú���Ѱַģʽ */
	g_i2c5_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		/* �ر�No-Stretchģʽ */
	HAL_I2C_Init(&g_i2c5_handle);
	
	HAL_I2CEx_ConfigAnalogFilter(&g_i2c5_handle, I2C_ANALOGFILTER_ENABLE); /* ����ģ�������˲��� */
	HAL_I2CEx_ConfigDigitalFilter(&g_i2c5_handle, 0);				/* �������������˲��� */
}

/**
 * @brief       IIC4��ʼ������
 *   @note      ������֧��I2C4,IIC4ʱ��ԴΪHSI=64Mhz
 *				Timing����I2C�ٶ����ã���ӦI2CX_TIMINGR�Ĵ������ȼĴ�����λ�������£�
 *				bit[31:28] PRESC  : ʱ���Ƶֵ��ʱ������tPRESC = (PRESC+1)*tI2CCLK
 *				bit[23:20] SCLDEL : ���ݽ���ʱ�䣬Ҳ����SDA��������SCL������֮�����ʱ��tSCLDEL = (SCLDEL+1)*tPRESC
 *				bit[19:16] SDADEL : ���ݱ���ʱ�䣬Ҳ����SCL�½�����SDA������֮�����ʱ��tSDADEL = (SDADEL+1)*tPRESC
 *				bit[15:8]  SCLH   : SCL�ߵ�ƽ���ڣ�tSCLH=(SCLH+1)*tPRESC
 *				bit[7:0]   SCLL	  : SCL�͵�ƽ���ڣ�tSCLL=(SCLL+1)*tPRESC
 *				ͨ��PRESC��SCLH��SCLL����ȷ��I2Cʱ��Ƶ�ʣ����磺
 *				400KHzʱ��I2CX_TIMINGR�Ĵ���=0XC0000809��PRESEC=1100=12��tPRESC=(12+1)*(1/104500000)=203.125ns.
 *						  SCLH=0110=6, tSCLH=(5+1)*203.125ns=1218.75ns��
 *						  SCLL=0111=7, tSCLL=(6+1)*203.125ns=1421.875ns��
 *						  SCL����ΪtSCLH+tSCLL=1218.75+1421.875=2640.625nsԼ����378.698KHz��
 *			    ע�⣡0XC0000809��STM32CubeMX��������ģ������ʵ��ʹ����Timing���������ֱ����CubeMX������
 * @param       ��
 * @retval      ��
 */
void iic4_init(void)
{
	g_i2c4_handle.Instance = I2C4;									/* I2C4 */
	g_i2c4_handle.Init.Timing = 0xC0000607; 						/* ����ģʽ400KHz��ʵ��Ϊ378.698KHz */
	g_i2c4_handle.Init.OwnAddress1 = 0x00;							/* I2C������ַ1(�Զ���,��Ҫ�ʹӻ���ͻ����) */
	g_i2c4_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;	/* 7λ��ַģʽ */
	g_i2c4_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;	/* �ر�˫��ַģʽ */
	g_i2c4_handle.Init.OwnAddress2 = 0x00;							/* I2C������ַ2(�Զ���,��Ҫ�ʹӻ���ͻ����) */
	g_i2c4_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;	/* �ر�ͨ�ú���Ѱַģʽ */
	g_i2c4_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		/* �ر�No-Stretchģʽ */
	HAL_I2C_Init(&g_i2c4_handle);
	
	HAL_I2CEx_ConfigAnalogFilter(&g_i2c4_handle, I2C_ANALOGFILTER_ENABLE); /* ����ģ�������˲��� */
	HAL_I2CEx_ConfigDigitalFilter(&g_i2c4_handle, 0);				/* �������������˲��� */
}

/**
 * @brief       IIC�ײ�������ʱ������
 * @param       hrtc:IIC���
 * @note        �˺����ᱻHAL_I2C_Init()����
 * @retval      ��
 */

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;
	
	if(hi2c->Instance == I2C5)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();				/* ʹ��PAʱ�� 	*/
		__HAL_RCC_I2C5_CLK_ENABLE();				/* ʹ��I2C5ʱ�� */
		
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C35;		/* ����I2C3,5ʱ��Դ */
		PeriphClkInit.I2c35ClockSelection = RCC_I2C35CLKSOURCE_PCLK1;	/* I2C3,5ʱ��ԴλPCLK1=104.5MHz */
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11;	/* PA11��PA12  */
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C5;		/* ����λI2C5 */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else if(hi2c->Instance == I2C4)
	{
		__HAL_RCC_GPIOZ_CLK_ENABLE();				/* ʹ��PZʱ�� 	*/
		__HAL_RCC_I2C4_CLK_ENABLE();				/* ʹ��I2C4ʱ�� */
		
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C46;		/* ����I2C4,6ʱ��Դ */
		PeriphClkInit.I2c46ClockSelection = RCC_I2C46CLKSOURCE_HSI;		/* I2C4,6ʱ��ԴΪHSI=64MHz */
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

		GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;	/* PZ4��PZ5  */
		GPIO_InitStruct.Alternate = GPIO_AF6_I2C4;		/* ����λI2C4 */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOZ, &GPIO_InitStruct);
	}
}


/**
 ****************************************************************************************************
 * @file        dac.c
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

#include "./BSP/DAC/dac.h"
#include "./SYSTEM/delay/delay.h"


DAC_HandleTypeDef g_dac_handle;           /* DAC��� */

/**
 * @brief       DAC��ʼ������
 *   @note      ������֧��DAC1_OUT1/2ͨ����ʼ��
 *              DAC������ʱ������APB1, ʱ��Ƶ��=104.5Mhz=9.5ns
 *              DAC�����buffer�رյ�ʱ��, �������ʱ��: tSETTLING = 2us (STM32MP1�����ֲ���д)
 *              ���DAC���������ٶ�ԼΪ:500Khz, ��10����Ϊһ������, ��������50Khz���ҵĲ���
 *
 * @param       outx: Ҫ��ʼ����ͨ��. 1,ͨ��1; 2,ͨ��2
 * @retval      ��
 */
void dac_init(uint32_t outx)
{
    DAC_ChannelConfTypeDef dac_ch_conf;     /* DAC1ͨ�����ýṹ�� */
    
    g_dac_handle.Instance = DAC_DACX;
    HAL_DAC_Init(&g_dac_handle);                              /* ��ʼ��DAC */
	
	dac_ch_conf.DAC_Trigger = DAC_TRIGGER_NONE;  /* ��ʹ�ô������� */
	dac_ch_conf.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_DISABLE;
	dac_ch_conf.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE; 	/* DAC�������ֹر� */
	dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;		/* DAC�������ر� */
	dac_ch_conf.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	dac_ch_conf.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
    HAL_DAC_ConfigChannel(&g_dac_handle, &dac_ch_conf, outx); /* DACͨ������ */
    
    HAL_DAC_Start(&g_dac_handle, outx);  /* ����DACͨ�� */
}

/**
 * @brief       DAC�ײ�������ʱ�����ã����� ����
 * @param       hdac:DAC���
 * @note        �˺����ᱻHAL_DAC_Init()����
 * @retval      ��
 */
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
    GPIO_InitTypeDef gpio_init_struct;

    DAC_DACX_CHY_CLK_ENABLE();             		/* ʹ��DACʱ�� */
    DAC_DACX_CHY_GPIO_CLK_ENABLE();             /* ����GPIOAʱ�� */

    gpio_init_struct.Pin = DAC_DACX_CHY_GPIO_PIN;        /* PA4 */
    gpio_init_struct.Mode = GPIO_MODE_ANALOG; /* ģ�� */
    gpio_init_struct.Pull = GPIO_NOPULL;      /* ���������� */
    HAL_GPIO_Init(DAC_DACX_CHY_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ����ͨ��1/2�����ѹ
 * @param       outx: 1,ͨ��1; 2,ͨ��2
 * @param       vol : 0~3300,����0~3.3V
 * @retval      ��
 */
void dac_set_voltage(uint16_t vol)
{
    double temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;

    HAL_DAC_SetValue(&g_dac_handle, DAC_DACX_CHY, DAC_ALIGN_12B_R, temp); /* 12λ�Ҷ������ݸ�ʽ����DACֵ */
}






/**
 ****************************************************************************************************
 * @file        adc.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-13
 * @brief       ADC ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32H750������
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

#include "./BSP/ADC/adc.h"
#include "./BSP/DMA/dma.h"
#include "./SYSTEM/delay/delay.h"


ADC_HandleTypeDef g_adc_handle;   /* ADC��� */

/**
 * @brief       ADC��ʼ������
 *   @note      ������֧��ADC1/ADC2����ͨ��,���ǲ�֧��ADC3
 *              ����ʹ��16λ����, ADC����ʱ��=32M, ת��ʱ��Ϊ:�������� + 8.5��ADC����
 *              ��������������: 810.5, ��ת��ʱ�� = 819��ADC���� = 25.6us
 * @param       ��
 * @retval      ��
 */
void adc_init(void)
{
	RCC_PeriphCLKInitTypeDef adc_periphclk_init_struct;
	
    ADC_ADCX_CHY_CLK_ENABLE();                   /* ʹ��ADC1/2ʱ�� */
	
	/* ����ADCʱ��Դ=PER=24MHz  */
	adc_periphclk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	adc_periphclk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PER;
	HAL_RCCEx_PeriphCLKConfig(&adc_periphclk_init_struct);

    adc_gpio_init();                             /* GPIO��ʼ�� */

    g_adc_handle.Instance = ADC_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;            /* ����ʱ��2��Ƶ,��adc_ker_ck=per_ck/2=32Mhz */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_16B;                      /* 16λģʽ  */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                      /* ��ɨ��ģʽ */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                   /* �ر�EOC�ж� */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                           /* �Զ��͹��Ĺر� */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                         /* �ر�����ת�� */
    g_adc_handle.Init.NbrOfConversion = 1;                                  /* ʹ����1��ת��ͨ�� */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                      /* ��ֹ����������ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 0;                              /* ��ֹ������ģʽ�󣬴˲������ԣ�����������ͨ����Ϊ0 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* ������� */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* ������������Ļ�����λ���� */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                   /* ���µ����ݵ�����ֱ�Ӹ��ǵ������� */
    g_adc_handle.Init.OversamplingMode = DISABLE;                           /* �������ر� */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;     /* ����ͨ�������ݽ���������DR�Ĵ������� */
    HAL_ADC_Init(&g_adc_handle);                                            /* ��ʼ�� */

    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED); /* ADCУ׼ */
}

/**
 * @brief       ADC��gpio��ʼ������
 * @param       ��
 * @note        �˺����ᱻadc_init()����
 * @retval      ��
 */
void adc_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    ADC_ADCX_CHY_GPIO_CLK_ENABLE();              /* ����ADCͨ��IO����ʱ�� */

    gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;    /* ADCͨ��IO���� */
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;        /* ģ�� */
    gpio_init_struct.Pull = GPIO_NOPULL;             /* ���������� */
    HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ���ADCת����Ľ�� 
 * @param       ch: ͨ��ֵ 0~19��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_19
 * @retval      ����ֵ:ת�����
 */
uint32_t adc_get_result(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;

    ADC1_ChanConf.Channel = ch;                                   /* ͨ�� */
    ADC1_ChanConf.Rank = ADC_REGULAR_RANK_1;                      /* 1������ */
    ADC1_ChanConf.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;      /* ����ʱ�� */
    ADC1_ChanConf.SingleDiff = ADC_SINGLE_ENDED;                  /* ���߲ɼ� */
    ADC1_ChanConf.OffsetNumber = ADC_OFFSET_NONE;
    ADC1_ChanConf.Offset = 0;   
    HAL_ADC_ConfigChannel(&g_adc_handle ,&ADC1_ChanConf);         /* ͨ������ */

    HAL_ADC_Start(&g_adc_handle);                                 /* ����ADC */

    HAL_ADC_PollForConversion(&g_adc_handle, 10);                 /* ��ѯת�� */
    return HAL_ADC_GetValue(&g_adc_handle);                       /* �������һ��ADC1�������ת����� */
}

/**
 * @brief       ��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ��
 * @param       ch      : ͨ����, 0~19
 * @param       times   : ��ȡ����
 * @retval      ͨ��ch��times��ת�����ƽ��ֵ
 */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;

    for (t = 0; t < times; t++) /* ��ȡtimes������ */
    {
        temp_val += adc_get_result(ch);
        delay_ms(5);
    }

    return temp_val / times;    /* ����ƽ��ֵ */
}

/***************************************��ͨ��ADC�ɼ�(DMA��ȡ)����*****************************************/

ADC_HandleTypeDef g_adc_dma_handle;     /* ��DMA������ADC��� */
DMA_HandleTypeDef g_dma_adc_handle;     /* ��ADC������DMA��� */

uint8_t g_adc_dma_sta = 0;              /* DMA����״̬��־, 0,δ���; 1, ����� */

/**
 * @brief       ADC DMA��ȡ ��ʼ������
 *   @note      ����������ʹ��adc_init��ADC���д󲿷�����,�в���ĵط��ٵ�������
 * @param       par         : �����ַ
 * @param       mar         : �洢����ַ
 * @retval      ��
 */
void adc_dma_init(uint32_t par, uint32_t mar)
{
	RCC_PeriphCLKInitTypeDef adc_periphclk_init_struct;
    ADC_ChannelConfTypeDef adc_ch_conf;
    
    ADC_ADCX_CHY_CLK_ENABLE();                                                  /* ʹ��ADC1/2ʱ�� */
	__HAL_RCC_DMAMUX_CLK_ENABLE();												/* ʹ��DMAMUXʱ�� */
	
	/* ����ADCʱ��Դ=PER=24MHz  */
	adc_periphclk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	adc_periphclk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PER;
	HAL_RCCEx_PeriphCLKConfig(&adc_periphclk_init_struct);
	
    adc_gpio_init();                                                            /* GPIO��ʼ�� */
    
    g_adc_dma_handle.Instance = ADC_ADCX;
    g_adc_dma_handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;            /* ����ʱ��2��Ƶ,��adc_ker_ck=pll4r_ck/2=37.125Mhz */
    g_adc_dma_handle.Init.Resolution = ADC_RESOLUTION_16B;                      /* 16λģʽ  */
    g_adc_dma_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                      /* ��ɨ��ģʽ */
    g_adc_dma_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                   /* �ر�EOC�ж� */
    g_adc_dma_handle.Init.LowPowerAutoWait = DISABLE;                           /* �Զ��͹��Ĺر� */
    g_adc_dma_handle.Init.ContinuousConvMode = DISABLE;                         /* �ر�����ת�� */
    g_adc_dma_handle.Init.NbrOfConversion = 1;                                  /* ʹ����1��ת��ͨ�� */
    g_adc_dma_handle.Init.DiscontinuousConvMode = DISABLE;                      /* ��ֹ����������ģʽ */
    g_adc_dma_handle.Init.NbrOfDiscConversion = 0;                              /* ��ֹ������ģʽ�󣬴˲������ԣ�����������ͨ����Ϊ0 */
    g_adc_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* ����������� */
    g_adc_dma_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* ������������Ļ�����λ���� */
    g_adc_dma_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                   /* ���µ����ݵ�����ֱ�Ӹ��ǵ������� */
    g_adc_dma_handle.Init.OversamplingMode = DISABLE;                           /* �������ر� */
    g_adc_dma_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;     /* ����ͨ�������ݽ���������DR�Ĵ������� */
    HAL_ADC_Init(&g_adc_dma_handle);                                            /* ��ʼ�� */

    HAL_ADCEx_Calibration_Start(&g_adc_dma_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED); /* ADCУ׼ */

    /* ����ADC����ת��, DMA���δ���ADC���� */
    ADC_ADCX->CFGR |= 1 << 0;   /* DMNGT[1:0] = 01, DMA���δ���ADC���� */
    ADC_ADCX->CFGR |= 1 << 13;  /* CONT = 1, ����ת��ģʽ */

    /* DMA������� */
    dma_mux_init(ADC_ADCX_DMASx, ADC_ADCX_DMASx_REQ);  /* ��ʼ��DMA �������� */    
    ADC_ADCX_DMASx->PAR = par;      /* DMA�����ַ */
    ADC_ADCX_DMASx->M0AR = mar;     /* DMA �洢��0��ַ */
    ADC_ADCX_DMASx->NDTR = 0;       /* DMA �洢��0��ַ */

    g_dma_adc_handle.Instance = ADC_ADCX_DMASx;                           /* ʹ��DMA1 Stream7 */
    g_dma_adc_handle.Init.Request = ADC_ADCX_DMASx_REQ;                   /* �������Ͳ���DMA_REQUEST_ADC1 */
    g_dma_adc_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;               /* �����赽�洢��ģʽ */
    g_dma_adc_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* ���������ģʽ */
    g_dma_adc_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* �洢������ģʽ */
    g_dma_adc_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  /* �������ݳ���:16λ */
    g_dma_adc_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;     /* �洢�����ݳ���:16λ */
    g_dma_adc_handle.Init.Mode = DMA_CIRCULAR;                            /* ѭ��ģʽ */
    g_dma_adc_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* �е����ȼ� */
    g_dma_adc_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;                /* ��ֹFIFO*/
    HAL_DMA_Init(&g_dma_adc_handle);  /* ��ʼ��DMA */

    ADC_ADCX_DMASx->CR |= 1 << 4;     /* TCIE = 1, DMA��������ж�ʹ�� */

    __HAL_LINKDMA(&g_adc_dma_handle, DMA_Handle, g_dma_adc_handle);       /* ��DMA��adc��ϵ���� */

    HAL_NVIC_SetPriority(ADC_ADCX_DMASx_IRQn, 3, 3);
    HAL_NVIC_EnableIRQ(ADC_ADCX_DMASx_IRQn);

    adc_ch_conf.Channel = ADC_ADCX_CHY;                    /* ����ʹ�õ�ADCͨ�� */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;                 /* ����������ĵ�1�� */
    adc_ch_conf.SamplingTime = ADC_SAMPLETIME_810CYCLES_5; /* ��������Ϊ810.5��ʱ������ */
    adc_ch_conf.SingleDiff = ADC_SINGLE_ENDED ;            /* �������� */
    adc_ch_conf.OffsetNumber = ADC_OFFSET_NONE;            /* ��ƫ�� */
    adc_ch_conf.Offset = 0;                                /* ��ƫ�Ƶ�����£��˲������� */
    adc_ch_conf.OffsetRightShift       = DISABLE;          /* ��ֹ���� */
    adc_ch_conf.OffsetSignedSaturation = DISABLE;          /* ��ֹ�з��ű��� */
    HAL_ADC_ConfigChannel(&g_adc_dma_handle, &adc_ch_conf);/* ����ADCͨ�� */

    ADC_Enable(&g_adc_dma_handle);                         /* ʹ��ADC */
}

/**
 * @brief       ʹ��һ��ADC DMA���� 
 * @param       ndtr: DMA����Ĵ���
 * @retval      ��
 */
void adc_dma_enable(uint16_t ndtr)
{
    dma_enable(ADC_ADCX_DMASx, ndtr);       /* ����ʹ��DMA���� */
    
    ADC_ADCX->CR |= 1 << 2;                 /* ��������ת��ͨ�� */
}

/**
 * @brief       ADC DMA�ɼ��жϷ�����
 * @param       �� 
 * @retval      ��
 */
void ADC_ADCX_DMASx_IRQHandler(void)
{
    if (ADC_ADCX_DMASx_IS_TC())
    {
        g_adc_dma_sta = 1;          /* ���DMA������� */
        ADC_ADCX_DMASx_CLR_TC();    /* ���DMA1 ������7 ��������ж� */
    }
}











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

/***************************************DAC������ǲ�����*****************************************/

/**
 * @brief       ����DAC_OUT1������ǲ�
 *   @note      ���Ƶ�� �� 1000 / (dt * samples) Khz, ������dt��С��ʱ��,����С��5usʱ, ����delay_us
 *              ����Ͳ�׼��(���ú���,����ȶ���Ҫʱ��,��ʱ��С��ʱ��,��Щʱ���Ӱ�쵽��ʱ), Ƶ�ʻ�ƫС.
 * 
 * @param       maxval : ���ֵ(0 < maxval < 4096), (maxval + 1)������ڵ���samples/2
 * @param       dt     : ÿ�����������ʱʱ��(��λ: us)
 * @param       samples: ������ĸ���, samples����С�ڵ���(maxval + 1) * 2 , ��maxval���ܵ���0
 * @param       n      : ������θ���,0~65535
 *
 * @retval      ��
 */
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n)
{
    uint16_t i, j;
    float incval;           /* ������ */
    
    if((maxval + 1) <= samples)return ; /* ���ݲ��Ϸ� */
        
    incval = (maxval + 1) / (samples / 2);  /* ��������� */
    
    for(j = 0; j < n; j++)
    { 
        DAC1->DHR12R1 = 0;  /* �����0 */
        for(i = 0; i < (samples / 2); i++)  /* ��������� */
        { 
             DAC1->DHR12R1 +=  incval;
             delay_us(dt);
        } 
        for(i = 0; i < (samples / 2); i++)  /* ����½��� */
        {
             DAC1->DHR12R1 -=  incval;
             delay_us(dt);
        }
    }
}

/***************************************DAC������Ҳ�����*****************************************/

DAC_HandleTypeDef g_dac_dma_handle;
DMA_HandleTypeDef g_dma_dac_handle;

/**
 * @brief       DAC DMA������Ҳ���ʼ������
 *   @note      ������֧��DAC1_OUT1/2ͨ����ʼ��
 *              DAC������ʱ������APB1, ʱ��Ƶ��=104.5Mhz=9.5ns
 *              DAC�����buffer�رյ�ʱ��, �������ʱ��: tSETTLING = 2us (STM32MP1�����ֲ���д)
 *              ���DAC���������ٶ�ԼΪ:500Khz, ��10����Ϊһ������, ��������50Khz���ҵĲ���
 *
 * @param       outx: Ҫ��ʼ����ͨ��. 1,ͨ��1; 2,ͨ��2
 * @param       DMA_Streamx : DMA������,DMA1_Stream0~7/DMA2_Stream0~7
 * @param       ch          : DMAͨ��ѡ��
 * @param       arr         : TIM7���Զ���װ��ֵ
 * @param       psc         : TIM7�ķ�Ƶϵ��
 * @retval      ��
 */
void dac_dma_wave_init(void)
{
    DAC_ChannelConfTypeDef sConfig={0};
    TIM_MasterConfigTypeDef sMasterConfig={0};
    GPIO_InitTypeDef gpio_init_struct;
    TIM_HandleTypeDef tim7_handle;

    __HAL_RCC_GPIOA_CLK_ENABLE();             	/* DACͨ�����Ŷ˿�ʱ��ʹ�� 	*/
    __HAL_RCC_DAC12_CLK_ENABLE();             	/* DAC����ʱ��ʹ�� 			*/
    __HAL_RCC_DMA2_CLK_ENABLE();              	/* DMAʱ��ʹ�� 				*/
	__HAL_RCC_DMAMUX_CLK_ENABLE();				/* ʹ��DMAMUXʱ�� 			*/
    __HAL_RCC_TIM7_CLK_ENABLE();              	/* TIM7ʱ��ʹ�� 			*/

    gpio_init_struct.Pin = GPIO_PIN_4;        	/* PA4 						*/
    gpio_init_struct.Mode = GPIO_MODE_ANALOG; 	/* ģ�� 					*/
    gpio_init_struct.Pull = GPIO_NOPULL;      	/* ���������� 				*/
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);  	/* ��ʼ��DAC���� 			*/

    g_dac_dma_handle.Instance = DAC1;
    HAL_DAC_Init(&g_dac_dma_handle);                                     /* DAC��ʼ�� */

    g_dma_dac_handle.Instance = DMA2_Stream6;                            /* ʹ�õ�DAM2 Stream6 */
    g_dma_dac_handle.Init.Request = DMA_REQUEST_DAC1;                	 /* DAC����DMA���� */
    g_dma_dac_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;              /* �洢��������ģʽ */
    g_dma_dac_handle.Init.PeriphInc = DMA_PINC_DISABLE;                  /* �����ַ��ֹ���� */
    g_dma_dac_handle.Init.MemInc = DMA_MINC_ENABLE;                      /* �洢����ַ���� */
    g_dma_dac_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; /* �������ݳ���:16λ */
    g_dma_dac_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;    /* �洢�����ݳ���:16λ */
    g_dma_dac_handle.Init.Mode = DMA_CIRCULAR;                           /* ѭ��ģʽ */
    g_dma_dac_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                /* �е����ȼ� */
    g_dma_dac_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;               /* ��ʹ��FIFO */
    HAL_DMA_Init(&g_dma_dac_handle);                                     /* ��ʼ��DMA */

    __HAL_LINKDMA(&g_dac_dma_handle, DMA_Handle1, g_dma_dac_handle);     /* DMA�����DAC������� */

    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 1, 0);                       /* ��ռ���ȼ�1�������ȼ�0 */
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);                               /* ʹ��DMA�ж�ͨ�� */

    sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;               /* �رղ�������ģʽ�����ģʽ��Ҫ���ڵ͹��� */
    sConfig.DAC_Trigger = DAC_TRIGGER_T7_TRGO;                           /* ���ö�ʱ��7���� */
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;                  /* ʹ��������� */
    sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;       /* ����DAC���ӵ�Ƭ������ */
    sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;                     /* ʹ�ó���У׼ */
    HAL_DAC_ConfigChannel(&g_dac_dma_handle, &sConfig, DAC_CHANNEL_1);   /* DACͨ��������� */

    tim7_handle.Instance = TIM7;                                         /* ѡ��ʱ��7 */
    tim7_handle.Init.Prescaler = 209;                                     /* ��Ƶϵ�� */
    tim7_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                   /* ���ϼ��� */
    tim7_handle.Init.Period = 1;                                         /* ��װ��ֵ */
    tim7_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;  /* �Զ���װ */
    HAL_TIM_Base_Init(&tim7_handle);                                     /* ��ʼ����ʱ��7 */

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&tim7_handle, &sMasterConfig); /* ����TIM7 TRGO */
    HAL_TIM_Base_Start(&tim7_handle);                                    /* ʹ�ܶ�ʱ��7 */
}

/**
 * @brief       DAC DMA�жϷ�����
 * @param       �� 
 * @retval      ��
 */
void DMA2_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_dma_dac_handle);
}




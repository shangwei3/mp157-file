/**
 ****************************************************************************************************
 * @file        atim.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       �߼���ʱ�� ��������
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
 * V1.0 20200506
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/TIMER/atim.h"
#include "./BSP/LED/led.h"

/*********************************ͨ�ö�ʱ�����ָ������PWM����*************************************/

TIM_HandleTypeDef g_timx_npwm_chy_handle;     /* ��ʱ��x��� */
TIM_OC_InitTypeDef g_timx_oc_npwm_chy_handle; /* ��ʱ�������� */

/* g_npwm_remain��ʾ��ǰ��ʣ�¶��ٸ�����Ҫ���� 
 * ÿ����෢��256������
 */
static uint32_t g_npwm_remain = 0;

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ���ָ������PWM ��ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��D2PPRE1��2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ120M, ���Զ�ʱ��ʱ�� = 240Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_npwm_chy_init(uint16_t arr,uint16_t psc)
{
    gtim_timx_npwm_chy_gpio_init();
    GTIM_TIMX_NPWM_CHY_CLK_ENABLE();
    
    g_timx_npwm_chy_handle.Instance = GTIM_TIMX_NPWM;                     /* ��ʱ��x */
    g_timx_npwm_chy_handle.Init.Prescaler = psc;                          /* ��ʱ����Ƶ */
    g_timx_npwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;         /* ���ϼ���ģʽ */
    g_timx_npwm_chy_handle.Init.Period = arr;                             /* �Զ���װ��ֵ */
    g_timx_npwm_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;   /* ʱ�ӷ�Ƶ���� */
    HAL_TIM_PWM_Init(&g_timx_npwm_chy_handle);                            /* ��ʼ��PWM */
    
    g_timx_oc_npwm_chy_handle.OCMode = TIM_OCMODE_PWM1;                  /* ģʽѡ��PWM1 */
    g_timx_oc_npwm_chy_handle.Pulse = arr/2;                             /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
                                                                         /* Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50% */
    g_timx_oc_npwm_chy_handle.OCPolarity = TIM_OCPOLARITY_HIGH;          /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_PWM_ConfigChannel(&g_timx_npwm_chy_handle, &g_timx_oc_npwm_chy_handle, GTIM_TIMX_NPWM_CHY);/* ����TIMxͨ��y */

    
    HAL_TIM_PWM_Start(&g_timx_npwm_chy_handle, GTIM_TIMX_NPWM_CHY);       /* ����PWMͨ��y */
    
    HAL_NVIC_SetPriority(GTIM_TIMX_NPWM_IRQn, 1, 3);  /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_NPWM_IRQn);          /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_timx_npwm_chy_handle);   /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
   
}

/**
 * @brief       ͨ�ö�ʱ�����ָ������PWMͨ�����ų�ʼ������
 * @param       htim:��ʱ�����
 * @note        �˺����ᱻgtim_timx_npwm_chy_init()����
 * @retval      ��
 */
void gtim_timx_npwm_chy_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    GTIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE();                    /* ����ͨ��y��GPIOʱ�� */

    gpio_init_struct.Pin = GTIM_TIMX_NPWM_CHY_GPIO_PIN;      /* ͨ��y��GPIO�� */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                 /* ����������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      /* ���� */
    gpio_init_struct.Alternate = GTIM_TIMX_NPWM_CHY_GPIO_AF; /* ��ʱ��xͨ��y��GPIO�ڸ��� */
    HAL_GPIO_Init(GTIM_TIMX_NPWM_CHY_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ͨ�ö�ʱ��TIMX NPWM����PWM����
 * @param       rcr: PWM�ĸ���, 1~2^32�η���
 * @retval      ��
 */
void gtim_timx_npwm_chy_set(uint32_t npwm)
{
    if (npwm == 0)return ;
    g_npwm_remain = npwm;               /* ����������� */
    GTIM_TIMX_NPWM->EGR |= 1 << 0;      /* ����һ�θ����¼�,���ж����洦��������� */
    GTIM_TIMX_NPWM->CR1 |= 1 << 0;      /* ʹ�ܶ�ʱ��TIMX */
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_NPWM_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_npwm_chy_handle);
}

/**
 * @brief       ��ʱ�������жϻص�����
 * @param       htim:��ʱ�����ָ��
 * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /**********************************���ָ������PWM�������********************************/
    if (htim == (&g_timx_npwm_chy_handle)) /* ͨ�ö�ʱ�����ָ������PWMʵ��ص�ִ�е����� */
    {
        uint16_t npwm = 0;
        
        if (g_npwm_remain > 256)        /* ���д���256��������Ҫ���� */
        {
            g_npwm_remain=g_npwm_remain - 256;
            npwm = 256;
        }
        else if (g_npwm_remain % 256)   /* ����λ��������256��������Ҫ���� */
        {
            npwm = g_npwm_remain % 256; 
            g_npwm_remain = 0;          /* û�������� */
        }
        if (npwm)   /* ������Ҫ���� */
        { 
            GTIM_TIMX_NPWM->RCR = npwm - 1; /* �����ظ������Ĵ���ֵΪnpwm-1, ��npwm������ */
            GTIM_TIMX_NPWM->EGR |= 1 << 0;  /* ����һ�θ����¼�,�Ը���RCR�Ĵ��� */
            GTIM_TIMX_NPWM->CR1 |= 1 << 0;  /* ʹ�ܶ�ʱ��TIMX */
        }
        else
        { 
            GTIM_TIMX_NPWM->CR1 &= ~(1 << 0);   /* �رն�ʱ��TIMX */
        }
    }
}

/*********************************  �߼���ʱ������Ƚϳ���*************************************/

TIM_HandleTypeDef g_timx_comp_pwm_handle;                              /* ��ʱ��x��� */

/**
 * @brief       �߼���ʱ��TIMX ����Ƚ�ģʽ ��ʼ��������ʹ������Ƚ�ģʽ��
 * @note
 *              ���ø߼���ʱ��TIMX 2·����Ƚ�ģʽPWM���,ʵ��50%ռ�ձ�,��ͬ��λ����
 *              ע��,����������Ƚ�ģʽ,ÿ2���������ڲ������һ��PWM���,������Ƶ�ʼ���
 *              ����,���ǻ����Կ����ж����ж������޸�CCRx,�Ӷ�ʵ�ֲ�ͬƵ��/��ͬ��λ�Ŀ���
 *              �������ǲ��Ƽ���ôʹ��,��Ϊ����ܵ��·ǳ�Ƶ�����ж�,�Ӷ�ռ�ô���CPU��Դ
 *
 *              �߼���ʱ����ʱ������APB2,��APB2DIV��2��Ƶ��ʱ��
 *              �߼���ʱ����ʱ��ΪAPB2ʱ�ӵ�2��, ��APB2Ϊ104.5M, ���Զ�ʱ��ʱ�� = 209Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    atim_timx_comp_pwm_gpio_init();
    ATIM_TIMX_COMP_CLK_ENABLE();

    g_timx_comp_pwm_handle.Instance = ATIM_TIMX_COMP;                       /* ��ʱ��1 */
    g_timx_comp_pwm_handle.Init.Prescaler = psc  ;                          /* ��ʱ����Ƶ */
    g_timx_comp_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;           /* ���ϼ���ģʽ */
    g_timx_comp_pwm_handle.Init.Period = arr;                               /* �Զ���װ��ֵ */
    g_timx_comp_pwm_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;     /* ʱ�ӷ�Ƶ���� */
    g_timx_comp_pwm_handle.Init.RepetitionCounter = 0;
    g_timx_comp_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&g_timx_comp_pwm_handle);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&g_timx_comp_pwm_handle, &sClockSourceConfig);

    HAL_TIM_OC_Init(&g_timx_comp_pwm_handle);                               /*����Ƚϳ�ʼ��TIMx */

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&g_timx_comp_pwm_handle, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;         /* �Ƚ����ģʽ */
    sConfigOC.Pulse = 250;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &sConfigOC, TIM_CHANNEL_3);
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_3);

    sConfigOC.Pulse = 500;
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &sConfigOC, TIM_CHANNEL_4);
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_4);

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_comp_pwm_handle, &sBreakDeadTimeConfig);
}

/**
 * @brief       ��ʱ������Ƚ�ģʽͨ�����ų�ʼ������
 * @param       ��
 * @note        �˺����ᱻatim_timx_comp_pwm_init()��������
 * @retval      ��
 */
void atim_timx_comp_pwm_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE();
    ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin = ATIM_TIMX_COMP_CH3_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_COMP_CH3_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_COMP_CH3_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = ATIM_TIMX_COMP_CH4_GPIO_PIN;
    gpio_init_struct.Alternate = ATIM_TIMX_COMP_CH4_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_COMP_CH4_GPIO_PORT, &gpio_init_struct);
}










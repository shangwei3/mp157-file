/**
 ****************************************************************************************************
 * @file        atim.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-06
 * @brief       高级定时器 驱动代码
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

#include "./BSP/TIMER/atim.h"
#include "./BSP/LED/led.h"

/*********************************通用定时器输出指定个数PWM程序*************************************/

TIM_HandleTypeDef g_timx_npwm_chy_handle;     /* 定时器x句柄 */
TIM_OC_InitTypeDef g_timx_oc_npwm_chy_handle; /* 定时器输出句柄 */

/* g_npwm_remain表示当前还剩下多少个脉冲要发送 
 * 每次最多发送256个脉冲
 */
static uint32_t g_npwm_remain = 0;

/**
 * @brief       通用定时器TIMX 通道Y 输出指定个数PWM 初始化函数
 * @note
 *              通用定时器的时钟来自APB1,当D2PPRE1≥2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为120M, 所以定时器时钟 = 240Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_npwm_chy_init(uint16_t arr,uint16_t psc)
{
    gtim_timx_npwm_chy_gpio_init();
    GTIM_TIMX_NPWM_CHY_CLK_ENABLE();
    
    g_timx_npwm_chy_handle.Instance = GTIM_TIMX_NPWM;                     /* 定时器x */
    g_timx_npwm_chy_handle.Init.Prescaler = psc;                          /* 定时器分频 */
    g_timx_npwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;         /* 向上计数模式 */
    g_timx_npwm_chy_handle.Init.Period = arr;                             /* 自动重装载值 */
    g_timx_npwm_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;   /* 时钟分频因子 */
    HAL_TIM_PWM_Init(&g_timx_npwm_chy_handle);                            /* 初始化PWM */
    
    g_timx_oc_npwm_chy_handle.OCMode = TIM_OCMODE_PWM1;                  /* 模式选择PWM1 */
    g_timx_oc_npwm_chy_handle.Pulse = arr/2;                             /* 设置比较值,此值用来确定占空比 */
                                                                         /* 默认比较值为自动重装载值的一半,即占空比为50% */
    g_timx_oc_npwm_chy_handle.OCPolarity = TIM_OCPOLARITY_HIGH;          /* 输出比较极性为高 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_npwm_chy_handle, &g_timx_oc_npwm_chy_handle, GTIM_TIMX_NPWM_CHY);/* 配置TIMx通道y */

    
    HAL_TIM_PWM_Start(&g_timx_npwm_chy_handle, GTIM_TIMX_NPWM_CHY);       /* 开启PWM通道y */
    
    HAL_NVIC_SetPriority(GTIM_TIMX_NPWM_IRQn, 1, 3);  /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_NPWM_IRQn);          /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&g_timx_npwm_chy_handle);   /* 使能定时器x和定时器x更新中断 */
   
}

/**
 * @brief       通用定时器输出指定个数PWM通道引脚初始化函数
 * @param       htim:定时器句柄
 * @note        此函数会被gtim_timx_npwm_chy_init()调用
 * @retval      无
 */
void gtim_timx_npwm_chy_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    GTIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE();                    /* 开启通道y的GPIO时钟 */

    gpio_init_struct.Pin = GTIM_TIMX_NPWM_CHY_GPIO_PIN;      /* 通道y的GPIO口 */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                 /* 复用推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      /* 高速 */
    gpio_init_struct.Alternate = GTIM_TIMX_NPWM_CHY_GPIO_AF; /* 定时器x通道y的GPIO口复用 */
    HAL_GPIO_Init(GTIM_TIMX_NPWM_CHY_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       通用定时器TIMX NPWM设置PWM个数
 * @param       rcr: PWM的个数, 1~2^32次方个
 * @retval      无
 */
void gtim_timx_npwm_chy_set(uint32_t npwm)
{
    if (npwm == 0)return ;
    g_npwm_remain = npwm;               /* 保存脉冲个数 */
    GTIM_TIMX_NPWM->EGR |= 1 << 0;      /* 产生一次更新事件,在中断里面处理脉冲输出 */
    GTIM_TIMX_NPWM->CR1 |= 1 << 0;      /* 使能定时器TIMX */
}

/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void GTIM_TIMX_NPWM_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_npwm_chy_handle);
}

/**
 * @brief       定时器更新中断回调函数
 * @param       htim:定时器句柄指针
 * @note        此函数会被定时器中断函数共同调用的
 * @retval      无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /**********************************输出指定个数PWM处理代码********************************/
    if (htim == (&g_timx_npwm_chy_handle)) /* 通用定时器输出指定个数PWM实验回调执行的内容 */
    {
        uint16_t npwm = 0;
        
        if (g_npwm_remain > 256)        /* 还有大于256个脉冲需要发送 */
        {
            g_npwm_remain=g_npwm_remain - 256;
            npwm = 256;
        }
        else if (g_npwm_remain % 256)   /* 还有位数（不到256）个脉冲要发送 */
        {
            npwm = g_npwm_remain % 256; 
            g_npwm_remain = 0;          /* 没有脉冲了 */
        }
        if (npwm)   /* 有脉冲要发送 */
        { 
            GTIM_TIMX_NPWM->RCR = npwm - 1; /* 设置重复计数寄存器值为npwm-1, 即npwm个脉冲 */
            GTIM_TIMX_NPWM->EGR |= 1 << 0;  /* 产生一次更新事件,以更新RCR寄存器 */
            GTIM_TIMX_NPWM->CR1 |= 1 << 0;  /* 使能定时器TIMX */
        }
        else
        { 
            GTIM_TIMX_NPWM->CR1 &= ~(1 << 0);   /* 关闭定时器TIMX */
        }
    }
}

/*********************************  高级定时器输出比较程序*************************************/

TIM_HandleTypeDef g_timx_comp_pwm_handle;                              /* 定时器x句柄 */

/**
 * @brief       高级定时器TIMX 输出比较模式 初始化函数（使用输出比较模式）
 * @note
 *              配置高级定时器TIMX 2路输出比较模式PWM输出,实现50%占空比,不同相位控制
 *              注意,本例程输出比较模式,每2个计数周期才能完成一个PWM输出,因此输出频率减半
 *              另外,我们还可以开启中断在中断里面修改CCRx,从而实现不同频率/不同相位的控制
 *              但是我们不推荐这么使用,因为这可能导致非常频繁的中断,从而占用大量CPU资源
 *
 *              高级定时器的时钟来自APB2,当APB2DIV≥2分频的时候
 *              高级定时器的时钟为APB2时钟的2倍, 而APB2为104.5M, 所以定时器时钟 = 209Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    atim_timx_comp_pwm_gpio_init();
    ATIM_TIMX_COMP_CLK_ENABLE();

    g_timx_comp_pwm_handle.Instance = ATIM_TIMX_COMP;                       /* 定时器1 */
    g_timx_comp_pwm_handle.Init.Prescaler = psc  ;                          /* 定时器分频 */
    g_timx_comp_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;           /* 向上计数模式 */
    g_timx_comp_pwm_handle.Init.Period = arr;                               /* 自动重装载值 */
    g_timx_comp_pwm_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;     /* 时钟分频因子 */
    g_timx_comp_pwm_handle.Init.RepetitionCounter = 0;
    g_timx_comp_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&g_timx_comp_pwm_handle);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&g_timx_comp_pwm_handle, &sClockSourceConfig);

    HAL_TIM_OC_Init(&g_timx_comp_pwm_handle);                               /*输出比较初始化TIMx */

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&g_timx_comp_pwm_handle, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;         /* 比较输出模式 */
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
 * @brief       定时器输出比较模式通道引脚初始化函数
 * @param       无
 * @note        此函数会被atim_timx_comp_pwm_init()函数调用
 * @retval      无
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

/*******************************互补输出带死区控制程序**************************************/

TIM_HandleTypeDef g_timx_cplm_pwm_handle;                              /* 定时器x句柄 */

/**
 * @brief       高级定时器TIMX 互补输出 初始化函数（使用PWM模式1）
 * @note
 *              配置高级定时器TIMX 互补输出, 一路OCy 一路OCyN, 并且可以设置死区时间
 *
 *              高级定时器的时钟来自APB2,当APB2DIV≥2分频的时候
 *              高级定时器的时钟为APB2时钟的2倍, 而APB2为104.5M, 所以定时器时钟 = 209Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    atim_timx_cplm_pwm_gpio_init();
    ATIM_TIMX_CPLM_CLK_ENABLE();

    g_timx_cplm_pwm_handle.Instance = TIM1;
    g_timx_cplm_pwm_handle.Init.Prescaler = psc;
    g_timx_cplm_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_cplm_pwm_handle.Init.Period = arr;
    g_timx_cplm_pwm_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    g_timx_cplm_pwm_handle.Init.RepetitionCounter = 0;
    g_timx_cplm_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&g_timx_cplm_pwm_handle);
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&g_timx_cplm_pwm_handle, &sClockSourceConfig);
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle) ;
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&g_timx_cplm_pwm_handle, &sMasterConfig);
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 300;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle, &sConfigOC, ATIM_TIMX_CPLM_CHY_CCRY);
    
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 100;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_LOW;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_LOW;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle, &sBreakDeadTimeConfig);

    HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle, ATIM_TIMX_CPLM_CHY_CCRY);
    HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle,ATIM_TIMX_CPLM_CHY_CCRY);
}

/**
 * @brief       定时器互补输出模式通道引脚初始化函数
 * @param       无
 * @note        此函数会被atim_timx_cplm_pwm_init()函数调用
 * @retval      无
 */
void atim_timx_cplm_pwm_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE();   /* 通道X对应IO口时钟使能 */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE();  /* 通道X互补通道对应IO口时钟使能 */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();  /* 通道X刹车输入对应IO口时钟使能 */
  
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP; 
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH ;
    gpio_init_struct.Alternate = ATIM_TIMX_CPLM_CHY_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
  
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN;
    gpio_init_struct.Alternate = ATIM_TIMX_CPLM_CHYN_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHYN_GPIO_PORT, &gpio_init_struct);
  
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    gpio_init_struct.Alternate = ATIM_TIMX_CPLM_BKIN_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_BKIN_GPIO_PORT, &gpio_init_struct);
}









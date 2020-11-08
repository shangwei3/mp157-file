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









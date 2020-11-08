/**
 ****************************************************************************************************
 * @file        dac.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-16
 * @brief       DAC 驱动代码
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
 * V1.0 20200516
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./BSP/DAC/dac.h"
#include "./SYSTEM/delay/delay.h"


DAC_HandleTypeDef g_dac_handle;           /* DAC句柄 */

/**
 * @brief       DAC初始化函数
 *   @note      本函数支持DAC1_OUT1/2通道初始化
 *              DAC的输入时钟来自APB1, 时钟频率=104.5Mhz=9.5ns
 *              DAC在输出buffer关闭的时候, 输出建立时间: tSETTLING = 2us (STM32MP1数据手册有写)
 *              因此DAC输出的最高速度约为:500Khz, 以10个点为一个周期, 最大能输出50Khz左右的波形
 *
 * @param       outx: 要初始化的通道. 1,通道1; 2,通道2
 * @retval      无
 */
void dac_init(uint32_t outx)
{
    DAC_ChannelConfTypeDef dac_ch_conf;     /* DAC1通道配置结构体 */
    
    g_dac_handle.Instance = DAC_DACX;
    HAL_DAC_Init(&g_dac_handle);                              /* 初始化DAC */
	
	dac_ch_conf.DAC_Trigger = DAC_TRIGGER_NONE;  /* 不使用触发功能 */
	dac_ch_conf.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_DISABLE;
	dac_ch_conf.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE; 	/* DAC采样保持关闭 */
	dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;		/* DAC输出缓冲关闭 */
	dac_ch_conf.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	dac_ch_conf.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
    HAL_DAC_ConfigChannel(&g_dac_handle, &dac_ch_conf, outx); /* DAC通道配置 */
    
    HAL_DAC_Start(&g_dac_handle, outx);  /* 开启DAC通道 */
}

/**
 * @brief       DAC底层驱动，时钟配置，引脚 配置
 * @param       hdac:DAC句柄
 * @note        此函数会被HAL_DAC_Init()调用
 * @retval      无
 */
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
    GPIO_InitTypeDef gpio_init_struct;

    DAC_DACX_CHY_CLK_ENABLE();             		/* 使能DAC时钟 */
    DAC_DACX_CHY_GPIO_CLK_ENABLE();             /* 开启GPIOA时钟 */

    gpio_init_struct.Pin = DAC_DACX_CHY_GPIO_PIN;        /* PA4 */
    gpio_init_struct.Mode = GPIO_MODE_ANALOG; /* 模拟 */
    gpio_init_struct.Pull = GPIO_NOPULL;      /* 不带上下拉 */
    HAL_GPIO_Init(DAC_DACX_CHY_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       设置通道1/2输出电压
 * @param       outx: 1,通道1; 2,通道2
 * @param       vol : 0~3300,代表0~3.3V
 * @retval      无
 */
void dac_set_voltage(uint16_t vol)
{
    double temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;

    HAL_DAC_SetValue(&g_dac_handle, DAC_DACX_CHY, DAC_ALIGN_12B_R, temp); /* 12位右对齐数据格式设置DAC值 */
}

/***************************************DAC输出三角波程序*****************************************/

/**
 * @brief       设置DAC_OUT1输出三角波
 *   @note      输出频率 ≈ 1000 / (dt * samples) Khz, 不过在dt较小的时候,比如小于5us时, 由于delay_us
 *              本身就不准了(调用函数,计算等都需要时间,延时很小的时候,这些时间会影响到延时), 频率会偏小.
 * 
 * @param       maxval : 最大值(0 < maxval < 4096), (maxval + 1)必须大于等于samples/2
 * @param       dt     : 每个采样点的延时时间(单位: us)
 * @param       samples: 采样点的个数, samples必须小于等于(maxval + 1) * 2 , 且maxval不能等于0
 * @param       n      : 输出波形个数,0~65535
 *
 * @retval      无
 */
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n)
{
    uint16_t i, j;
    float incval;           /* 递增量 */
    
    if((maxval + 1) <= samples)return ; /* 数据不合法 */
        
    incval = (maxval + 1) / (samples / 2);  /* 计算递增量 */
    
    for(j = 0; j < n; j++)
    { 
        DAC1->DHR12R1 = 0;  /* 先输出0 */
        for(i = 0; i < (samples / 2); i++)  /* 输出上升沿 */
        { 
             DAC1->DHR12R1 +=  incval;
             delay_us(dt);
        } 
        for(i = 0; i < (samples / 2); i++)  /* 输出下降沿 */
        {
             DAC1->DHR12R1 -=  incval;
             delay_us(dt);
        }
    }
}





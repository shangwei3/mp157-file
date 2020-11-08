/**
 ****************************************************************************************************
 * @file        pcf8563.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-21
 * @brief       PCF8563 驱动代码
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
 * V1.0 20200521
 * 第一次发布
 *
 ****************************************************************************************************
 */
 
#include "./BSP/PCF8563/pcf8563.h"
#include "./BSP/IIC/iic.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       初始化PCF8563
 * @param       无
 * @retval      0,初始化成功
 *				1,初始化失败
 */
uint8_t pcf8563_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
	
	iic4_init();			/* 初始化IIC 			*/
	   
    PCF8563_INT_GPIO_CLK_ENABLE();                           /* 中断引脚时钟使能 */
    
    gpio_init_struct.Pin = PCF8563_INT_GPIO_PIN;             /* RTC INT引脚 */
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下降沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* 上拉 */
    HAL_GPIO_Init(PCF8563_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0引脚初始化 */
    
    HAL_NVIC_SetPriority(PCF8563_INT_IRQn, 2, 1);          	/* 抢占优先级为2，子优先级为1 */
    HAL_NVIC_EnableIRQ(PCF8563_INT_IRQn);                  	/* 使能中断线1 */
		
	pcf8563_enable_alarm_int();		/* 打开闹钟中断 */
	pcf8563_clear_alarm_intflag();	/* 清除闹钟中断标志位 */
	return 0;
}

/**
 * @brief       BCD转十进制
 * @param       bcd:  要转换的bcd
 * @retval      转换后的十进制数据
 */
uint8_t bcd_to_dec(uint8_t bcd)
{
	return ((bcd >> 4) * 10 + (bcd & 0XF));
}
	
/**
 * @brief       十进制转BCD
 * @param       dec:  要转换的十进制数据
 * @retval      转换后的BCD数据
 */
uint8_t dec_to_bcd(uint8_t dec)
{
	return (((dec / 10) << 4) + (dec % 10));
}

/**
 * @brief       使能闹钟
 * @param       无
 * @retval      无
 */
void pcf8563_enable_alarm_int(void)
{
	uint8_t state;
	
	state = pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2);
	state |= 0X02;
	pcf8563_write_one_byte(PCF8563_CONTROL_STATUS2, state);
}

/**
 * @brief       清除闹钟中断标志位
 * @param       无
 * @retval      无
 */
void pcf8563_clear_alarm_intflag(void)
{
	uint8_t state;
	
	state = pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2);
	state &= ~0X08;
	
	pcf8563_write_one_byte(PCF8563_CONTROL_STATUS2, state);
}

/**
 * @brief       读取PCF8563时间值
 * @param       reg:  寄存器地址
 * @param       date: 读取到的数据
 * @retval      无
 */
void pcf8563_get_date(pcf8563_date *date)
{	
	uint8_t data[7];
	
	pcf8563_read_n_byte(PCF8563_SECONDS, 7, data);
	
	date->sec = bcd_to_dec(data[0] & 0x7f);
	date->min = bcd_to_dec(data[1] & 0x7f);
	date->hour = bcd_to_dec(data[2] & 0x3f);
	
	date->day = bcd_to_dec(data[3] & 0x3f);
	date->week = bcd_to_dec(data[4] & 0x7);
	date->month = bcd_to_dec(data[5] & 0x1f);
	date->year = 2000 + bcd_to_dec(data[6] & 0xff);
}

/**
 * @brief       设置PCF8563时间
 * @param       year:  年
 * @param       month：月
 * @param       day：  日
 * @param       hour： 时
 * @param       min：  分
 * @param       sec：  秒
 * @param       week: 星期，0~6分别对应星期天(0)~星期六(6)
 * @retval      无
 */
void pcf8563_set_date(uint16_t year, uint8_t month, uint8_t day, \
	                uint8_t hour, uint8_t min, uint8_t sec, uint8_t week)
{
	if(year < 2000)
		year = 2000;
	else if(year > 2099)
		year = 2099;
	
	pcf8563_write_one_byte(PCF8563_YEARS, dec_to_bcd(year - 2000));
	pcf8563_write_one_byte(PCF8563_MONTHS, dec_to_bcd(month));
	pcf8563_write_one_byte(PCF8563_DAYS, dec_to_bcd(day));
	
	pcf8563_write_one_byte(PCF8563_HOURS, dec_to_bcd(hour));
	pcf8563_write_one_byte(PCF8563_MINUTES, dec_to_bcd(min));
	pcf8563_write_one_byte(PCF8563_SECONDS, dec_to_bcd(sec));
	
	pcf8563_write_one_byte(PCF8563_WEEKDAYS, dec_to_bcd(week));
}

/**
 * @brief       设置闹钟
 * @param       day：  日
 * @param       hour： 时
 * @param       min：  分
 * @retval      无
 */
void pcf8563_set_alarm( uint8_t day, uint8_t hour, uint8_t min)
{
	pcf8563_write_one_byte(PCF8563_MINUTE_ALARM, dec_to_bcd(min));
	pcf8563_write_one_byte(PCF8563_HOUR_ALARM, dec_to_bcd(hour));
	pcf8563_write_one_byte(PCF8563_DAY_ALARM, dec_to_bcd(day));
}

/**
 * @brief       设置闹钟，星期
 * @param       day：  日
 * @param       hour： 时
 * @param       min：  分
 * @retval      无
 */
void pcf8563_set_alarm_week( uint8_t week)
{
	pcf8563_write_one_byte(PCF8563_WEEKDAY_ALARM, dec_to_bcd(week));
}


/**
 * @brief       向PCF8563指定寄存器写一个字节  
 * @param       reg:  寄存器地址
 * @param       data: 要写入的数据
 * @retval      无
 */
void pcf8563_write_one_byte(uint8_t reg,uint8_t data)
{
	uint8_t senddata[2];
	
	senddata[0] = reg;  /* 寄存器地址 */
	senddata[1] = data;	/* 要写的数据 */
	
	INTX_DISABLE();		/* I2C通信的时候,关闭中断，防止干扰 */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, senddata, 2, 1000);
	
}

/**
 * @brief       读取PCF8563指定寄存器数据  
 * @param       reg:  寄存器地址
 * @retval      读到的数据
 */
uint8_t pcf8563_read_one_byte(uint8_t reg)
{
	uint8_t res;
	uint8_t senddata;
	
	/* 1、先发送要读取的寄存器地址 */
	senddata = reg;  /* 寄存器地址 */
	INTX_DISABLE();		/* I2C通信的时候,关闭中断，防止干扰 */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, &senddata, 1, 1000);
	
	/* 2、读取数据 */;
	HAL_I2C_Master_Receive(&g_i2c4_handle, PCF8563_ADDR, &res, 1, 1000);
	INTX_ENABLE();		/* I2C通信完成，打开中断 */
    return res;  
}

/**
 * @brief       连续读取PCF8563多个寄存器数据
 * @param       reg:  要读取的起始寄存器
 * @param		num:  要读取的数据量
 * @param		data: 读取到的数据存储地址
 * @retval      读到的数据
 */
void pcf8563_read_n_byte(uint8_t reg, uint8_t num, uint8_t *data)
{
	uint8_t senddata;
	
	/* 1、先发送要读取的寄存器地址 */
	senddata = reg;  /* 寄存器地址 */
	INTX_DISABLE();		/* I2C通信的时候,关闭中断，防止干扰 */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, &senddata, 1, 1000);
	
	/* 2、读取数据 */;
	HAL_I2C_Master_Receive(&g_i2c4_handle, PCF8563_ADDR, data, num, 1000);
	INTX_ENABLE();		/* I2C通信完成，打开中断 */
}

/**
 * @brief       外部中断服务程序
 * @param       无
 * @retval      无
 */
void PCF8563_INT_IRQHandler(void)
{
	/* 调用中断处理公用函数,RTC INT引脚中断*/
	HAL_GPIO_EXTI_IRQHandler(PCF8563_INT_GPIO_PIN); 
}

/**
 * @brief       GPIO下降沿回调函数
 * @param       GPIO_Pin: 中断引脚号
 * @note        在HAL库中所有的外部中断服务函数都会调用此函数
 * @retval      无
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{     
    if (GPIO_Pin == PCF8563_INT_GPIO_PIN)     /* RTC INT */
    {
		/* ALARM中断 */
		if(pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2) & 0x08)
		{
			printf("rtc alarm!\r\n");
			pcf8563_clear_alarm_intflag();
		}
    }
}



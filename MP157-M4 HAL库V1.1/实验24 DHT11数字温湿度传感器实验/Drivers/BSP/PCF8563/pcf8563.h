/**
 ****************************************************************************************************
 * @file        pcf8563.h
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
#ifndef __PCF8563_H
#define __PCF8563_H
#include "./SYSTEM/sys/sys.h"


/* PCF8563中断引脚 */
#define PCF8563_INT_GPIO_PORT              GPIOI
#define PCF8563_INT_GPIO_PIN               GPIO_PIN_3
#define PCF8563_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)   /* PG口时钟使能 */
#define PCF8563_INT_IRQn             		EXTI3_IRQn
#define PCF8563_INT_IRQHandler       		EXTI3_IRQHandler

#define PCF8563_ADDR    0XA2	/* PCF8563器件IIC地址(左移了一位) */

/* PCF8563寄存器地址，一共16个8位寄存器 */
#define PCF8563_CONTROL_STATUS1		0X00
#define PCF8563_CONTROL_STATUS2		0X01
#define PCF8563_SECONDS				0X02
#define PCF8563_MINUTES				0X03
#define PCF8563_HOURS				0X04
#define PCF8563_DAYS				0X05
#define PCF8563_WEEKDAYS			0X06
#define PCF8563_MONTHS				0X07
#define PCF8563_YEARS				0X08
#define PCF8563_MINUTE_ALARM		0X09
#define	PCF8563_HOUR_ALARM			0X0A
#define PCF8563_DAY_ALARM			0X0B
#define PCF8563_WEEKDAY_ALARM		0X0C
#define PCF8563_CLKOUT_CONTROL		0X0D
#define PCF8563_TIMER_CONTROL		0X0E
#define PCF8563_TIMER				0X0F

/* 内部定时器时钟源 */
#define PCF8563_TIMER_4096HZ		0x00
#define PCF8563_TIMER_64HZ			0X01
#define PCF8563_TIMER_1HZ			0X02
#define PCF8563_TIMER_1_60HZ		0X03

typedef struct pcf8563_date_structure{
	uint8_t	sec;		/* 秒 	*/
	uint8_t	min;		/* 分钟 */
	uint8_t	hour;		/* 小时 */
	uint8_t	day;		/* 日 	*/
	uint8_t	month;		/* 月 	*/
	uint16_t year;		/* 年 	*/
	uint8_t	week;		/* 星期0~6,0为星期天，1~6分别为星期一到六	*/
}pcf8563_date;

uint8_t pcf8563_init(void);
uint8_t bcd_to_dec(uint8_t bcd);
uint8_t dec_to_bcd(uint8_t dec);
void pcf8563_write_one_byte(uint8_t reg,uint8_t data);
uint8_t pcf8563_read_one_byte(uint8_t reg);
void pcf8563_read_n_byte(uint8_t reg, uint8_t num, uint8_t *data);
void pcf8563_get_date(pcf8563_date *date);
void pcf8563_enable_alarm_int(void);
void pcf8563_clear_alarm_intflag(void);
void pcf8563_set_alarm( uint8_t day, uint8_t hour, uint8_t min);
void pcf8563_set_alarm_week( uint8_t week);
void pcf8563_set_date(uint16_t year, uint8_t month, uint8_t day, \
	                uint8_t hour, uint8_t min, uint8_t sec, uint8_t week);
#endif

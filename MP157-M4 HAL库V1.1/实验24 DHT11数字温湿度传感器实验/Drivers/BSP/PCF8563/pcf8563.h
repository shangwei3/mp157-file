/**
 ****************************************************************************************************
 * @file        pcf8563.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-21
 * @brief       PCF8563 ��������
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
 * V1.0 20200521
 * ��һ�η���
 *
 ****************************************************************************************************
 */
#ifndef __PCF8563_H
#define __PCF8563_H
#include "./SYSTEM/sys/sys.h"


/* PCF8563�ж����� */
#define PCF8563_INT_GPIO_PORT              GPIOI
#define PCF8563_INT_GPIO_PIN               GPIO_PIN_3
#define PCF8563_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)   /* PG��ʱ��ʹ�� */
#define PCF8563_INT_IRQn             		EXTI3_IRQn
#define PCF8563_INT_IRQHandler       		EXTI3_IRQHandler

#define PCF8563_ADDR    0XA2	/* PCF8563����IIC��ַ(������һλ) */

/* PCF8563�Ĵ�����ַ��һ��16��8λ�Ĵ��� */
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

/* �ڲ���ʱ��ʱ��Դ */
#define PCF8563_TIMER_4096HZ		0x00
#define PCF8563_TIMER_64HZ			0X01
#define PCF8563_TIMER_1HZ			0X02
#define PCF8563_TIMER_1_60HZ		0X03

typedef struct pcf8563_date_structure{
	uint8_t	sec;		/* �� 	*/
	uint8_t	min;		/* ���� */
	uint8_t	hour;		/* Сʱ */
	uint8_t	day;		/* �� 	*/
	uint8_t	month;		/* �� 	*/
	uint16_t year;		/* �� 	*/
	uint8_t	week;		/* ����0~6,0Ϊ�����죬1~6�ֱ�Ϊ����һ����	*/
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

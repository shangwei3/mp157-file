/**
 ****************************************************************************************************
 * @file        pcf8563.c
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
 
#include "./BSP/PCF8563/pcf8563.h"
#include "./BSP/IIC/iic.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       ��ʼ��PCF8563
 * @param       ��
 * @retval      0,��ʼ���ɹ�
 *				1,��ʼ��ʧ��
 */
uint8_t pcf8563_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
	
	iic4_init();			/* ��ʼ��IIC 			*/
	   
    PCF8563_INT_GPIO_CLK_ENABLE();                           /* �ж�����ʱ��ʹ�� */
    
    gpio_init_struct.Pin = PCF8563_INT_GPIO_PIN;             /* RTC INT���� */
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* ���� */
    HAL_GPIO_Init(PCF8563_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0���ų�ʼ�� */
    
    HAL_NVIC_SetPriority(PCF8563_INT_IRQn, 2, 1);          	/* ��ռ���ȼ�Ϊ2�������ȼ�Ϊ1 */
    HAL_NVIC_EnableIRQ(PCF8563_INT_IRQn);                  	/* ʹ���ж���1 */
		
	pcf8563_enable_alarm_int();		/* �������ж� */
	pcf8563_clear_alarm_intflag();	/* ��������жϱ�־λ */
	return 0;
}

/**
 * @brief       BCDתʮ����
 * @param       bcd:  Ҫת����bcd
 * @retval      ת�����ʮ��������
 */
uint8_t bcd_to_dec(uint8_t bcd)
{
	return ((bcd >> 4) * 10 + (bcd & 0XF));
}
	
/**
 * @brief       ʮ����תBCD
 * @param       dec:  Ҫת����ʮ��������
 * @retval      ת�����BCD����
 */
uint8_t dec_to_bcd(uint8_t dec)
{
	return (((dec / 10) << 4) + (dec % 10));
}

/**
 * @brief       ʹ������
 * @param       ��
 * @retval      ��
 */
void pcf8563_enable_alarm_int(void)
{
	uint8_t state;
	
	state = pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2);
	state |= 0X02;
	pcf8563_write_one_byte(PCF8563_CONTROL_STATUS2, state);
}

/**
 * @brief       ��������жϱ�־λ
 * @param       ��
 * @retval      ��
 */
void pcf8563_clear_alarm_intflag(void)
{
	uint8_t state;
	
	state = pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2);
	state &= ~0X08;
	
	pcf8563_write_one_byte(PCF8563_CONTROL_STATUS2, state);
}

/**
 * @brief       ��ȡPCF8563ʱ��ֵ
 * @param       reg:  �Ĵ�����ַ
 * @param       date: ��ȡ��������
 * @retval      ��
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
 * @brief       ����PCF8563ʱ��
 * @param       year:  ��
 * @param       month����
 * @param       day��  ��
 * @param       hour�� ʱ
 * @param       min��  ��
 * @param       sec��  ��
 * @param       week: ���ڣ�0~6�ֱ��Ӧ������(0)~������(6)
 * @retval      ��
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
 * @brief       ��������
 * @param       day��  ��
 * @param       hour�� ʱ
 * @param       min��  ��
 * @retval      ��
 */
void pcf8563_set_alarm( uint8_t day, uint8_t hour, uint8_t min)
{
	pcf8563_write_one_byte(PCF8563_MINUTE_ALARM, dec_to_bcd(min));
	pcf8563_write_one_byte(PCF8563_HOUR_ALARM, dec_to_bcd(hour));
	pcf8563_write_one_byte(PCF8563_DAY_ALARM, dec_to_bcd(day));
}

/**
 * @brief       �������ӣ�����
 * @param       day��  ��
 * @param       hour�� ʱ
 * @param       min��  ��
 * @retval      ��
 */
void pcf8563_set_alarm_week( uint8_t week)
{
	pcf8563_write_one_byte(PCF8563_WEEKDAY_ALARM, dec_to_bcd(week));
}


/**
 * @brief       ��PCF8563ָ���Ĵ���дһ���ֽ�  
 * @param       reg:  �Ĵ�����ַ
 * @param       data: Ҫд�������
 * @retval      ��
 */
void pcf8563_write_one_byte(uint8_t reg,uint8_t data)
{
	uint8_t senddata[2];
	
	senddata[0] = reg;  /* �Ĵ�����ַ */
	senddata[1] = data;	/* Ҫд������ */
	
	INTX_DISABLE();		/* I2Cͨ�ŵ�ʱ��,�ر��жϣ���ֹ���� */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, senddata, 2, 1000);
	
}

/**
 * @brief       ��ȡPCF8563ָ���Ĵ�������  
 * @param       reg:  �Ĵ�����ַ
 * @retval      ����������
 */
uint8_t pcf8563_read_one_byte(uint8_t reg)
{
	uint8_t res;
	uint8_t senddata;
	
	/* 1���ȷ���Ҫ��ȡ�ļĴ�����ַ */
	senddata = reg;  /* �Ĵ�����ַ */
	INTX_DISABLE();		/* I2Cͨ�ŵ�ʱ��,�ر��жϣ���ֹ���� */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, &senddata, 1, 1000);
	
	/* 2����ȡ���� */;
	HAL_I2C_Master_Receive(&g_i2c4_handle, PCF8563_ADDR, &res, 1, 1000);
	INTX_ENABLE();		/* I2Cͨ����ɣ����ж� */
    return res;  
}

/**
 * @brief       ������ȡPCF8563����Ĵ�������
 * @param       reg:  Ҫ��ȡ����ʼ�Ĵ���
 * @param		num:  Ҫ��ȡ��������
 * @param		data: ��ȡ�������ݴ洢��ַ
 * @retval      ����������
 */
void pcf8563_read_n_byte(uint8_t reg, uint8_t num, uint8_t *data)
{
	uint8_t senddata;
	
	/* 1���ȷ���Ҫ��ȡ�ļĴ�����ַ */
	senddata = reg;  /* �Ĵ�����ַ */
	INTX_DISABLE();		/* I2Cͨ�ŵ�ʱ��,�ر��жϣ���ֹ���� */
	HAL_I2C_Master_Transmit(&g_i2c4_handle, PCF8563_ADDR, &senddata, 1, 1000);
	
	/* 2����ȡ���� */;
	HAL_I2C_Master_Receive(&g_i2c4_handle, PCF8563_ADDR, data, num, 1000);
	INTX_ENABLE();		/* I2Cͨ����ɣ����ж� */
}

/**
 * @brief       �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void PCF8563_INT_IRQHandler(void)
{
	/* �����жϴ����ú���,RTC INT�����ж�*/
	HAL_GPIO_EXTI_IRQHandler(PCF8563_INT_GPIO_PIN); 
}

/**
 * @brief       GPIO�½��ػص�����
 * @param       GPIO_Pin: �ж����ź�
 * @note        ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @retval      ��
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{     
    if (GPIO_Pin == PCF8563_INT_GPIO_PIN)     /* RTC INT */
    {
		/* ALARM�ж� */
		if(pcf8563_read_one_byte(PCF8563_CONTROL_STATUS2) & 0x08)
		{
			printf("rtc alarm!\r\n");
			pcf8563_clear_alarm_intflag();
		}
    }
}



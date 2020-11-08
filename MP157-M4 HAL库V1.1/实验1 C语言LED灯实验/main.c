/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ��Linux�Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       C���Ե�� ʵ��
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
 ****************************************************************************************************
 */

#include "main.h"

/**
 * @brief     ʹ�����ʱ��
 * @param     ��
 * @retval    ��
 */ 
void clk_enable(void)
{
	RCC_MC_AHB4ENSETR |= ((unsigned int)1 << 8);	/* ʹ��GPIOIʱ�� */
	RCC_MC_AHB4ENSETR |= ((unsigned int)1 << 5);	/* ʹ��GPIOFʱ�� */
}

/**
 * @brief     ��ʼ��GPIO
 * @param     ��
 * @retval    ��
 */ 
void gpio_init(void)
{
	/* GPIOI_0����Ϊ��� */
	GPIOI_MODER &= ~((unsigned int)3 << (2 * 0));
	GPIOI_MODER |= ((unsigned int)1 << (2 * 0));
	
	/* GPIOI_0����Ϊ����ģʽ */
	GPIOI_OTYPER &= ~((unsigned int)1 << 0);
	
	/* GPIOI_0����Ϊ����ģʽ */
	GPIOI_OSPEEDR &= ~((unsigned int)3 << (2 * 0));
	GPIOI_OSPEEDR |= ((unsigned int)2 << (2 * 0));
	
	/* GPIOI_0����Ϊ���� */
	GPIOI_PUPDR &= ~((unsigned int)3 << (2 * 0));
	GPIOI_PUPDR |= ((unsigned int)1 << (2 * 0));
	
	/* GPIOF_3����Ϊ��� */
	GPIOF_MODER &= ~((unsigned int)3 << (2 * 3));
	GPIOF_MODER |= ((unsigned int)1 << (2 * 3));
	
	/* GPIOF_3����Ϊ����ģʽ */
	GPIOF_OTYPER &= ~((unsigned int)1 << 3);
	
	/* GPIOF_3����Ϊ����ģʽ */
	GPIOF_OSPEEDR &= ~((unsigned int)3 << (2 * 3));
	GPIOF_OSPEEDR |= ((unsigned int)2 << (2 * 3));
	
	/* GPIOF_3����Ϊ���� */
	GPIOF_PUPDR &= ~((unsigned int)3 << (2 * 3));
	GPIOF_PUPDR |= ((unsigned int)1 << (2 * 3));
}

/**
 * @brief     LED0���غ���
 * @param     ��
 * @retval    ��
 */ 
void led0_switch(unsigned char state)
{
	if(state == OFF) 
	{
		GPIOI_BSRR |= ((unsigned int)1 << 0); 	/* GPIOI_0����ߵ�ƽ */
	} else if(state == ON) 
	{
		GPIOI_BSRR |= ((unsigned int)1 << 16); 	/* GPIOI_0����͵�ƽ */
	}
}

/**
 * @brief     LED1���غ���
 * @param     ��
 * @retval    ��
 */ 
void led1_switch(unsigned char state)
{
	if(state == OFF) 
	{
		GPIOF_BSRR |= ((unsigned int)1 << 3); 	/* GPIOF_3����ߵ�ƽ */
	} else if(state == ON) 
	{
		GPIOF_BSRR |= ((unsigned int)1 << 19); 	/* GPIOF_3����͵�ƽ */
	}
}

/**
 * @brief		��ʱ����ʱ����
 * @param - n	Ҫ��ʱѭ������(�ղ���ѭ��������ģʽ��ʱ)
 * @retval 		��
 */
void delay_short(volatile unsigned int n)
{
	while(n--){}
}

/**
 * @brief		����ʱ����
 * @param - n	Ҫ��ʱ��ʱ��ѭ����
 * @retval 		��
 */
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7fff);
	}
}

/**
 * @brief		main����
 * @param		��
 * @retval 		��
 */
int main(void)
{
	clk_enable();	/* ʹ��ʱ�� 	*/
	gpio_init();	/* ��ʼ��GPIO 	*/
	
	while(1) 
	{
		led0_switch(ON);
		led1_switch(OFF);
		delay(100);
		led0_switch(OFF);
		led1_switch(ON);
		delay(100);
	}	
}
 

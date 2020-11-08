/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ��Linux�Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       ʹ�ýṹ�嶨������ ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32MP1������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv
 .com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "main.h"

/* LED�����Ŷ��� */
#define LED0_PORT		GPIOI
#define LED0_PIN		0
#define LED1_PORT		GPIOF
#define LED1_PIN		3

/**
 * @brief     ʹ�����ʱ��
 * @param     ��
 * @retval    ��
 */ 
void clk_enable(void)
{
	RCC->MC_AHB4ENSETR |= ((unsigned int)1 << 4);	/* ʹ��GPIOEʱ�� */
	RCC->MC_AHB4ENSETR |= ((unsigned int)1 << 7);	/* ʹ��GPIOHʱ�� */
}

/**
 * @brief     ��ʼ��GPIOΪ���ģʽ
 * @param     ��
 * @retval    ��
 */ 
void gpio_init(GPIO_TypeDef  *GPIOx, unsigned char pin)
{
	/* ����Ϊ��� */
	GPIOx->MODER &= ~((unsigned int)3 << (2 * pin));
	GPIOx->MODER |= ((unsigned int)1 << (2 * pin));
	
	/* ����Ϊ����ģʽ */
	GPIOx->OTYPER &= ~(1 << 15);
	
	/* ����Ϊ����ģʽ */
	GPIOx->OSPEEDR &= ~((unsigned int)3 << (2 * pin));
	GPIOx->OSPEEDR |= ((unsigned int)2 << (2 * pin));
	
	/* ����Ϊ���� */
	GPIOx->PUPDR &= ((unsigned int)3 << (2 * pin));
	GPIOx->PUPDR |= ((unsigned int)1 << (2 * pin));
}


/**
 * @brief     LED0���غ���
 * @param     ��
 * @retval    ��
 */ 
void pin_write(GPIO_TypeDef *GPIOx, unsigned char pin, unsigned char state)
{
	if(state == SET) 
	{
		GPIOx->BSRR |= ((unsigned int)1 << pin);			/* ����ߵ�ƽ */
	} else if(state == RESET) 
	{
		GPIOx->BSRR |= ((unsigned int)1 << (15 + pin + 1));	/* ����͵�ƽ */
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
	clk_enable();					/* ʹ��ʱ�� 	*/
	gpio_init(LED0_PORT, LED0_PIN);	/* ��ʼ��LED0 	*/
	gpio_init(LED1_PORT, LED1_PIN);	/* ��ʼ��LED1 	*/
	
	while(1) 
	{
		pin_write(LED0_PORT, LED0_PIN, RESET);	/* LED0�͵�ƽ�� */
		pin_write(LED1_PORT, LED1_PIN, SET);	/* LED1�ߵ�ƽ�ر� */			
		delay(100);
		pin_write(LED0_PORT, LED0_PIN, SET);	/* LED0�ߵ�ƽ�ر� */
		pin_write(LED1_PORT, LED1_PIN, RESET);	/* LED1�͵�ƽ�� */
		delay(100);
	}	
}
 

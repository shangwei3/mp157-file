/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子Linux团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       使用结构体定义外设 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32MP1开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv
 .com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "main.h"

/* LED灯引脚定义 */
#define LED0_PORT		GPIOI
#define LED0_PIN		0
#define LED1_PORT		GPIOF
#define LED1_PIN		3

/**
 * @brief     使能相关时钟
 * @param     无
 * @retval    无
 */ 
void clk_enable(void)
{
	RCC->MC_AHB4ENSETR |= ((unsigned int)1 << 4);	/* 使能GPIOE时钟 */
	RCC->MC_AHB4ENSETR |= ((unsigned int)1 << 7);	/* 使能GPIOH时钟 */
}

/**
 * @brief     初始化GPIO为输出模式
 * @param     无
 * @retval    无
 */ 
void gpio_init(GPIO_TypeDef  *GPIOx, unsigned char pin)
{
	/* 设置为输出 */
	GPIOx->MODER &= ~((unsigned int)3 << (2 * pin));
	GPIOx->MODER |= ((unsigned int)1 << (2 * pin));
	
	/* 设置为推完模式 */
	GPIOx->OTYPER &= ~(1 << 15);
	
	/* 设置为高速模式 */
	GPIOx->OSPEEDR &= ~((unsigned int)3 << (2 * pin));
	GPIOx->OSPEEDR |= ((unsigned int)2 << (2 * pin));
	
	/* 设置为上拉 */
	GPIOx->PUPDR &= ((unsigned int)3 << (2 * pin));
	GPIOx->PUPDR |= ((unsigned int)1 << (2 * pin));
}


/**
 * @brief     LED0开关函数
 * @param     无
 * @retval    无
 */ 
void pin_write(GPIO_TypeDef *GPIOx, unsigned char pin, unsigned char state)
{
	if(state == SET) 
	{
		GPIOx->BSRR |= ((unsigned int)1 << pin);			/* 输出高电平 */
	} else if(state == RESET) 
	{
		GPIOx->BSRR |= ((unsigned int)1 << (15 + pin + 1));	/* 输出低电平 */
	}
}
	
/**
 * @brief		短时间延时函数
 * @param - n	要延时循环次数(空操作循环次数，模式延时)
 * @retval 		无
 */
void delay_short(volatile unsigned int n)
{
	while(n--){}
}

/**
 * @brief		长延时函数
 * @param - n	要延时的时间循环数
 * @retval 		无
 */
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7fff);
	}
}

/**
 * @brief		main函数
 * @param		无
 * @retval 		无
 */
int main(void)
{
	clk_enable();					/* 使能时钟 	*/
	gpio_init(LED0_PORT, LED0_PIN);	/* 初始化LED0 	*/
	gpio_init(LED1_PORT, LED1_PIN);	/* 初始化LED1 	*/
	
	while(1) 
	{
		pin_write(LED0_PORT, LED0_PIN, RESET);	/* LED0低电平打开 */
		pin_write(LED1_PORT, LED1_PIN, SET);	/* LED1高电平关闭 */			
		delay(100);
		pin_write(LED0_PORT, LED0_PIN, SET);	/* LED0高电平关闭 */
		pin_write(LED1_PORT, LED1_PIN, RESET);	/* LED1低电平打开 */
		delay(100);
	}	
}
 

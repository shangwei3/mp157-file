/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子Linux团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       C语言点灯 实验
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
 ****************************************************************************************************
 */

#include "main.h"

/**
 * @brief     使能相关时钟
 * @param     无
 * @retval    无
 */ 
void clk_enable(void)
{
	RCC_MC_AHB4ENSETR |= ((unsigned int)1 << 8);	/* 使能GPIOI时钟 */
	RCC_MC_AHB4ENSETR |= ((unsigned int)1 << 5);	/* 使能GPIOF时钟 */
}

/**
 * @brief     初始化GPIO
 * @param     无
 * @retval    无
 */ 
void gpio_init(void)
{
	/* GPIOI_0设置为输出 */
	GPIOI_MODER &= ~((unsigned int)3 << (2 * 0));
	GPIOI_MODER |= ((unsigned int)1 << (2 * 0));
	
	/* GPIOI_0设置为推完模式 */
	GPIOI_OTYPER &= ~((unsigned int)1 << 0);
	
	/* GPIOI_0设置为高速模式 */
	GPIOI_OSPEEDR &= ~((unsigned int)3 << (2 * 0));
	GPIOI_OSPEEDR |= ((unsigned int)2 << (2 * 0));
	
	/* GPIOI_0设置为上拉 */
	GPIOI_PUPDR &= ~((unsigned int)3 << (2 * 0));
	GPIOI_PUPDR |= ((unsigned int)1 << (2 * 0));
	
	/* GPIOF_3设置为输出 */
	GPIOF_MODER &= ~((unsigned int)3 << (2 * 3));
	GPIOF_MODER |= ((unsigned int)1 << (2 * 3));
	
	/* GPIOF_3设置为推完模式 */
	GPIOF_OTYPER &= ~((unsigned int)1 << 3);
	
	/* GPIOF_3设置为高速模式 */
	GPIOF_OSPEEDR &= ~((unsigned int)3 << (2 * 3));
	GPIOF_OSPEEDR |= ((unsigned int)2 << (2 * 3));
	
	/* GPIOF_3设置为上拉 */
	GPIOF_PUPDR &= ~((unsigned int)3 << (2 * 3));
	GPIOF_PUPDR |= ((unsigned int)1 << (2 * 3));
}

/**
 * @brief     LED0开关函数
 * @param     无
 * @retval    无
 */ 
void led0_switch(unsigned char state)
{
	if(state == OFF) 
	{
		GPIOI_BSRR |= ((unsigned int)1 << 0); 	/* GPIOI_0输出高电平 */
	} else if(state == ON) 
	{
		GPIOI_BSRR |= ((unsigned int)1 << 16); 	/* GPIOI_0输出低电平 */
	}
}

/**
 * @brief     LED1开关函数
 * @param     无
 * @retval    无
 */ 
void led1_switch(unsigned char state)
{
	if(state == OFF) 
	{
		GPIOF_BSRR |= ((unsigned int)1 << 3); 	/* GPIOF_3输出高电平 */
	} else if(state == ON) 
	{
		GPIOF_BSRR |= ((unsigned int)1 << 19); 	/* GPIOF_3输出低电平 */
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
	clk_enable();	/* 使能时钟 	*/
	gpio_init();	/* 初始化GPIO 	*/
	
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
 

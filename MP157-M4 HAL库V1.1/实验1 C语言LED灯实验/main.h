/**
 ****************************************************************************************************
 * @file        main.h
 * @author      ����ԭ��Linux�Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       ����һЩ�Ĵ�����ַ��Ϣ
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32MP15X������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200503
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __MAIN_H
#define __MAIN_H

/* 
 * �����������ַ 
 */
#define PERIPH_BASE				(0x40000000)
#define MCU_AHB4_PERIPH_BASE  	(PERIPH_BASE + 0x10000000)
#define RCC_BASE        		(MCU_AHB4_PERIPH_BASE + 0x0000)	
#define GPIOI_BASE      		(MCU_AHB4_PERIPH_BASE + 0xA000)	
#define GPIOF_BASE      		(MCU_AHB4_PERIPH_BASE + 0x7000)	

/* 
 * �Ĵ�����ַ 
 */
#define RCC_MC_AHB4ENSETR		*((volatile unsigned int *)(RCC_BASE + 0XAA8))
#define GPIOI_MODER      		*((volatile unsigned int *)(GPIOI_BASE + 0x0000))	
#define GPIOI_OTYPER      		*((volatile unsigned int *)(GPIOI_BASE + 0x0004))	
#define GPIOI_OSPEEDR      		*((volatile unsigned int *)(GPIOI_BASE + 0x0008))	
#define GPIOI_PUPDR      		*((volatile unsigned int *)(GPIOI_BASE + 0x000C))	
#define GPIOI_BSRR      		*((volatile unsigned int *)(GPIOI_BASE + 0x0018))

#define GPIOF_MODER      		*((volatile unsigned int *)(GPIOF_BASE + 0x0000))	
#define GPIOF_OTYPER      		*((volatile unsigned int *)(GPIOF_BASE + 0x0004))	
#define GPIOF_OSPEEDR      		*((volatile unsigned int *)(GPIOF_BASE + 0x0008))	
#define GPIOF_PUPDR      		*((volatile unsigned int *)(GPIOF_BASE + 0x000C))	
#define GPIOF_BSRR      		*((volatile unsigned int *)(GPIOF_BASE + 0x0018))


#define OFF 	0
#define ON 		1

#endif


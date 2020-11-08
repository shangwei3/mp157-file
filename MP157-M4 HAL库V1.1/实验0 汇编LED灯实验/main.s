;******************************************************************************
;* @file			: main.s
;* @author         	: 正点原子Linux团队
;* @version     	: V1.0
;* @date         	: 2020-05-03
;* @description     : MP157开发板M4裸机例程main汇编文件
;*                    本文件功能:
;*                    - 定义所要使用的寄存器
;*                    - Start函数编写，复位中断函数Reset_Handler会执行Start函数
;*                    - 使能GPIOI时钟，初始化GPIOI_0这个IO为推挽输出
;*                    - 循环里面周期性的点亮/熄灭LED0
;* @license     	: Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
;****************************************************************************** 

PERIPH_BASE     		EQU     (0x40000000)
MCU_AHB4_PERIPH_BASE  	EQU    	(PERIPH_BASE + 0x10000000)
RCC_BASE        		EQU    	(MCU_AHB4_PERIPH_BASE + 0x0000)	
RCC_MC_AHB4ENSETR		EQU		(RCC_BASE + 0XAA8)
GPIOI_BASE      		EQU     (MCU_AHB4_PERIPH_BASE + 0xA000)	
GPIOI_MODER      		EQU     (GPIOI_BASE + 0x0000)	
GPIOI_OTYPER      		EQU     (GPIOI_BASE + 0x0004)	
GPIOI_OSPEEDR      		EQU     (GPIOI_BASE + 0x0008)	
GPIOI_PUPDR      		EQU     (GPIOI_BASE + 0x000C)	
GPIOI_BSRR      		EQU     (GPIOI_BASE + 0x0018)	
	
        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT  Start
			
Start
	;1、设置RCC_MC_AHB4ENSETR寄存器，使能GPIOI时钟
	LDR		R0,	=RCC_MC_AHB4ENSETR
	LDR		R1, [R0]				;读取RCC_MC_AHB4ENSETR寄存器的值到R1
	ORR		R1, #(1 << 8)			;bit4置1,使能GPIOI时钟
	STR		R1,	[R0]				;写入到RCC_MC_AHB4ENSETR寄存器
	
	;2、GPIOI_MODER寄存器，设置GPIOI_0输出模式
	LDR		R0,	=GPIOI_MODER
	LDR		R1, [R0]				;读取GPIOI_MODER寄存器的值到R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0清零
	ORR		R1, #(1 << (2 * 0))		;bit1:0设置为01
	STR		R1,	[R0]				;写入到GPIOI_MODER寄存器
	
	;3、GPIOI_OTYPER寄存器，设置GPIOI_0为推挽模式
	LDR		R0,	=GPIOI_OTYPER		
	LDR		R1, [R0]				;读取GPIOI_OTYPER寄存器值到R1
	BIC		R1, #(1 << 0)			;bit0清零,设置为上拉
	STR		R1,	[R0]				;写入到GPIOI_OTYPER寄存器	
	
	;4、GPIOI_OSPEEDR寄存器，设置GPIOI_0为高速
	LDR		R0,	=GPIOI_OSPEEDR
	LDR		R1, [R0]				;读取GPIOI_OSPEEDR寄存器的值到R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0清零
	ORR		R1, #(2 << (2 * 0))		;bit1:0设置为10
	STR		R1,	[R0]				;写入到GPIOI_OSPEEDR寄存器	
	
	;5、GPIOI_PUPDR寄存器，设置GPIOI_0上拉
	LDR		R0,	=GPIOI_PUPDR
	LDR		R1, [R0]				;读取GPIOI_PUPDR寄存器的值到R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0清零
	ORR		R1, #(1 << (2 * 0))		;bit1:0设置为01
	STR		R1,	[R0]				;写入到GPIOI_PUPDR寄存器	
	
	;6、GPIOI_BSRR寄存器，设置GPIOI_0为低，点亮LED0
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;读取GPIOI_BSRR寄存器的值到R1
	ORR		R1, #(1 << 16)			;bit16设置为0
	STR		R1,	[R0]				;写入到GPIOI_BSRR寄存器

;循环
Loop
	BL	Led0_on		;开灯
	BL	Delay		;延时
	BL 	Led0_off	;关灯
	BL 	Delay		;延时
	B Loop
	

;打开LED0
Led0_on
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;读取GPIOI_BSRR寄存器的值到R1
	ORR		R1, #(1 << 16)			;bit16置1,输出低电平
	STR		R1,	[R0]				;写入到GPIOI_BSRR寄存器
	BX		LR

;关闭LED0
Led0_off
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;读取GPIOI_BSRR寄存器的值到R1
	ORR		R1, #(1 << 0)			;bit15置1，输出高电平
	STR		R1,	[R0]				;写入到GPIOI_BSRR寄存器
	BX		LR

;延时函数
Delay
    LDR	R2, =0X4FFFFF
	LDR R3, =0X0
Delay_loop
    SUB R2, R2, #1	;R2寄存器减1
	CMP R2, R3		;R2和R3寄存器的值进行比较
	BNE	Delay_loop	;R2与R3的值不相等，说明没有R2还没有减完，继续
	BX LR			;返回LR
	END
	
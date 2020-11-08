;******************************************************************************
;* @file			: main.s
;* @author         	: ����ԭ��Linux�Ŷ�
;* @version     	: V1.0
;* @date         	: 2020-05-03
;* @description     : MP157������M4�������main����ļ�
;*                    ���ļ�����:
;*                    - ������Ҫʹ�õļĴ���
;*                    - Start������д����λ�жϺ���Reset_Handler��ִ��Start����
;*                    - ʹ��GPIOIʱ�ӣ���ʼ��GPIOI_0���IOΪ�������
;*                    - ѭ�����������Եĵ���/Ϩ��LED0
;* @license     	: Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
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
	;1������RCC_MC_AHB4ENSETR�Ĵ�����ʹ��GPIOIʱ��
	LDR		R0,	=RCC_MC_AHB4ENSETR
	LDR		R1, [R0]				;��ȡRCC_MC_AHB4ENSETR�Ĵ�����ֵ��R1
	ORR		R1, #(1 << 8)			;bit4��1,ʹ��GPIOIʱ��
	STR		R1,	[R0]				;д�뵽RCC_MC_AHB4ENSETR�Ĵ���
	
	;2��GPIOI_MODER�Ĵ���������GPIOI_0���ģʽ
	LDR		R0,	=GPIOI_MODER
	LDR		R1, [R0]				;��ȡGPIOI_MODER�Ĵ�����ֵ��R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0����
	ORR		R1, #(1 << (2 * 0))		;bit1:0����Ϊ01
	STR		R1,	[R0]				;д�뵽GPIOI_MODER�Ĵ���
	
	;3��GPIOI_OTYPER�Ĵ���������GPIOI_0Ϊ����ģʽ
	LDR		R0,	=GPIOI_OTYPER		
	LDR		R1, [R0]				;��ȡGPIOI_OTYPER�Ĵ���ֵ��R1
	BIC		R1, #(1 << 0)			;bit0����,����Ϊ����
	STR		R1,	[R0]				;д�뵽GPIOI_OTYPER�Ĵ���	
	
	;4��GPIOI_OSPEEDR�Ĵ���������GPIOI_0Ϊ����
	LDR		R0,	=GPIOI_OSPEEDR
	LDR		R1, [R0]				;��ȡGPIOI_OSPEEDR�Ĵ�����ֵ��R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0����
	ORR		R1, #(2 << (2 * 0))		;bit1:0����Ϊ10
	STR		R1,	[R0]				;д�뵽GPIOI_OSPEEDR�Ĵ���	
	
	;5��GPIOI_PUPDR�Ĵ���������GPIOI_0����
	LDR		R0,	=GPIOI_PUPDR
	LDR		R1, [R0]				;��ȡGPIOI_PUPDR�Ĵ�����ֵ��R1
	BIC		R1, #(3 << (2 * 0))		;bit1:0����
	ORR		R1, #(1 << (2 * 0))		;bit1:0����Ϊ01
	STR		R1,	[R0]				;д�뵽GPIOI_PUPDR�Ĵ���	
	
	;6��GPIOI_BSRR�Ĵ���������GPIOI_0Ϊ�ͣ�����LED0
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;��ȡGPIOI_BSRR�Ĵ�����ֵ��R1
	ORR		R1, #(1 << 16)			;bit16����Ϊ0
	STR		R1,	[R0]				;д�뵽GPIOI_BSRR�Ĵ���

;ѭ��
Loop
	BL	Led0_on		;����
	BL	Delay		;��ʱ
	BL 	Led0_off	;�ص�
	BL 	Delay		;��ʱ
	B Loop
	

;��LED0
Led0_on
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;��ȡGPIOI_BSRR�Ĵ�����ֵ��R1
	ORR		R1, #(1 << 16)			;bit16��1,����͵�ƽ
	STR		R1,	[R0]				;д�뵽GPIOI_BSRR�Ĵ���
	BX		LR

;�ر�LED0
Led0_off
	LDR		R0,	=GPIOI_BSRR
	LDR		R1, [R0]				;��ȡGPIOI_BSRR�Ĵ�����ֵ��R1
	ORR		R1, #(1 << 0)			;bit15��1������ߵ�ƽ
	STR		R1,	[R0]				;д�뵽GPIOI_BSRR�Ĵ���
	BX		LR

;��ʱ����
Delay
    LDR	R2, =0X4FFFFF
	LDR R3, =0X0
Delay_loop
    SUB R2, R2, #1	;R2�Ĵ�����1
	CMP R2, R3		;R2��R3�Ĵ�����ֵ���бȽ�
	BNE	Delay_loop	;R2��R3��ֵ����ȣ�˵��û��R2��û�м��꣬����
	BX LR			;����LR
	END
	
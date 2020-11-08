;******************************************************************************
;* @file         	: startup_stm32mp15xx.s
;* @author         	: ����ԭ��Linux�Ŷ�
;* @version     	: V1.0
;* @date         	: 2020-05-03
;* Description     	: STM32MP1�豸���ж�������
;*                    ���ļ�����:
;*                    - ��ʼ��SP
;*                    - STM32P1�����Ժ���ִ��Reset_Handler����
;*                    - Reset_Handler����������תȥ����Start����
;* @license     	: Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
;****************************************************************************** 

Stack_Size      EQU     0x00000400		;ջ��СΪ0X400��C��������Ҫʹ��

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE   Stack_Size
__initial_sp							;��ʼ��SP

				AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
					
__Vectors       DCD      __initial_sp   	;ջ��
                DCD      Reset_Handler     	;��λ�ж�������


__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors
	
				AREA     |.text|, CODE, READONLY
					
Reset_Handler   PROC						;��λ�жϺ���	
				IMPORT  Start
				
				LDR R0, =Start				;��תִ��Start����
				BX 		R0
                ENDP
					

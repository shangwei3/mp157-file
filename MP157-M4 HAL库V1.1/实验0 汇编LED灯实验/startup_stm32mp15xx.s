;******************************************************************************
;* @file         	: startup_stm32mp15xx.s
;* @author         	: 正点原子Linux团队
;* @version     	: V1.0
;* @date         	: 2020-05-03
;* Description     	: STM32MP1设备的中断向量表
;*                    本文件功能:
;*                    - 初始化SP
;*                    - STM32P1启动以后先执行Reset_Handler函数
;*                    - Reset_Handler函数里面跳转去运行Start函数
;* @license     	: Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
;****************************************************************************** 

Stack_Size      EQU     0x00000400		;栈大小为0X400，C语言运行要使用

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE   Stack_Size
__initial_sp							;初始化SP

				AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
					
__Vectors       DCD      __initial_sp   	;栈顶
                DCD      Reset_Handler     	;复位中断向量表


__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors
	
				AREA     |.text|, CODE, READONLY
					
Reset_Handler   PROC						;复位中断函数	
				IMPORT  Start
				
				LDR R0, =Start				;跳转执行Start函数
				BX 		R0
                ENDP
					

/**
 ****************************************************************************************************
 * @file        main.h
 * @author      正点原子Linux团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-03
 * @brief       定义外设结构体
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
 * 修改说明
 * V1.0 20200503
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __MAIN_H
#define __MAIN_H

/*
 * 数据类型 
 */
#define __IO volatile  
#define RESET 	0
#define SET		1
typedef unsigned int 			uint32_t; 
 
/* 
 * 各个外设基地址 
 */
#define PERIPH_BASE				(0x40000000)
#define MCU_AHB4_PERIPH_BASE  	(PERIPH_BASE + 0x10000000)
#define RCC_BASE        		(MCU_AHB4_PERIPH_BASE + 0x0000)	
#define GPIOA_BASE            	(MCU_AHB4_PERIPH_BASE + 0x2000)
#define GPIOB_BASE            	(MCU_AHB4_PERIPH_BASE + 0x3000)
#define GPIOC_BASE            	(MCU_AHB4_PERIPH_BASE + 0x4000)
#define GPIOD_BASE            	(MCU_AHB4_PERIPH_BASE + 0x5000)
#define GPIOE_BASE            	(MCU_AHB4_PERIPH_BASE + 0x6000)
#define GPIOF_BASE            	(MCU_AHB4_PERIPH_BASE + 0x7000)
#define GPIOG_BASE            	(MCU_AHB4_PERIPH_BASE + 0x8000)
#define GPIOH_BASE            	(MCU_AHB4_PERIPH_BASE + 0x9000)
#define GPIOI_BASE            	(MCU_AHB4_PERIPH_BASE + 0xA000)
#define GPIOJ_BASE            	(MCU_AHB4_PERIPH_BASE + 0xB000)
#define GPIOK_BASE            	(MCU_AHB4_PERIPH_BASE + 0xC000)
#define AIEC_BASE             	(MCU_AHB4_PERIPH_BASE + 0xD000)

/*
 * RCC外设结构体
 */
typedef struct
{
	__IO uint32_t TZCR;                      	 /* Address offset: 0x00 */
		uint32_t RESERVED0[2];                   /* Address offset: 0x04 */
	__IO uint32_t OCENSETR;                      /* Address offset: 0x0C */
	__IO uint32_t OCENCLRR;                      /* Address offset: 0x10 */
		uint32_t RESERVED1;                      /* Address offset: 0x14 */
	__IO uint32_t HSICFGR;                       /* Address offset: 0x18 */
	__IO uint32_t CSICFGR;                       /* Address offset: 0x1C */
	__IO uint32_t MPCKSELR;                      /* Address offset: 0x20 */
	__IO uint32_t ASSCKSELR;                     /* Address offset: 0x24 */
	__IO uint32_t RCK12SELR;                     /* Address offset: 0x28 */
	__IO uint32_t MPCKDIVR;                      /* Address offset: 0x2C */
	__IO uint32_t AXIDIVR;                       /* Address offset: 0x30 */
		uint32_t RESERVED2[2];                   /* Address offset: 0x34 */
	__IO uint32_t APB4DIVR;                      /* Address offset: 0x3C */
	__IO uint32_t APB5DIVR;                      /* Address offset: 0x40 */
	__IO uint32_t RTCDIVR;                       /* Address offset: 0x44 */
	__IO uint32_t MSSCKSELR;                     /* Address offset: 0x48 */
		uint32_t RESERVED3[13];                  /* Address offset: 0x4C */
	__IO uint32_t PLL1CR;                        /* Address offset: 0x80 */
	__IO uint32_t PLL1CFGR1;                     /* Address offset: 0x84 */
	__IO uint32_t PLL1CFGR2;                     /* Address offset: 0x88 */
	__IO uint32_t PLL1FRACR;                     /* Address offset: 0x8C */
	__IO uint32_t PLL1CSGR;                      /* Address offset: 0x90 */
	__IO uint32_t PLL2CR;                        /* Address offset: 0x94 */
	__IO uint32_t PLL2CFGR1;                     /* Address offset: 0x98 */
	__IO uint32_t PLL2CFGR2;                     /* Address offset: 0x9C */
	__IO uint32_t PLL2FRACR;                     /* Address offset: 0xA0 */
	__IO uint32_t PLL2CSGR;                      /* Address offset: 0xA4 */
		uint32_t RESERVED4[6];                   /* Address offset: 0xA8 */
	__IO uint32_t I2C46CKSELR;                   /* Address offset: 0xC0 */
	__IO uint32_t SPI6CKSELR;                    /* Address offset: 0xC4 */
	__IO uint32_t UART1CKSELR;                   /* Address offset: 0xC8 */
	__IO uint32_t RNG1CKSELR;                    /* Address offset: 0xCC */
	__IO uint32_t CPERCKSELR;                    /* Address offset: 0xD0 */
	__IO uint32_t STGENCKSELR;                   /* Address offset: 0xD4 */
	__IO uint32_t DDRITFCR;                      /* Address offset: 0xD8 */
		uint32_t RESERVED5;                      /* Address offset: 0xDC */
		uint32_t RESERVED6[8];                   /* Address offset: 0xE0 */
	__IO uint32_t MP_BOOTCR;                     /* Address offset: 0x100 */
	__IO uint32_t MP_SREQSETR;                   /* Address offset: 0x104 */
	__IO uint32_t MP_SREQCLRR;                   /* Address offset: 0x108 */
	__IO uint32_t MP_GCR;                        /* Address offset: 0x10C */
	__IO uint32_t MP_APRSTCR;                    /* Address offset: 0x110 */
	__IO uint32_t MP_APRSTSR;                    /* Address offset: 0x114 */
		uint32_t RESERVED7[10];                  /* Address offset: 0x118 */
	__IO uint32_t BDCR;                          /* Address offset: 0x140 */
	__IO uint32_t RDLSICR;                       /* Address offset: 0x144 */
		uint32_t RESERVED8[14];                  /* Address offset: 0x148 */
	__IO uint32_t APB4RSTSETR;                   /* Address offset: 0x180 */
	__IO uint32_t APB4RSTCLRR;                   /* Address offset: 0x184 */
	__IO uint32_t APB5RSTSETR;                   /* Address offset: 0x188 */
	__IO uint32_t APB5RSTCLRR;                   /* Address offset: 0x18C */
	__IO uint32_t AHB5RSTSETR;                   /* Address offset: 0x190 */
	__IO uint32_t AHB5RSTCLRR;                   /* Address offset: 0x194 */
	__IO uint32_t AHB6RSTSETR;                   /* Address offset: 0x198 */
	__IO uint32_t AHB6RSTCLRR;                   /* Address offset: 0x19C */
	__IO uint32_t TZAHB6RSTSETR;                 /* Address offset: 0x1A0 */
	__IO uint32_t TZAHB6RSTCLRR;                 /* Address offset: 0x1A4 */
		uint32_t RESERVED9[22];                  /* Address offset: 0x1A8 */
	__IO uint32_t MP_APB4ENSETR;                 /* Address offset: 0x200 */
	__IO uint32_t MP_APB4ENCLRR;                 /* Address offset: 0x204 */
	__IO uint32_t MP_APB5ENSETR;                 /* Address offset: 0x208 */
	__IO uint32_t MP_APB5ENCLRR;                 /* Address offset: 0x20C */
	__IO uint32_t MP_AHB5ENSETR;                 /* Address offset: 0x210 */
	__IO uint32_t MP_AHB5ENCLRR;                 /* Address offset: 0x214 */
	__IO uint32_t MP_AHB6ENSETR;                 /* Address offset: 0x218 */
	__IO uint32_t MP_AHB6ENCLRR;                 /* Address offset: 0x21C */
		uint32_t RESERVED10[24];                 /* Address offset: 0x220 */
	__IO uint32_t MC_APB4ENSETR;                 /* Address offset: 0x280 */
	__IO uint32_t MC_APB4ENCLRR;                 /* Address offset: 0x284 */
	__IO uint32_t MC_APB5ENSETR;                 /* Address offset: 0x288 */
	__IO uint32_t MC_APB5ENCLRR;                 /* Address offset: 0x28C */
	__IO uint32_t MC_AHB5ENSETR;                 /* Address offset: 0x290 */
	__IO uint32_t MC_AHB5ENCLRR;                 /* Address offset: 0x294 */
	__IO uint32_t MC_AHB6ENSETR;                 /* Address offset: 0x298 */
	__IO uint32_t MC_AHB6ENCLRR;                 /* Address offset: 0x29C */
		uint32_t RESERVED11[24];                 /* Address offset: 0x2A0 */
	__IO uint32_t MP_APB4LPENSETR;               /* Address offset: 0x300 */
	__IO uint32_t MP_APB4LPENCLRR;               /* Address offset: 0x304 */
	__IO uint32_t MP_APB5LPENSETR;               /* Address offset: 0x308 */
	__IO uint32_t MP_APB5LPENCLRR;               /* Address offset: 0x30C */
	__IO uint32_t MP_AHB5LPENSETR;               /* Address offset: 0x310 */
	__IO uint32_t MP_AHB5LPENCLRR;               /* Address offset: 0x314 */
	__IO uint32_t MP_AHB6LPENSETR;               /* Address offset: 0x318 */
	__IO uint32_t MP_AHB6LPENCLRR;               /* Address offset: 0x31C */
		uint32_t RESERVED12[24];                 /* Address offset: 0x320 */
	__IO uint32_t MC_APB4LPENSETR;               /* Address offset: 0x380 */
	__IO uint32_t MC_APB4LPENCLRR;               /* Address offset: 0x384 */
	__IO uint32_t MC_APB5LPENSETR;               /* Address offset: 0x388 */
	__IO uint32_t MC_APB5LPENCLRR;               /* Address offset: 0x38C */
	__IO uint32_t MC_AHB5LPENSETR;               /* Address offset: 0x390 */
	__IO uint32_t MC_AHB5LPENCLRR;               /* Address offset: 0x394 */
	__IO uint32_t MC_AHB6LPENSETR;               /* Address offset: 0x398 */
	__IO uint32_t MC_AHB6LPENCLRR;               /* Address offset: 0x39C */
		uint32_t RESERVED13[24];                 /* Address offset: 0x3A0 */
	__IO uint32_t BR_RSTSCLRR;                   /* Address offset: 0x400 */
	__IO uint32_t MP_GRSTCSETR;                  /* Address offset: 0x404 */
	__IO uint32_t MP_RSTSCLRR;                   /* Address offset: 0x408 */
	__IO uint32_t MP_IWDGFZSETR;                 /* Address offset: 0x40C */
	__IO uint32_t MP_IWDGFZCLRR;                 /* Address offset: 0x410 */
	__IO uint32_t MP_CIER;                       /* Address offset: 0x414 */
	__IO uint32_t MP_CIFR;                       /* Address offset: 0x418 */
	__IO uint32_t PWRLPDLYCR;                    /* Address offset: 0x41C */
	__IO uint32_t MP_RSTSSETR;                   /* Address offset: 0x420 */
		uint32_t RESERVED14[247];                /* Address offset: 0x424 */
	__IO uint32_t MCO1CFGR;                      /* Address offset: 0x800 */
	__IO uint32_t MCO2CFGR;                      /* Address offset: 0x804 */
	__IO uint32_t OCRDYR;                        /* Address offset: 0x808 */
	__IO uint32_t DBGCFGR;                       /* Address offset: 0x80C */
		uint32_t RESERVED15[4];                  /* Address offset: 0x810 */
	__IO uint32_t RCK3SELR;                      /* Address offset: 0x820 */
	__IO uint32_t RCK4SELR;                      /* Address offset: 0x824 */
	__IO uint32_t TIMG1PRER;                     /* Address offset: 0x828 */
	__IO uint32_t TIMG2PRER;                     /* Address offset: 0x82C */
	__IO uint32_t MCUDIVR;                       /* Address offset: 0x830 */
	__IO uint32_t APB1DIVR;                      /* Address offset: 0x834 */
	__IO uint32_t APB2DIVR;                      /* Address offset: 0x838 */
	__IO uint32_t APB3DIVR;                      /* Address offset: 0x83C */
		uint32_t RESERVED16[16];                 /* Address offset: 0x840 */
	__IO uint32_t PLL3CR;                        /* Address offset: 0x880 */
	__IO uint32_t PLL3CFGR1;                     /* Address offset: 0x884 */
	__IO uint32_t PLL3CFGR2;                     /* Address offset: 0x888 */
	__IO uint32_t PLL3FRACR;                     /* Address offset: 0x88C */
	__IO uint32_t PLL3CSGR;                      /* Address offset: 0x890 */
	__IO uint32_t PLL4CR;                        /* Address offset: 0x894 */
	__IO uint32_t PLL4CFGR1;                     /* Address offset: 0x898 */
	__IO uint32_t PLL4CFGR2;                     /* Address offset: 0x89C */
	__IO uint32_t PLL4FRACR;                     /* Address offset: 0x8A0 */
	__IO uint32_t PLL4CSGR;                      /* Address offset: 0x8A4 */
		uint32_t RESERVED17[6];                  /* Address offset: 0x8A8 */
	__IO uint32_t I2C12CKSELR;                   /* Address offset: 0x8C0 */
	__IO uint32_t I2C35CKSELR;                   /* Address offset: 0x8C4 */
	__IO uint32_t SAI1CKSELR;                    /* Address offset: 0x8C8 */
	__IO uint32_t SAI2CKSELR;                    /* Address offset: 0x8CC */
	__IO uint32_t SAI3CKSELR;                    /* Address offset: 0x8D0 */
	__IO uint32_t SAI4CKSELR;                    /* Address offset: 0x8D4 */
	__IO uint32_t SPI2S1CKSELR;                  /* Address offset: 0x8D8 */
	__IO uint32_t SPI2S23CKSELR;                 /* Address offset: 0x8DC */
	__IO uint32_t SPI45CKSELR;                   /* Address offset: 0x8E0 */
	__IO uint32_t UART6CKSELR;                   /* Address offset: 0x8E4 */
	__IO uint32_t UART24CKSELR;                  /* Address offset: 0x8E8 */
	__IO uint32_t UART35CKSELR;                  /* Address offset: 0x8EC */
	__IO uint32_t UART78CKSELR;                  /* Address offset: 0x8F0 */
	__IO uint32_t SDMMC12CKSELR;                 /* Address offset: 0x8F4 */
	__IO uint32_t SDMMC3CKSELR;                  /* Address offset: 0x8F8 */
	__IO uint32_t ETHCKSELR;                     /* Address offset: 0x8FC */
	__IO uint32_t QSPICKSELR;                    /* Address offset: 0x900 */
	__IO uint32_t FMCCKSELR;                     /* Address offset: 0x904 */
		uint32_t RESERVED18;                     /* Address offset: 0x908 */
	__IO uint32_t FDCANCKSELR;                   /* Address offset: 0x90C */
		uint32_t RESERVED19;                     /* Address offset: 0x910 */
	__IO uint32_t SPDIFCKSELR;                   /* Address offset: 0x914 */
	__IO uint32_t CECCKSELR;                     /* Address offset: 0x918 */
	__IO uint32_t USBCKSELR;                     /* Address offset: 0x91C */
	__IO uint32_t RNG2CKSELR;                    /* Address offset: 0x920 */
	__IO uint32_t DSICKSELR;                     /* Address offset: 0x924 */
	__IO uint32_t ADCCKSELR;                     /* Address offset: 0x928 */
	__IO uint32_t LPTIM45CKSELR;                 /* Address offset: 0x92C */
	__IO uint32_t LPTIM23CKSELR;                 /* Address offset: 0x930 */
	__IO uint32_t LPTIM1CKSELR;                  /* Address offset: 0x934 */
		uint32_t RESERVED20[18];                 /* Address offset: 0x938 */
	__IO uint32_t APB1RSTSETR;                   /* Address offset: 0x980 */
	__IO uint32_t APB1RSTCLRR;                   /* Address offset: 0x984 */
	__IO uint32_t APB2RSTSETR;                   /* Address offset: 0x988 */
	__IO uint32_t APB2RSTCLRR;                   /* Address offset: 0x98C */
	__IO uint32_t APB3RSTSETR;                   /* Address offset: 0x990 */
	__IO uint32_t APB3RSTCLRR;                   /* Address offset: 0x994 */
	__IO uint32_t AHB2RSTSETR;                   /* Address offset: 0x998 */
	__IO uint32_t AHB2RSTCLRR;                   /* Address offset: 0x99C */
	__IO uint32_t AHB3RSTSETR;                   /* Address offset: 0x9A0 */
	__IO uint32_t AHB3RSTCLRR;                   /* Address offset: 0x9A4 */
	__IO uint32_t AHB4RSTSETR;                   /* Address offset: 0x9A8 */
	__IO uint32_t AHB4RSTCLRR;                   /* Address offset: 0x9AC */
		uint32_t RESERVED21[20];                 /* Address offset: 0x9B0 */
	__IO uint32_t MP_APB1ENSETR;                 /* Address offset: 0xA00 */
	__IO uint32_t MP_APB1ENCLRR;                 /* Address offset: 0xA04 */
	__IO uint32_t MP_APB2ENSETR;                 /* Address offset: 0xA08 */
	__IO uint32_t MP_APB2ENCLRR;                 /* Address offset: 0xA0C */
	__IO uint32_t MP_APB3ENSETR;                 /* Address offset: 0xA10 */
	__IO uint32_t MP_APB3ENCLRR;                 /* Address offset: 0xA14 */
	__IO uint32_t MP_AHB2ENSETR;                 /* Address offset: 0xA18 */
	__IO uint32_t MP_AHB2ENCLRR;                 /* Address offset: 0xA1C */
	__IO uint32_t MP_AHB3ENSETR;                 /* Address offset: 0xA20 */
	__IO uint32_t MP_AHB3ENCLRR;                 /* Address offset: 0xA24 */
	__IO uint32_t MP_AHB4ENSETR;                 /* Address offset: 0xA28 */
	__IO uint32_t MP_AHB4ENCLRR;                 /* Address offset: 0xA2C */
		uint32_t RESERVED22[2];                  /* Address offset: 0xA30 */
	__IO uint32_t MP_MLAHBENSETR;                /* Address offset: 0xA38 */
	__IO uint32_t MP_MLAHBENCLRR;                /* Address offset: 0xA3C */
		uint32_t RESERVED23[16];                 /* Address offset: 0x940 */
	__IO uint32_t MC_APB1ENSETR;                 /* Address offset: 0xA80 */
	__IO uint32_t MC_APB1ENCLRR;                 /* Address offset: 0xA84 */
	__IO uint32_t MC_APB2ENSETR;                 /* Address offset: 0xA88 */
	__IO uint32_t MC_APB2ENCLRR;                 /* Address offset: 0xA8C */
	__IO uint32_t MC_APB3ENSETR;                 /* Address offset: 0xA90 */
	__IO uint32_t MC_APB3ENCLRR;                 /* Address offset: 0xA94 */
	__IO uint32_t MC_AHB2ENSETR;                 /* Address offset: 0xA98 */
	__IO uint32_t MC_AHB2ENCLRR;                 /* Address offset: 0xA9C */
	__IO uint32_t MC_AHB3ENSETR;                 /* Address offset: 0xAA0 */
	__IO uint32_t MC_AHB3ENCLRR;                 /* Address offset: 0xAA4 */
	__IO uint32_t MC_AHB4ENSETR;                 /* Address offset: 0xAA8 */
	__IO uint32_t MC_AHB4ENCLRR;                 /* Address offset: 0xAAC */
	__IO uint32_t MC_AXIMENSETR;                 /* Address offset: 0xAB0 */
	__IO uint32_t MC_AXIMENCLRR;                 /* Address offset: 0xAB4 */
	__IO uint32_t MC_MLAHBENSETR;                /* Address offset: 0xAB8 */
	__IO uint32_t MC_MLAHBENCLRR;                /* Address offset: 0xABC */
		uint32_t RESERVED24[16];                 /* Address offset: 0xAC0 */
	__IO uint32_t MP_APB1LPENSETR;               /* Address offset: 0xB00 */
	__IO uint32_t MP_APB1LPENCLRR;               /* Address offset: 0xB04 */
	__IO uint32_t MP_APB2LPENSETR;               /* Address offset: 0xB08 */
	__IO uint32_t MP_APB2LPENCLRR;               /* Address offset: 0xB0C */
	__IO uint32_t MP_APB3LPENSETR;               /* Address offset: 0xB10 */
	__IO uint32_t MP_APB3LPENCLRR;               /* Address offset: 0xB14 */
	__IO uint32_t MP_AHB2LPENSETR;               /* Address offset: 0xB18 */
	__IO uint32_t MP_AHB2LPENCLRR;               /* Address offset: 0xB1C */
	__IO uint32_t MP_AHB3LPENSETR;               /* Address offset: 0xB20 */
	__IO uint32_t MP_AHB3LPENCLRR;               /* Address offset: 0xB24 */
	__IO uint32_t MP_AHB4LPENSETR;               /* Address offset: 0xB28 */
	__IO uint32_t MP_AHB4LPENCLRR;               /* Address offset: 0xB2C */
	__IO uint32_t MP_AXIMLPENSETR;               /* Address offset: 0xB30 */
	__IO uint32_t MP_AXIMLPENCLRR;               /* Address offset: 0xB34 */
	__IO uint32_t MP_MLAHBLPENSETR;              /* Address offset: 0xB38 */
	__IO uint32_t MP_MLAHBLPENCLRR;              /* Address offset: 0xB3C */
		uint32_t RESERVED25[16];                 /* Address offset: 0xB40 */
	__IO uint32_t MC_APB1LPENSETR;               /* Address offset: 0xB80 */
	__IO uint32_t MC_APB1LPENCLRR;               /* Address offset: 0xB84 */
	__IO uint32_t MC_APB2LPENSETR;               /* Address offset: 0xB88 */
	__IO uint32_t MC_APB2LPENCLRR;               /* Address offset: 0xB8C */
	__IO uint32_t MC_APB3LPENSETR;               /* Address offset: 0xB90 */
	__IO uint32_t MC_APB3LPENCLRR;               /* Address offset: 0xB94 */
	__IO uint32_t MC_AHB2LPENSETR;               /* Address offset: 0xB98 */
	__IO uint32_t MC_AHB2LPENCLRR;               /* Address offset: 0xB9C */
	__IO uint32_t MC_AHB3LPENSETR;               /* Address offset: 0xBA0 */
	__IO uint32_t MC_AHB3LPENCLRR;               /* Address offset: 0xBA4 */
	__IO uint32_t MC_AHB4LPENSETR;               /* Address offset: 0xBA8 */
	__IO uint32_t MC_AHB4LPENCLRR;               /* Address offset: 0xBAC */
	__IO uint32_t MC_AXIMLPENSETR;               /* Address offset: 0xBB0 */
	__IO uint32_t MC_AXIMLPENCLRR;               /* Address offset: 0xBB4 */
	__IO uint32_t MC_MLAHBLPENSETR;              /* Address offset: 0xBB8 */
	__IO uint32_t MC_MLAHBLPENCLRR;              /* Address offset: 0xBBC */
		uint32_t RESERVED26[16];                 /* Address offset: 0xBC0 */
	__IO uint32_t MC_RSTSCLRR;                   /* Address offset: 0xC00 */
		uint32_t RESERVED27[4];                  /* Address offset: 0xC04 */
	__IO uint32_t MC_CIER;                       /* Address offset: 0xC14 */
	__IO uint32_t MC_CIFR;                       /* Address offset: 0xC18 */
		uint32_t RESERVED28[246];                /* Address offset: 0xC1C */
	__IO uint32_t VERR;                          /* Address offset: 0xFF4 */
	__IO uint32_t IPIDR;                         /* Address offset: 0xFF8 */
	__IO uint32_t SIDR;                          /* Address offset: 0xFFC */
} RCC_TypeDef;

/*
 *  GPIO外设结构体
 */
typedef struct
{
  __IO uint32_t MODER;           				/* Address offset: 0x000 */
  __IO uint32_t OTYPER;                         /* Address offset: 0x004 */
  __IO uint32_t OSPEEDR;                        /* Address offset: 0x008 */
  __IO uint32_t PUPDR;                          /* Address offset: 0x00C */
  __IO uint32_t IDR;                            /* Address offset: 0x010 */
  __IO uint32_t ODR;                            /* Address offset: 0x014 */
  __IO uint32_t BSRR;                           /* Address offset: 0x018 */
  __IO uint32_t LCKR;                           /* Address offset: 0x01C */
  __IO uint32_t AFR[2];                         /* Address offset: 0x020-0x024 */
  __IO uint32_t BRR;                            /* Address offset: 0x028 */
       uint32_t RESERVED0;                      /* Address offset: 0x02C */
  __IO uint32_t SECCFGR;                        /* Address offset: 0x030 */
       uint32_t RESERVED1[229];                 /* Address offset: 0x034-0x3C4 */
  __IO uint32_t HWCFGR10;                       /* Address offset: 0x3C8 */
  __IO uint32_t HWCFGR9;                        /* Address offset: 0x3CC */
  __IO uint32_t HWCFGR8;                        /* Address offset: 0x3D0 */
  __IO uint32_t HWCFGR7;                        /* Address offset: 0x3D4 */
  __IO uint32_t HWCFGR6;                        /* Address offset: 0x3D8 */
  __IO uint32_t HWCFGR5;                        /* Address offset: 0x3DC */
  __IO uint32_t HWCFGR4;                        /* Address offset: 0x3E0 */
  __IO uint32_t HWCFGR3;                        /* Address offset: 0x3E4 */
  __IO uint32_t HWCFGR2;                        /* Address offset: 0x3E8 */
  __IO uint32_t HWCFGR1;                        /* Address offset: 0x3EC */
  __IO uint32_t HWCFGR0;                        /* Address offset: 0x3F0 */
  __IO uint32_t VERR;                           /* Address offset: 0x3F4 */
  __IO uint32_t IPIDR;                          /* Address offset: 0x3F8 */
  __IO uint32_t SIDR;                           /* Address offset: 0x3FC */
} GPIO_TypeDef;

/*
 * 外设
 */
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ               ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK               ((GPIO_TypeDef *) GPIOK_BASE)


#endif


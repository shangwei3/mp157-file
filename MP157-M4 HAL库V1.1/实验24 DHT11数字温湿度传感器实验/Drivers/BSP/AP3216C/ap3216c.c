/**
 ****************************************************************************************************
 * @file        ap3216c.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-20
 * @brief       AP3216C ��������
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
 * �޸�˵��
 * V1.0 20200520
 * ��һ�η���
 *
 ****************************************************************************************************
 */
#include "./BSP/AP3216C/ap3216c.h"
#include "./BSP/IIC/iic.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       ��ʼ��AP3216C
 * @param       ��
 * @retval      0,��ʼ���ɹ�
 *				1,��ʼ��ʧ��
 */
uint8_t ap3216c_init(void)
{
	uint8_t temp=0;
         				
	iic5_init();						/* ��ʼ��IIC 			*/
    ap3216c_write_one_byte(0x00, 0X04);	/* ��λAP3216C 			*/
    delay_ms(50);						/* AP33216C��λ����10ms */
    ap3216c_write_one_byte(0x00, 0X03);	/* ����ALS��PS+IR   	*/ 
	temp=ap3216c_read_one_byte(0X00);	/* ��ȡ�ո�д��ȥ��0X03 */
	if(temp == 0X03)
		return 0;						/* AP3216C���� 			*/
	else 
		return 1;						/* AP3216Cʧ�� 			*/
} 


/**
 * @brief       ��ȡAP3216C������
 * 	@note		ע�⣡���ͬʱ��ALS,IR+PS�Ļ��������ݶ�ȡ��ʱ����Ҫ����112.5ms
 * @param       ir:  ��ȡ����irֵ
 * @param       ps:  ��ȡ����psֵ
 * @param       als: ��ȡ����alsֵ
 * @retval      ��
 */
void ap3216c_read_data(uint16_t* ir,uint16_t* ps,uint16_t* als)
{
	uint8_t i;
    uint8_t buf[6];

    for(i=0;i<6;i++)	
    {
        buf[i]=ap3216c_read_one_byte(0X0A + i);			/* ѭ����ȡ���д���������*/
    }
	
    if(buf[0] & 0X80)
		*ir = 0;										/* IR_OFλΪ1,��������Ч */
	else 
		*ir = ((uint16_t)buf[1] << 2) | (buf[0] & 0X03);/* ��ȡIR������������ 	*/ 
	
	*als = ((uint16_t)buf[3] << 8) | buf[2];			/* ��ȡALS������������   */ 
	
    if(buf[4] & 0x40)
		*ps=0;    										/* IR_OFλΪ1,��������Ч */
	else 
		*ps=((uint16_t)(buf[5]&0X3F)<<4)|(buf[4]&0X0F);	/* ��ȡPS������������   */ 
}

/**
 * @brief       ��AP3216Cָ���Ĵ���дһ���ֽ�  
 * @param       reg:  �Ĵ�����ַ
 * @param       data: Ҫд�������
 * @retval      ��
 */
void ap3216c_write_one_byte(uint8_t reg,uint8_t data)
{
	uint8_t senddata[2];
	
	senddata[0] = reg;  /* �Ĵ�����ַ */
	senddata[1] = data;	/* Ҫд������ */
	
	INTX_DISABLE();		/* I2Cͨ�ŵ�ʱ��,�ر��жϣ���ֹ���� */
	HAL_I2C_Master_Transmit(&g_i2c5_handle, AP3216C_ADDR, senddata, 2, 1000);
	
}

/**
 * @brief       ��ȡAP3216Cָ���Ĵ�������  
 * @param       reg:  �Ĵ�����ַ
 * @retval      ����������
 */
uint8_t ap3216c_read_one_byte(uint8_t reg)
{
	uint8_t res;
	uint8_t senddata;
	
	/* 1���ȷ���Ҫ��ȡ�ļĴ�����ַ */
	senddata = reg;  /* �Ĵ�����ַ */
	INTX_DISABLE();		/* I2Cͨ�ŵ�ʱ��,�ر��жϣ���ֹ���� */
	HAL_I2C_Master_Transmit(&g_i2c5_handle, AP3216C_ADDR, &senddata, 1, 1000);
	
	/* 2����ȡ���� */;
	HAL_I2C_Master_Receive(&g_i2c5_handle, AP3216C_ADDR, &res, 1, 1000);
	INTX_ENABLE();		/* I2Cͨ����ɣ����ж� */
    return res;  
}



#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOC������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;//| GPIO_Pin_4 | GPIO_Pin_5	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

	/*������������Ϊ50MHz */   
  	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
  	GPIO_Init(GPIOC, &GPIO_InitStructure);		  

	/* �ر�����led��	*/
	//GPIO_ResetBits(GPIOC, GPIO_Pin_4 );	 //| GPIO_Pin_4 | GPIO_Pin_5
	
}

void GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOC������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;//| GPIO_Pin_4 | GPIO_Pin_5	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  

	/* �ر�����led��	*/
	//GPIO_SetBits(GPIOA, GPIO_Pin_7 );	 //| GPIO_Pin_4 | GPIO_Pin_5
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

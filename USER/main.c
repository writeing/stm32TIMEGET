/******
auth:wxc
date:2017.03.09
content:add TIM2 get ms time add systick get us time
        ʹ����ѯ����ѯ�ⲿ���壬�������岻�淶��������ʱ������
				���жϺ�������ʵʱ��ȡʱ�䣬Ȼ����main�����������ʹ�ӡ��			

auth:wxc
date:2017.03.10
content:add RTC get time on PPS is break

auth:wxc
date:2017.03.13
content:add flash save data 
				for startadress save data each 32*7*4 byte 
				and save value count cal data numble

auth:wxc
date:2017.03.14
content:add common.h head file save common value
*******/
#include "main.h"
/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
//struct pliuTime savePIL[500] __attribute__((at(0x08040000)));// flashCount __attribute__ ((at(0x08037000)));
//int savePltindex __attribute__((at(0x08010000)));//((section("NO_INIT"),zero_init));
int main(void)
{
//		static int i=0;
//		char buff[50];

		/****usart1 init******/
		USART1_Config();
		NVIC_Configuration();
		/********/
		/****usart1 init******/
		USART2_Config();
		NVIC_Configuration2();
		/********/
		/***RTC******/
		RTC_Configuration();
		/*************/
		/* TIM2 ��ʱ���� */
		TIM2_NVIC_Configuration();
    TIM2_Configuration();

		/* TIM2 ��ʼ��ʱ */
		START_TIME;			  
	  /***led init****/
		LED_GPIO_Config();
		//GPIO_Config();
	  /***************/
		/****sys init*****/
		SysTick_Init();
	  /*********/
		/***exit init******/
		EXTI_PA5_Config();
		EXTI_PA6_Config();
		/*********/		
		readFlashInit();
		while(1)
		{
			if(timeArray[0])
			{				
				printf("%d\r\n",timeArray[0]);
				timeArray[0] = 0;				
			}
			Delay_us(10);	
			if(PLTindex == SAVECOUNT)
			{		
				Writeflash(PLT);
				memset(PLT,0,sizeof(PLT));
				PLTindex = 0;
			}			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

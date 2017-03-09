/******
auth:wxc
date:2017.03.09
content:add TIM2 get ms time add systick get us time
        ʹ����ѯ����ѯ�ⲿ���壬�������岻�淶��������ʱ������
				���жϺ�������ʵʱ��ȡʱ�䣬Ȼ����main�����������ʹ�ӡ��				
*******/
#include "main.h"
/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
extern struct nowTime NowTime;
extern struct pliuTime PLT[20];
extern int PLTindex;
extern int timeArray[10];
extern volatile u32 TimingDelay; 
extern int GPSBaseTime;
extern float DelayUsTime;
int main(void)
{
		int i=0;
		/****usart1 init******/
		USART1_Config();
		NVIC_Configuration();
		/********/
		/****usart1 init******/
		USART2_Config();
		NVIC_Configuration2();
		/********/
		/****sys init*****/
		SysTick_Init();
	  /*********/
	  /***exit init******/
		EXTI_PA5_Config();
		//EXTI_PA6_Config();
		/*********/
	  /***led init****/
		LED_GPIO_Config();
		GPIO_Config();
	  /***************/
		/* TIM2 ��ʱ���� */
		TIM2_NVIC_Configuration();
    TIM2_Configuration();

		/* TIM2 ��ʼ��ʱ */
		START_TIME;
		while(1)
		{
			// Delay_us(10);		
			if(timeArray[0])
			{
				//printf("%d\r\n",timeArray[0]);
				//printf("%d\r\n",timeArray[1]);
				timeArray[0] = 0;				
			}
			Delay_us(10);
			if(PLTindex >= 6)
			{
				while(PLTindex)
				{
					PLTindex--;
					printf("%d-%02d-%02d %02d:%02d:%02d.%03.02f  %d\r\n",PLT[PLTindex].time.year,PLT[PLTindex].time.month,PLT[PLTindex].time.day,PLT[PLTindex].time.hour,PLT[PLTindex].time.minute,PLT[PLTindex].time.second,PLT[PLTindex].time.micros,PLTindex);
					//Delay_us(10);
				}		
			}	
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
			{		
				//�Ǹߵ�ƽ
				PLT[PLTindex].time = NowTime;
				if(GPSBaseTimeFlag)					
				{
					//PPS���廹û�е�					
					PLT[PLTindex].time.micros = (GPSBaseTime/100)%1000 + DelayUsTime/100;//(((100000-NowTime.micros)/100000)*TimingDelay + TimingDelay)/100;					
				}
				else
				{
					//PPS�����Ѿ�����
					PLT[PLTindex].time.micros = (TimingDelay + GPSBaseTime)%1000 + DelayUsTime/100;
				}
				
				PLT[PLTindex].index = PLTindex;
				PLTindex++;				
				printf("%d\r\n",i++);				
				while(1)
				{		
					//�ȴ�IO��Ϊ�͵�ƽ
					if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
					{
						Delay_us(100*50);	//50ms
						//��ʱ֮�󣬻��ǵ͵�ƽ
						if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
							break;
					}
				}
			}
			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/



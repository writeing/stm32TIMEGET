#include "main.h"
/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
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
		/* TIM2 定时配置 */
		TIM2_NVIC_Configuration();
    TIM2_Configuration();

		/* TIM2 开始计时 */
		START_TIME;
		while(1)
		{
			// Delay_us(10);		
			if(timeArray[0])
			{
				printf("%d\r\n",timeArray[0]);
				printf("%d\r\n",timeArray[1]);
				timeArray[0] = 0;				
			}
			Delay_us(10);
			if(PLTindex >= 6)
			{
				while(PLTindex--)
				{
					printf("%d-%02d-%02d %02d:%02d:%02d.%03.02f  %d\r\n",PLT[PLTindex].time.year,PLT[PLTindex].time.month,PLT[PLTindex].time.day,PLT[PLTindex].time.hour,PLT[PLTindex].time.minute,PLT[PLTindex].time.second,PLT[PLTindex].time.micros,PLTindex);
					//Delay_us(10);
				}		
			}	
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
			{													
				PLT[PLTindex].time = NowTime;
				if(GPSBaseTimeFlag)					
				{
					PLT[PLTindex].time.micros = (GPSBaseTime/100)%1000 + DelayUsTime/100;//(((100000-NowTime.micros)/100000)*TimingDelay + TimingDelay)/100;					
				}
				else
				{
					PLT[PLTindex].time.micros = (TimingDelay + GPSBaseTime)%1000 + DelayUsTime/100;
				}
				printf("delaytime = %d\r\n",GPSBaseTime);
				PLT[PLTindex].index = PLTindex;
				PLTindex++;				
				Delay_us(100*140);
			}
			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/



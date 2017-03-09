/******
auth:wxc
date:2017.03.09
content:add TIM2 get ms time add systick get us time
        使用轮询法查询外部脉冲，但是脉冲不规范，采用延时法防抖
				在中断函数里面实时获取时间，然后在main函数里面计算和打印，				
*******/
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
				//是高电平
				PLT[PLTindex].time = NowTime;
				if(GPSBaseTimeFlag)					
				{
					//PPS脉冲还没有到					
					PLT[PLTindex].time.micros = (GPSBaseTime/100)%1000 + DelayUsTime/100;//(((100000-NowTime.micros)/100000)*TimingDelay + TimingDelay)/100;					
				}
				else
				{
					//PPS脉冲已经到来
					PLT[PLTindex].time.micros = (TimingDelay + GPSBaseTime)%1000 + DelayUsTime/100;
				}
				
				PLT[PLTindex].index = PLTindex;
				PLTindex++;				
				printf("%d\r\n",i++);				
				while(1)
				{		
					//等待IO口为低电平
					if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
					{
						Delay_us(100*50);	//50ms
						//延时之后，还是低电平
						if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
							break;
					}
				}
			}
			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/



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

int main(void)
{
		int i=0;
		char buff[50];
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
		
		/***RTC******/
		RTC_Configuration();
		/*************/
		while(1)
		{
			// Delay_us(10);		
			if(timeArray[0])
			{
				printf("%d\r\n",timeArray[0]);
				//printf("%d\r\n",timeArray[1]);
				timeArray[0] = 0;				
			}
			Delay_us(10);
			if(PLTindex >= 6)
			{
				while(PLTindex)
				{
					PLTindex--;
					strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S",&PLT[PLTindex].time);					
					printf("%s.%06.2f\r\n",buff,PLT[PLTindex].micros);
					//printf( "%s.%06.2f\r\n", asctime( &PLT[PLTindex].time ),micros);
					//printf("%d-%02d-%02d %02d:%02d:%02d.%06.2f  %d\r\n",PLT[PLTindex].time.tm_year,PLT[PLTindex].time.month,PLT[PLTindex].time.day,PLT[PLTindex].time.hour,PLT[PLTindex].time.minute,PLT[PLTindex].time.second,PLT[PLTindex].time.micros,PLTindex);
					//Delay_us(10);
				}		
			}
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
			{		
				//高电平							
				if(RTCEnableFlag)
				{
					//RTC enable . PPS break						
					PLT[PLTindex].time = getTMforRTC();
					PLT[PLTindex].micros= TimingDelay%1000 + DelayUsTime/100;
				}
				else
				{
						PLT[PLTindex].time = NowTime;
						//RTC disable 。pps connect
						if(GPSBaseTimeFlag)					
						{
							//PPS脉冲还没有到					
							//PLT[PLTindex].time. 
							PLT[PLTindex].micros= (GPSBaseTime/100)%1000 + DelayUsTime/100;//(((100000-NowTime.micros)/100000)*TimingDelay + TimingDelay)/100;					
						}
						else
						{
							//PPS脉冲已经到来
							//PLT[PLTindex].time.
							PLT[PLTindex].micros = (TimingDelay + GPSBaseTime)%1000 + DelayUsTime/100;
						}
				}				
				printf("%d\r\n",i++);	
				PLT[PLTindex].index = PLTindex;
				PLTindex++;				
				
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



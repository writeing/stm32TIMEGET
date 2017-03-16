#include "sysdelay.h"


volatile u32 delayTime;
volatile float DelayUsTime;
/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	 //SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
		SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}


/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,10us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
 *       ：外部调用 
 */

void Delay_us(__IO u32 nTime)
{ 
	delayTime = nTime;
	// 使能滴答定时器  
	//SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(delayTime != 0);
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}


/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */ 
volatile u32 queryPlise = 0;
int getGPIOflag = 1;
//u32 msTime = 0;
void quePlise()
{		
	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
	{		
		//低电平								
		getGPIOflag = 0;		//frobid get the GPIO
		if(RTCEnableFlag)
		{
			//RTC enable . PPS break						
			PLT[PLTindex].time = getTMforRTC();
			PLT[PLTindex].micros= TimingDelay%1000 + DelayUsTime/100;
		}
		else
		{	
			//RTC disable 。pps connect					
			PLT[PLTindex].time = NowTime;
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
		PLT[PLTindex].index = PLTindex;
		PLTindex++;	
		PLTindex %= PLTARRAY;
		while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4));
	}			
	queryPlise = 30;
	getGPIOflag = 1;			// enable get GPIO
}
void TimingDelay_Decrement(void)
{
	/*if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
	else
	{
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	}
	*/
	if(queryPlise < 10 )
	{
		quePlise();
	}
	if (delayTime != 0x00)
	{ 
		delayTime--;
	}	
	DelayUsTime ++;		
	if(getGPIOflag)
		queryPlise--;
}

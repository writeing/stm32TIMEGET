/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

//#include "common.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//extern void TimingDelay_Decrement(void );

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
//**************************//
struct tm NowTime;
struct pliuTime PLT[PLTARRAY];
int PLTindex = 1;
int timeArray[10];
//**************************//

//**************************//
int updateBaseTime = 0;
volatile u8 timeArrayforGps[50];
static int timeIndex = 0;
//**************************//
volatile u32 TimingDelay; 
volatile int GPSBaseTime = 0;
//**************************//
int GPSBaseTimeFlag = 0;

//**************************//
int getGPIOPin = 0;
//**************************//
/* I/O线中断，中断线为PA5 */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) //确保是否产生了EXTI Line中断
	{		
		EXTI_ClearITPendingBit(EXTI_Line5);     //清除中断标志位		
		/**do it***/				
		timeArray[0] = TimingDelay;		
		timeArray[1] = DelayUsTime;			
		updateBaseTime = 1;		
		GPSBaseTimeFlag = 0;			
		RTCEnableFlag = 0;	
		Time_Adjust(NowTime);
		if(RTCEnableFlag)
			RTC_DISABLE();
		TimingDelay = 0;		
		DelayUsTime = 0;

	} 
//	if(EXTI_GetITStatus(EXTI_Line6) != RESET) //确保是否产生了EXTI Line中断
//	{	
//		EXTI_ClearITPendingBit(EXTI_Line6);     //清除中断标志位		
//		//高电平							
//		if(RTCEnableFlag)
//		{
//			//RTC enable . PPS break						
//			PLT[PLTindex].time = getTMforRTC();
//			PLT[PLTindex].micros= TimingDelay%1000 + DelayUsTime/100;
//		}
//		else
//		{
//				PLT[PLTindex].time = NowTime;
//				//RTC disable 。pps connect
//				if(GPSBaseTimeFlag)					
//				{
//					//PPS脉冲还没有到					
//					//PLT[PLTindex].time. 
//					PLT[PLTindex].micros= (GPSBaseTime/100)%1000 + DelayUsTime/100;//(((100000-NowTime.micros)/100000)*TimingDelay + TimingDelay)/100;					
//				}
//				else
//				{
//					//PPS脉冲已经到来
//					//PLT[PLTindex].time.
//					PLT[PLTindex].micros = (TimingDelay + GPSBaseTime)%1000 + DelayUsTime/100;
//				}
//		}				
//		
//		PLT[PLTindex].index = PLTindex;
//		PLTindex++;				
//		//Delay_us(100*2);
//		//while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4));
//	}		
}
//用来实现ms定时
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
			TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);    

			if(GPSBaseTimeFlag)
			{
				// usart data come and pps don't  timer 
				GPSBaseTime++;
			}
			TimingDelay++;	
			DelayUsTime = 0;//每次进入 清空us计时器  
			if(TimingDelay > 1010)	
			{				
				//如果ms高于1000 之后 开始启用RTC时钟
				Time_Adjust(NowTime);				//先设置基准时间
				Time_GetValue(RTC_GetCounter()+1);				//再把数据取出来，+1s
				Time_Adjust(getTMforRTC());
				RTC_ENABLE();				//使能RTC中断
				RTCEnableFlag = 1;	
				GPSBaseTimeFlag = 0;	//关闭时间补差，
			}			

			//GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_7)));
	}	
}

void USART1_IRQHandler()
{
	static u8 c[20];
	static int index = 0;
	char buff[50];
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    c[index] = USART1->DR;
			if(c[index-1] == '\r' && c[index] == '\n')
			{
				if(!strcmp((char *)c,"at+print\r\n"))
				{
					index = 0;
					//printf("%s\r\n",c);    //将接受到的数据直接返回打印
					memset((char *)c,'\0',sizeof(c));
//				
					Readflash();
					for(int i =0;i < PLTindex ;i++)
					{
						strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S",&PLT[i].time);					
						printf("%s.%06.2f\r\n",buff,PLT[i].micros);
					}
				}
			}
			else
			{
				index++;
			}
			
	  	
			
	} 
}
static int index = 0;
//判断接下来的数据是不是GNZDA的数据
int isGNZDA(u8 c)
{	
	switch(index)
	{		
		case 0:			
			if(c == 'G')
			{
				index = 1;				
			}
			else
			{
				index = 0;
			}
			break;
		case 1:			
				if(c == 'N')
				{
					index = 2;					
				}
				else
				{
					index = 0;
				}				
			break;
		case 2:			
				if(c == 'Z')
				{
					index = 3;					
				}							
				else
				{
					index = 0;
				}				
			break;
		case 3:			
				if(c == 'D')
				{
					index = 4;					
				}
				else
				{
					index = 0;
				}				
			break;
		case 4:			
				if(c == 'A')
				{
					index = 0;
					return 1;
				}
			  else
				{
					index = 0;
				}
			break;
		default:return 0;
	}	
	return 0;
} 


//解析字符串，获取时间数据
void getNowTime()
{	
	NowTime.tm_hour = (timeArrayforGps[0]-'0' )*10 + timeArrayforGps[1]-'0';
	NowTime.tm_min = (timeArrayforGps[2]-'0' )*10 + timeArrayforGps[3]-'0';
	NowTime.tm_sec = (timeArrayforGps[4]-'0' )*10 + timeArrayforGps[5]-'0';
	NowTime.tm_mday = (timeArrayforGps[9]-'0') *10 + timeArrayforGps[10]-'0';
	NowTime.tm_mon = (timeArrayforGps[11]-'0' )*10 + timeArrayforGps[12]-'0';
	NowTime.tm_year = (timeArrayforGps[13]-'0' )*1000 + (timeArrayforGps[14]-'0') *100 + (timeArrayforGps[15]-'0') *10 + (timeArrayforGps[16]-'0') - 1900;
	//printf("%d-%02d-%02d %02d:%02d:%02d\r\n",NowTime.year,NowTime.month,NowTime.day,NowTime.hour,NowTime.minute,NowTime.second);
	
}
//将GPS传输的时间字符串保存在数组里面
void beginSave(u8 c)
{
	if(c == ',')
		return ;
	timeArrayforGps[timeIndex++] = c;
	
}
void getGNZDAData(u8 c)
{	
	static int flag = 0;
	static int beginRecon = 0;
	if(c == '\r' && flag == 1)			//结束了
	{
		beginRecon = 0;
		flag = 0;
		getNowTime();			
		timeIndex = 0;				
	}
	if(flag)    // 判断是GPZDA数据
	{
		beginSave(c);
	}
	else
	{
		if(c == '$')   //开始进行判断
		{			
			beginRecon = 1;
			return;
		}
		if(beginRecon && isGNZDA(c))  //返回判断结果   
		{		
			GPSBaseTime = 0;
			GPSBaseTimeFlag = 1;			
			flag = 1;					
		}
	}
}
void USART2_IRQHandler()
{		
	static u8 c;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
	    c = USART2->DR;
			//printf("%c",c);
			getGNZDAData(c);			
			
	} 
}

void RTC_IRQHandler(void)
{	
	if(RTC_GetFlagStatus(RTC_IT_SEC) != RESET)
		{  				
				TimingDelay = 0;		
				DelayUsTime = 0;
//				uint32_t TempValue;
        Time_GetValue(RTC_GetCounter());  
//				TempValue=RTC_GetCounter();
//				do
//				{
//					 //CaculateTime();
//					 TempValue -=0x00015180;
//				}while(TempValue > 0x00015180);				
		}
  RTC_ClearITPendingBit(RTC_IT_SEC);  
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

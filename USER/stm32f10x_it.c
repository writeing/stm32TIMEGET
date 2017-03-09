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
#include "usrtConfig.h"
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
extern void TimingDelay_Decrement(void );

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

struct nowTime NowTime={0,0,0,0};

struct pliuTime PLT[20];
int PLTindex = 0;
int timeArray[10];

int updateBaseTime = 0;
volatile u8 timeArrayforGps[50];
static int timeIndex = 0;

volatile u32 TimingDelay; 
volatile int GPSBaseTime = 0;

int GPSBaseTimeFlag = 0;
extern float DelayUsTime;
/* I/O线中断，中断线为PA5 */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) //确保是否产生了EXTI Line中断
	{		
		EXTI_ClearITPendingBit(EXTI_Line5);     //清除中断标志位		
		/**do it***/								
		if(TimingDelay > 960)   //960ms
		{
			timeArray[0] = TimingDelay;		
			timeArray[1] = DelayUsTime;
			
			updateBaseTime = 1;
			//NowTime.micros = TimingDelay;
			GPSBaseTimeFlag = 0;
		}
		else
		{		
			updateBaseTime = 0;
			timeArray[0] = 0;
		}
		TimingDelay = 0;		
		DelayUsTime = 0;
	}  
	// exti6 A6 
//	if(EXTI_GetITStatus(EXTI_Line6) != RESET) //确保是否产生了EXTI Line中断
//	{
//		/*******do it*******/
//		PLT[PLTindex].time = NowTime;
//		PLT[PLTindex].time.micros = (100000-NowTime.micros)/100000*TimingDelay + TimingDelay;
//		PLT[PLTindex].index = PLTindex;
//		PLTindex++;
//		EXTI_ClearITPendingBit(EXTI_Line6);     //清除中断标志位		
//	}
}

void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
			TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);    

			if(GPSBaseTimeFlag)
			{
				GPSBaseTime++;
			}		
			TimingDelay++;	
			DelayUsTime = 0;
			//GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_7)?0:1));
	}	
}
void USART1_IRQHandler()
{
	u8 c;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART1->DR;
	  	printf("%c",c);    //将接受到的数据直接返回打印
			
	} 
}
static int index = 0;
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


void getNowTime()
{	
	NowTime.hour = (timeArrayforGps[0]-'0' )*10 + timeArrayforGps[1]-'0';
	NowTime.minute = (timeArrayforGps[2]-'0' )*10 + timeArrayforGps[3]-'0';
	NowTime.second = (timeArrayforGps[4]-'0' )*10 + timeArrayforGps[5]-'0';
	NowTime.day = (timeArrayforGps[9]-'0') *10 + timeArrayforGps[10]-'0';
	NowTime.month = (timeArrayforGps[11]-'0' )*10 + timeArrayforGps[12]-'0';
	NowTime.year = (timeArrayforGps[13]-'0' )*1000 + (timeArrayforGps[14]-'0') *100 + (timeArrayforGps[15]-'0') *10 + (timeArrayforGps[16]-'0');
	
	//printf("%d-%02d-%02d %02d:%02d:%02d\r\n",NowTime.year,NowTime.month,NowTime.day,NowTime.hour,NowTime.minute,NowTime.second);
	
}
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
			//printf("%c",c);
			/*if(c[0] == '\r')
			{
				i++;				
			}
			if(c[0] == '\r' && c[1] == '\n')
			{
				printf("xwxc\n");   
				i = 0;
			}*/
			
	} 
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

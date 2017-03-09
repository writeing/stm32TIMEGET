
#include "stm32f10x.h"
#include "usrtConfig.h"
#include "sysdelay.h"
#include "exti.h"
//#include "led.h"

/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
extern volatile u32 TimingDelay;
extern int printFlag;
extern int timeArray[10];
extern int i;
extern u32 msTime ;
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
		/*********/
	  /***led init****/
		//LED_GPIO_Config();
		//GPIO_Config();
	  /***************/
		while(1)
		{
			//printf("this is stm32 usart\r\n");
			//LED2( OFF );
			//Delay_us(); //100us  延时
			//LED2( ON );
			// Delay_us(10);		
			if(timeArray[0])
			{
				printf("%d\r\n",timeArray[0]);
				timeArray[0] = 0;				
			}
				
			//printf("%d\r\n",i);	
//			Delay_us(20);
//			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
//			{									
//				  //printf("wxc \r\n");
//				
//					timeArray[0] = TimingDelay;
//					printf("us1 = %d\r\n",timeArray[0]);
//					TimingDelay = 0;
//					Delay_us(10000);				
//			}
//			if(i ==  10)
//			{
//				i = 0;
//				printf("us1 = %d\r\n",timeArray[2]);
//				printf("us2 = %d\r\n",timeArray[3]);
//				printf("us3 = %d\r\n",timeArray[4]);
//				printf("us4 = %d\r\n",timeArray[5]);
//				printf("us5 = %d\r\n",timeArray[6]);
//			}
			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/



#include "sysdelay.h"

volatile u32 TimingDelay;
volatile u32 delayTime;
/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick
 * ����  ����
 * ���  ����
 * ����  ���ⲿ���� 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
		// �رյδ�ʱ��  
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}


/*
 * ��������Delay_us
 * ����  ��us��ʱ����,10usΪһ����λ
 * ����  ��- nTime
 * ���  ����
 * ����  ��Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
 *       ���ⲿ���� 
 */

void Delay_us(__IO u32 nTime)
{ 
	delayTime = nTime;
	// ʹ�ܵδ�ʱ��  
	//SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(delayTime != 0);

}


/*
 * ��������TimingDelay_Decrement
 * ����  ����ȡ���ĳ���
 * ����  ����
 * ���  ����
 * ����  ���� SysTick �жϺ��� SysTick_Handler()����
 */ 
//volatile u32 queryPlise = 0;
//u32 msTime = 0;
//void quePlise()
//{
//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
//		{		
//				Delay_us(20);				
//				msTime = TimingDelay;  
//				TimingDelay = 0;						
//				//while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4));
//				//printf("wxc \r\n");													
//		}
//		queryPlise = 0;
//}
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
//	if(queryPlise == 10 )
//	{
//		quePlise();
//	}
	if (delayTime != 0x00)
	{ 
		delayTime--;
	}	
	TimingDelay++;	
//	queryPlise++;
}
/******
auth:wxc
date:2017.03.09
content:add TIM2 get ms time add systick get us time
        使用轮询法查询外部脉冲，但是脉冲不规范，采用延时法防抖
				在中断函数里面实时获取时间，然后在main函数里面计算和打印，			

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
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
 
 void OutPutFile(void)
{ 
//  unsigned int a;
//  FRESULT res;
//  FILINFO finfo;
  DIR dirs;
	FIL fil;
  char path[50]={""};  
	UINT count;
  FATFS fs;
 // disk_initialize(0);
    
  f_mount(0, &fs);
	//f_open(&fil,"wang.txt",FA_CREATE_ALWAYS | FA_WRITE);
	//f_write(&fil,"wadadasdsa",11,&count);
//	printf("count = %d\r\n",count);
//	if (f_opendir(&dirs, path) == FR_OK) 
//  {
//  	printf("open dir success\n");
//    while (f_readdir(&dirs, &finfo) == FR_OK)  
//    {
//			printf("read dir OK\n");
//      if (finfo.fattrib & AM_ARC) 
//      {
//        if(!finfo.fname[0])	
//          break;         
        //printf("\r\n file name is:\n   %s\n",finfo.fname);
				//strcat(finfo.fname,(char *)"wang.txt");
				f_open(&fil,"AREA\\waaag.txt",FA_CREATE_ALWAYS | FA_WRITE);				
				f_write(&fil,"wwxc",11,&count);
//				printf("file size = %ld",fil.fsize);
        //res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
				f_close(&fil);                      
//      }
//    } 
    
//  }
  //f_close(&fil); 
  while(1);
}
 /**
  * @brief  Configures SDIO IRQ channel.
  * @param  None
  * @retval None
  */
 void NVIC_ConfigurationSPIO(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
//struct pliuTime savePIL[20] __attribute__((at(0x08050000)));// flashCount __attribute__ ((at(0x08037000)));
//int savePltindex[20] __attribute__((at(0x08040000))) = {1,2,3,4,5,6,7,8,9,0};//((section("NO_INIT"),zero_init));
int main(void)
{
//		static int i=0;
//		char buff[50];

		/****usart1 init******/
//		USART1_Config();
//		NVIC_Configuration();
		/********/
		/*********SPIO *********/
		NVIC_ConfigurationSPIO();
		/****usart1 init******/
//		USART2_Config();
//		NVIC_Configuration2();
		/********/
		/***RTC******/
//		RTC_Configuration();
		/*************/
		/* TIM2 定时配置 */
//		TIM2_NVIC_Configuration();
//    TIM2_Configuration();

		/* TIM2 开始计时 */
//		START_TIME;			  
	  /***led init****/
//		LED_GPIO_Config();
//		GPIO_Config();
	  /***************/
		/****sys init*****/
//		SysTick_Init();
	  /*********/
		/***exit init******/
//		EXTI_PA5_Config();
//		EXTI_PA6_Config();
		/*********/		
		//readFlashInit();
//		char buff[50]={0};
//		int index = 0;
		OutPutFile();
		while(1)
		{
			if(timeArray[0])
			{													
				//printf("%d.%d\r\n",timeArray[0],timeArray[1]);
				printf("%d.%d\r\n",getTimeValuePPS().tm_sec,PLTindex);
				timeArray[0] = 0;				
			} 	
//			while(PLTindex-1)
//			{
//				PLTindex--;//%R %T
//				strftime(buff,sizeof(buff),"%F %T",&PLT[PLTindex].time);//%Y-%m-%d %H:%M:%S
//				//printf("%4d-%02d-%02d %02d:%02d:%02d",PLT[PLTindex].time.tm_year+1900,PLT[PLTindex].time.tm_mon,PLT[PLTindex].time.tm_mday,PLT[PLTindex].time.tm_hour,PLT[PLTindex].time.tm_min,PLT[PLTindex].time.tm_sec);				
//				printf("%s.%06.2f\r\n",buff,PLT[PLTindex].micros);
//			}
			Delay_us(10);	
			if(PLTindex == SAVECOUNT+1)
			{		
				//Writeflash(PLT);
				memset(PLT,0,sizeof(PLT));
				PLTindex = 1;
			}			
		}
	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

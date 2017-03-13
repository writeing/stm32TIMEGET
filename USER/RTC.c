

#include "RTC.h"
u8 IRTYear,IRTMonth,IRTDay,IRTHour,IRTMinute,IRTSecond;
u8 RTCEnableFlag = 0;
struct tm RTCTimeTM;
void Time_Adjust(struct tm data)
{
	//struct tm when = data;
	time_t now;
//    when.tm_sec= data[5];
//    when.tm_min= data[4];
//    when.tm_hour= data[3];
//    when.tm_mday= data[2];
//    when.tm_mon= data[1];
//    when.tm_year= data[0];
//    when.tm_wday= 0;
//    when.tm_isdst= 0;
	now = mktime(&data);
	IRTYear = data.tm_year;
	IRTMonth = data.tm_mon;
	IRTDay = data.tm_mday;
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask(); 
  /* Change the current time */
  RTC_SetCounter(now);
//  RTC_SetCounter(0xfffffff0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();   

	RTC_ITConfig(RTC_IT_SEC,DISABLE);	//关闭定时器  
	
	RTC_WaitForLastTask();
}

//u8 IRTYear,IRTMonth,IRTDay,IRTHour,IRTMinute,IRTSecond;
struct tm getTMforRTC()
{
	RTCTimeTM.tm_year = IRTYear;
	RTCTimeTM.tm_mon = IRTMonth;
	RTCTimeTM.tm_mday = IRTDay;
	RTCTimeTM.tm_hour = IRTHour;
	RTCTimeTM.tm_min = IRTMinute;
	RTCTimeTM.tm_sec = IRTSecond;
	return RTCTimeTM;
}
void RTC_ENABLE()
{
	RTC_WaitForLastTask();   

	RTC_ITConfig(RTC_IT_SEC,ENABLE);	//打开定时器  
	
	RTC_WaitForLastTask();
}
void RTC_DISABLE()
{
	RTC_WaitForLastTask();   

	RTC_ITConfig(RTC_IT_SEC,DISABLE);	//close timer 
	
	RTC_WaitForLastTask();
}
void Time_Display(struct tm when)
{ 
//    static struct tm when;
//    time_t now;

//    now = (time_t)TimeVar; //TimeVar?RTCCcounter???
//    when = *localtime( &now );
   // printf( "Current time is %s ", asctime( &when ) );

}
//void RTC_CONFIG(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);  //打开总线时钟
//	PWR_BackupAccessCmd(ENABLE);					//打开寄存器写入
//	RTC_ITConfig(RTC_IT_SEC,DISABLE);			//  秒定时器，中断打开
//	RTC_WaitForLastTask();  
//	
//	RCC_LSEConfig(RCC_LSE_ON);            // 打开LES时钟
//	RTC_WaitForSynchro(); 
//	
//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);			//外部时钟LSE
//	RTC_WaitForSynchro(); 
//	
//	RCC_RTCCLKCmd(ENABLE);									//使能外部时钟
//	RTC_WaitForLastTask();  
//	
//	RTC_SetPrescaler(8000);								//预分频
//	RTC_WaitForLastTask();  
//		
//}

static void NVIC_Configuration(void)  
{  
    NVIC_InitTypeDef NVIC_InitStructure;  
  
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
  
}  


void RTC_Configuration(void)  
{  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);  //打开总线时钟
    PWR_BackupAccessCmd(ENABLE);  
    BKP_DeInit();  
    RCC_LSEConfig(RCC_LSE_ON);  
    while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);  
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
    RCC_RTCCLKCmd(ENABLE);  
  
    RTC_WaitForSynchro();     
  
  	RTC_ITConfig(RTC_IT_SEC,ENABLE);  
		RTC_WaitForLastTask();
  
    RTC_SetPrescaler(32767);  
    RTC_WaitForLastTask();  
		
		NVIC_Configuration();
} 


//const u8 MaxDayArray[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //


void Time_GetValue(u32 TimeVar) 
{
  u32 THH = 0, TMM = 0, TSS = 0;
  /* Compute  hours */
  THH = TimeVar/3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600)/60;
  /* Compute seconds */
  TSS = (TimeVar % 3600)% 60;
  IRTHour=(u8)THH;
  IRTMinute=(u8)TMM;
  IRTSecond=(u8)TSS;
}
//Time_GetValue(RTC_GetCounter());

/*CaculateTime :Caculate new Time*/
/*void CaculateTime(void)
{
    u32 IYear;
    IYear=2000+IRTYear;
    if(2==IRTMonth) { //
        IRTDay++;
        if((IYear%4==0&&IYear%100!=0)||(IYear%400==0)) { //leap year
            if ((IRTDay>MaxDayArray[IRTMonth-1]+1)) {
                //Day overflow
                IRTDay=1;
                IRTMonth++;
                if(IRTMonth>12) {
                    //Month overflow
                    IRTMonth=1;
                    IRTYear++;
                    if (IRTYear>99) {
                        //Year overflow
                        IRTYear=0;
                    }
                }
            }
        } else { //no leap year
            if ((IRTDay>MaxDayArray[IRTMonth-1])) {
                IRTDay=1;
                IRTMonth++;
                if(IRTMonth>12) {
                    //Month overflow
                    IRTMonth=1;
                    IRTYear++;
                    if (IRTYear>99) {
                        //Year overflow
                        IRTYear=0;
                    }
                }
            }
        }
    } else { //
        IRTDay++;
        if ((IRTDay>MaxDayArray[IRTMonth-1])) {
            IRTDay=1;
            IRTMonth++;
            if(IRTMonth>12) {
                //Month overflow
                IRTMonth=1;
                IRTYear++;
                if (IRTYear>99) {
                    //Year overflow
                    IRTYear=0;
                }
            }        
        }
    }
}*/
//TempValue=RTC_GetCounter();
//do while(TempValue > 0x00015180);
//{
//		 //
//		 CaculateTime();
//		 TempValue -=0x00015180;
//}



#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f10x.h"
#include "time.h"

void RTC_Configuration(void);
void Time_Adjust(struct tm data);
void Time_GetValue(u32 TimeVar);
void CaculateTime(void);
void RTC_ENABLE(void);
struct tm getTMforRTC(void);
void RTC_DISABLE(void);
void Time_sysValue(void );
struct tm getTimeValuePPS(void);
extern u8 IRTYear,IRTMonth,IRTDay,IRTHour,IRTMinute,IRTSecond;
extern u8 RTCEnableFlag;
#endif



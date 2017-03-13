#ifndef __SYSDELAY_H_
#define __SYSDELAY_H_

#include "stm32f10x.h"
#include "stm32f10x_it.h"
void SysTick_Init(void);
void Delay_us(__IO u32 nTime);

extern int GPSBaseTimeFlag;
extern volatile float DelayUsTime;
#endif /* __SYSDELAY_H_ */

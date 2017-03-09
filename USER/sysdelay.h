#ifndef __SYSDELAY_H_
#define __SYSDELAY_H_

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);

extern int GPSBaseTimeFlag;
#endif /* __SYSDELAY_H_ */

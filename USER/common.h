#ifndef __COMMON_H_
#define __COMMON_H_
#include "usrtConfig.h"
#include "stm32f10x.h"
#include "time.h"
#define PLTARRAY   40	 
#define SAVECOUNT   32
struct pliuTime
{
	struct tm time;	
	//struct pliuTime *next;
	int index;
	float micros;
};

#endif /*common*/


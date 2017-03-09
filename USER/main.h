#ifndef __MAIN_H_
#define __MAIN_H_
#include "stm32f10x.h"
#include "usrtConfig.h"
#include "sysdelay.h"
#include "exti.h"
#include "led.h"
#include "Tim.h"
//#include "common.h"
/**************************************/
//begin:add by wxc in 2017.03.09  def value for para to main
struct nowTime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	float micros;
};

struct pliuTime
{
	struct nowTime time;	
	//struct pliuTime *next;
	int index;
};


//end:add by wxc in 2017.03.09  def value for para to main
/**************************************/
#endif /*MIAN*/


#ifndef __MAIN_H_
#define __MAIN_H_
#include "usrtConfig.h"
#include "sysdelay.h"
#include "exti.h"
#include "led.h"
#include "Tim.h"
#include "RTC.h"
#include "stm32f10x_it.h"
//#include "common.h"
/**************************************/
//begin:add by wxc in 2017.03.09  def value for para to main
//struct nowTime
//{
//	int year;
//	int month;
//	int day;
//	int hour;
//	int minute;
//	int second;
//	float micros;
//};
struct pliuTime
{
	struct tm time;	
	//struct pliuTime *next;
	int index;
	float micros;
};


//end:add by wxc in 2017.03.09  def value for para to main
/**************************************/
#endif /*MIAN*/


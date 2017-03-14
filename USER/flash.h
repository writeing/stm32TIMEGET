#ifndef __FLASH_H_
#define __FLASH_H_
#include "stm32f10x.h"
//#include "main.h"
#include "common.h"
void Writeflash(struct pliuTime *data);
void Readflash(void);
void readFlashInit(void );
extern int count;

#endif  /*__FLASH_H_*/

#ifndef __FLASH_H_
#define __FLASH_H_
#include "stm32f10x.h"
#include "main.h"

extern void Writeflash(struct pliuTime *data);
extern void Readflash(void);
extern void readFlashInit(void );





#endif  /*__FLASH_H_*/

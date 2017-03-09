#ifndef __USARTCONFIG_H
#define	__USARTCONFIG_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Config(void);
void NVIC_Configuration(void);
void USART2_Config(void);
void NVIC_Configuration2(void);
int fputc(int ch, FILE *f);

#endif /* __USARTCONFIG_H */

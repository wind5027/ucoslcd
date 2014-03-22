#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"

#define ADC1_DR_Address ((u32)0x40012400+0x4c);
extern  u16 ADC1_ConvertValue[6];

void ADC_GPIO_Config(void);
void ADC_DMA_Config(void);
void ADC_MODE_Config(void);
void ADC_Clock_Config(void);
void ADC_Config(void);

#endif


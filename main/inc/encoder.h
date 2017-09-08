#ifndef ENCODER_H
#define ENCODER_H
 
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
void encoder_ini(void);
uint8_t getEnc_Counter(void);
void Systick_Enc(void);
void encoder_ini2(void);
#endif

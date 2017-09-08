#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define A0_RCC_FUNC RCC_AHB1PeriphClockCmd
#define A0_RCC 			RCC_AHB1Periph_GPIOE
#define A0_PIN			GPIO_Pin_7
#define A0_PORT			GPIOE

#define A1_RCC_FUNC RCC_AHB1PeriphClockCmd
#define A1_RCC 			RCC_AHB1Periph_GPIOE
#define A1_PIN			GPIO_Pin_8
#define A1_PORT			GPIOE

#define A2_RCC_FUNC RCC_AHB1PeriphClockCmd
#define A2_RCC 			RCC_AHB1Periph_GPIOE
#define A2_PIN			GPIO_Pin_9
#define A2_PORT			GPIOE

#define A3_RCC_FUNC RCC_AHB1PeriphClockCmd
#define A3_RCC 			RCC_AHB1Periph_GPIOE
#define A3_PIN			GPIO_Pin_10
#define A3_PORT			GPIOE

#define B0_RCC_FUNC RCC_AHB1PeriphClockCmd
#define B0_RCC 			RCC_AHB1Periph_GPIOE
#define B0_PIN			GPIO_Pin_11
#define B0_PORT			GPIOE

#define B1_RCC_FUNC RCC_AHB1PeriphClockCmd
#define B1_RCC 			RCC_AHB1Periph_GPIOE
#define B1_PIN			GPIO_Pin_12
#define B1_PORT			GPIOE

#define B2_RCC_FUNC RCC_AHB1PeriphClockCmd
#define B2_RCC 			RCC_AHB1Periph_GPIOE
#define B2_PIN			GPIO_Pin_13
#define B2_PORT			GPIOE

#define B3_RCC_FUNC RCC_AHB1PeriphClockCmd
#define B3_RCC 			RCC_AHB1Periph_GPIOE
#define B3_PIN			GPIO_Pin_14
#define B3_PORT			GPIOE

#define A0_HIGH			GPIO_SetBits(A0_PORT, A0_PIN)
#define A0_LOW      GPIO_ResetBits(A0_PORT, A0_PIN)

#define A1_HIGH			GPIO_SetBits(A1_PORT, A1_PIN)
#define A1_LOW      GPIO_ResetBits(A1_PORT, A1_PIN)

#define A2_HIGH			GPIO_SetBits(A2_PORT, A2_PIN)
#define A2_LOW      GPIO_ResetBits(A2_PORT, A2_PIN)

#define A3_HIGH			GPIO_SetBits(A3_PORT, A3_PIN)
#define A3_LOW      GPIO_ResetBits(A3_PORT, A3_PIN)


#define B0_INPUT				GPIO_ReadInputDataBit(B0_PORT, B0_PIN)
#define B1_INPUT				GPIO_ReadInputDataBit(B1_PORT, B1_PIN)
#define B2_INPUT				GPIO_ReadInputDataBit(B2_PORT, B2_PIN)
#define B3_INPUT				GPIO_ReadInputDataBit(B3_PORT, B3_PIN)

#define KEY_SENSE				2
void Keyboard_ini(void);
uint8_t  read_keyboard(void);
#endif

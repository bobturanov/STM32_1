#ifndef LCD_H
#define LCD_H

#include "mcu_ini.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void delay(int a);
void PulseLCD();
void SendByte(char ByteToSend, int IsData);
void Cursor(char Row, char Col);
void ClearLCDScreen();
void InitializeLCD(void);
void PrintStr(char *Text);


#endif
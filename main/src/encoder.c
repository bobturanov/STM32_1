#include "encoder.h"

#define Read_Enc_A			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define Read_Enc_B			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)

#define	ENC_MAX					3

uint8_t Enc_counter=0;
uint8_t Enc_Mode=0;
//----------------------------------------------------
void encoder_ini(void)
{
	GPIO_InitTypeDef GPIO_Enc_Ini;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Enc_Ini.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Enc_Ini.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Enc_Ini.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Enc_Ini.GPIO_OType = GPIO_OType_PP;
	GPIO_Enc_Ini.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA, &GPIO_Enc_Ini);
}

//----------------------------------------------------
void encoder_ini2(void)
{
	GPIO_InitTypeDef GPIO_Enc_Ini;
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	//GPIO INI
	GPIO_Enc_Ini.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Enc_Ini.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Enc_Ini.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Enc_Ini.GPIO_OType = GPIO_OType_PP;
	GPIO_Enc_Ini.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	
	GPIO_Init(GPIOC, &GPIO_Enc_Ini);
	
	//TIM3 Ini
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 256;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3, &TIM_Time_user);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3, ENABLE);
}

//----------------------------------------------------
uint8_t Enc_A_count=0;
uint8_t Enc_A_state=0;

uint8_t Enc_B_count=0;
uint8_t Enc_B_state=0;

void Systick_Enc(void)
{
	if (Read_Enc_A == 1)
	{
		if (Enc_A_count < ENC_MAX)
		{
			Enc_A_count++;
		} else {
			if (Enc_A_state == 0)
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter++;
				} else {
					Enc_Mode = 0;
					Enc_counter--;
				}
			}
			Enc_A_state = 1;
		}
	} else {
		if (Enc_A_count > 0)
		{
			Enc_A_count--;
		} else {
			if (Enc_A_state == 1)	
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter++;
				} else {
					Enc_Mode = 0;
					Enc_counter--;
				}
			}
			Enc_A_state = 0;
		}
	}
	
	if (Read_Enc_B == 1)
	{
		if (Enc_B_count < ENC_MAX)
		{
			Enc_B_count++;
		} else {
			if (Enc_B_state == 0)
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter--;
				} else {
					Enc_Mode = 0;
					Enc_counter++;
				}
			}
			Enc_B_state = 1;
		}
	} else {
		if (Enc_B_count > 0)
		{
			Enc_B_count--;
		} else {
			if (Enc_B_state == 1)	
			{
				if (Enc_Mode == 0)
				{
					Enc_Mode = 1;
					Enc_counter--;
				} else {
					Enc_Mode = 0;
					Enc_counter++;
				}
			}
			Enc_B_state = 0;
		}
	}
}

//----------------------------------------------------
uint8_t getEnc_Counter(void)
{
	//return Enc_counter;
	return TIM3->CNT;
}

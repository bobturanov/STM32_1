#include "keyboard.h"

uint8_t Key_Count=0;

uint8_t Key_input[4][4]={0};
uint8_t Key_input_filter[4][4]={0};
uint8_t Key_input_count[4][4]={0};

void Keyboard_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	
	A0_RCC_FUNC(A0_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = A0_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(A0_PORT, &GPIO_Init_LED);
	
	A1_RCC_FUNC(A1_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = A1_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(A1_PORT, &GPIO_Init_LED);
	
	A2_RCC_FUNC(A2_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = A2_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(A2_PORT, &GPIO_Init_LED);
	
	A3_RCC_FUNC(A3_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = A3_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(A3_PORT, &GPIO_Init_LED);
	
	
	B0_RCC_FUNC(B0_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = B0_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(B0_PORT, &GPIO_Init_LED);
	
	B1_RCC_FUNC(B1_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = B1_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(B1_PORT, &GPIO_Init_LED);
	
	B2_RCC_FUNC(B2_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = B2_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(B2_PORT, &GPIO_Init_LED);
	
	B3_RCC_FUNC(B3_RCC, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = B3_PIN;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(B3_PORT, &GPIO_Init_LED);
}

//-----------------------------------------------------
void Change_Pins(void)
{
	Key_Count = (Key_Count+1)%4;
	
	if (Key_Count == 0)
	{
		A0_HIGH;
		A1_LOW;
		A2_LOW;
		A3_LOW;
	} else if (Key_Count == 1) {
		A1_HIGH;
		A0_LOW;
		A2_LOW;
		A3_LOW;
	} else if (Key_Count == 2) {
		A2_HIGH;
		A1_LOW;
		A0_LOW;
		A3_LOW;
	} else if (Key_Count == 3) {
		A3_HIGH;
		A1_LOW;
		A2_LOW;
		A0_LOW;
	}
}

//------------------------------------------------
void Key_read(void)
{
	Key_input[Key_Count][0] = B0_INPUT;
	Key_input[Key_Count][1] = B1_INPUT;
	Key_input[Key_Count][2] = B2_INPUT;
	Key_input[Key_Count][3] = B3_INPUT;
}

//------------------------------------------------
void key_one_filter(uint8_t x, uint8_t y)
{
	if (Key_input[x][y] == 1)
	{
		if (Key_input_count[x][y] < KEY_SENSE)
		{
			Key_input_count[x][y]++;
		} else {
			Key_input_filter[x][y] = 1;
		}
	} else {
		if (Key_input_count[x][y] > 0)
		{
			Key_input_count[x][y]--;
		} else {
			Key_input_filter[x][y] = 0;
		}
	}
}

//------------------------------------------------
void All_buttons_filter(void)
{
	uint8_t i,j;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			key_one_filter(i,j);
		}
	}
}

//------------------------------------------------
uint8_t read_button(void)
{
	uint8_t i,j, k=0;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			k++;
			if (Key_input_filter[i][j] == 1)
			{
				return k;
			}
		}
	}
	return 0;
}

//------------------------------------------------
uint8_t  read_keyboard(void)
{
	uint8_t answer=0;
	
	Key_read();
	if (Key_Count == 3)
	{
		All_buttons_filter();
	}
	Change_Pins();
	answer = read_button();
	return answer;
}

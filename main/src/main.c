#include "main.h"
#include "lcd.h"
#include <stdio.h>
#include <math.h> 
//uint16_t delay_count=0;


//void SysTick_Handler(void)//1ms
//{
//	if (delay_count > 0)
//	{
//		delay_count--;
//	}
//}

//void delay_ms(uint16_t delay_temp)
//{
//	delay_count = delay_temp;
//	
//	while(delay_count){}
//}
uint16_t delay_count1=0;
int key_num = 0;
int key_num_old = 0;
int ans;
char key_num_str[12];
char str[17];
short flag = 0;
short flag_act = 0;
short flag_once = 0;
short flag_reiteration = 0;
short flag_divide = 0;
short count_divide = 0;
int a = 0;
int b = 0;
char oper = 0;
float tmp = 0;

 
void SysTick_Handler(void)//1ms
{
	if (delay_count1 > 0)
	{
		delay_count1--;
	}
	Systick_Enc();
	key_num = read_keyboard();
}

void delay_ms(uint16_t delay_temp)
{

	delay_count1 = delay_temp;
	
	while(delay_count1){}
}

void out_print (uint16_t sim)
{
	//str += sim;
	
	Cursor(0,0);
	delay_ms(30);
	ClearLCDScreen();
	delay_ms(30);
	//printf(key_num_str, "%d", sim);
	PrintStr("asa");
} 

void var_act (short var)
{
	if (!flag_act)
			{
				if (!flag_once)
				{
					a += var;
					flag_once= 1;
				}
				else
				{
					a = a * 10 + var;
				}
			}
			else
				{
				if (!flag_once)
				{
					b += var;
					flag_once= 1;
				}
				else
				{
					b = b * 10 + var;
				}
			}
}
void act_without_print (char operat)             //_----------------------TUT! x = 8.123456;
                                                               //fractpart = modf(x, &intpart);

{
	
		if (flag_divide == 0){
					if (operat == '*')
				{
					a = a * b;
				
				} else if (operat == '/')
				{
					
					tmp = (float)a / (float)b;
					
				} else if (operat == '+')
				{
					a =  a + b;
					
				} else if (operat == '-')
				{
					a = a - b;
					
				}
			}
		else 
		{
			if (count_divide == 1)
			{
				tmp = (float)a;
				count_divide = 100;
			}
			
				if (operat == '*')
				{
					tmp = tmp * (float)b;
				
				} else if (operat == '/')
				{
					
					tmp = tmp / (float)b;
					
				} else if (operat == '+')
				{
					tmp =  tmp + (float)b;
					
				} else if (operat == '-')
				{
					tmp = tmp - (float)b;
		}				
	}
}




void act (char operat)             //_----------------------TUT! x = 8.123456;
                                                               //fractpart = modf(x, &intpart);

{
if (flag_divide == 0){
					if (operat == '*')
				{
					sprintf(str, "%d", a * b);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				} else if (operat == '/')
				{
					if (count_divide <= 1)
					{
							tmp = (float)a;
					}
					tmp = tmp / (float)b;
					sprintf(str, "%f", tmp);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				
				} else if (operat == '+')
				{
					sprintf(str, "%d", a + b);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				} else if (operat == '-')
				{
					sprintf(str, "%d", a - b);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				}
	} 
	else
	{
		if (count_divide <= 1)
					{
							tmp = (float)a;
					}
		if (operat == '*')
				{
					tmp = tmp * (float)b;
					sprintf(str, "%f", tmp);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				} else if (operat == '/')
				{
					
					
					
					tmp = tmp / (float)b;
					sprintf(str, "%f", tmp);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				
				} else if (operat == '+')
				{
					tmp = tmp + (float)b;
					sprintf(str, "%f", tmp);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				} else if (operat == '-')
				{
					tmp = tmp * (float)b;
					sprintf(str, "%f", tmp);
					Cursor(1,0);
					delay_ms(30);
					PrintStr(str);
				}
	}
}

int main(void)
{
	  SystemCoreClockUpdate();
		SysTick_Config(SystemCoreClock/1000);//1 ms
	  //SysTick_lib();
		//SysTick_Config(SystemCoreClock/1000);//1 ms
		Keyboard_ini();
    InitializeLCD(); //????????????? ???????
		delay_ms(30);
    ClearLCDScreen();	//??????? ??????? ?? ??????
	delay_ms(30);
    Cursor(0,0);	//????????? ???????
	delay_ms(40);
    PrintStr("Calculator"); //????????? ??????
	delay_ms(40);
    Cursor(1,3);
	delay_ms(30);
    PrintStr("STM32");
	delay_ms(3000);
		LEDs_init();
		RED_ON();
	//	delay(500);
		ClearLCDScreen();
	delay_ms(30);
    Cursor(0,0);
		char key_num_str[12];
		RED_OFF();
		
		while(1)
    {
			if (key_num == 1)
		{
			if (!flag)
			{	
			RED_ON();
			PrintStr("1");
			flag_reiteration = 0;
			var_act(1);
			flag = 1;
			}
		}else if (key_num == 2) {
			if (!flag)
			{	
			BLUE_ON();
				PrintStr("4");
				flag_reiteration = 0;
				var_act(4);
			flag = 1;
			}
		} else if (key_num == 3) {
			if (!flag)
			{	
			GREEN_ON();
			PrintStr("7");
				flag_reiteration = 0;
				var_act(7);
			flag = 1;
			}
		} else if (key_num == 4) {
			if (!flag)
			{	
			YELLOW_ON();
			if (!flag_reiteration){
			PrintStr("*");
			if (flag_act)
			{	
				act_without_print(oper);                   //_----------------------TUT!
				b = 0;
				flag_once= 0;
			}
			oper = '*';
			
			flag_act = 1;
			flag = 1;
			flag_reiteration = 1;
		}
			}
		}
			if (key_num == 5)
		{
			if (!flag)
			{	
			RED_ON();
			PrintStr("2");
				flag_reiteration = 0;
				var_act(2);
			flag = 1;
			}
		}else if (key_num == 6) {
			if (!flag)
			{	
			BLUE_ON();
			
			PrintStr("5");// -  - -- - - --TEST sprintf(str, "%d", a);
			flag_reiteration = 0;
				var_act(5);
				flag = 1;
			}
		} else if (key_num == 7) {
			if (!flag)
			{	
			GREEN_ON();
			PrintStr("8");
				flag_reiteration = 0;
				var_act(8);
			flag = 1;
			}
		} else if (key_num == 8) {
			if (!flag)
			{	
			YELLOW_ON();
				PrintStr("0");
				flag_reiteration = 0;
				var_act(0);
			flag = 1;
			}
		}
			if (key_num == 9)
		{
			if (!flag)
			{	
			RED_ON();
			PrintStr("3");
				flag_reiteration = 0;
				var_act(3);
			flag = 1;
			}
		}else if (key_num == 10) {
			if (!flag)
			{	
			BLUE_ON();
				PrintStr("6");
				flag_reiteration = 0;
				var_act(6);
			flag = 1;
			}
		} else if (key_num == 11) {
			if (!flag)
			{	
			GREEN_ON();
			PrintStr("9");
flag_reiteration = 0;
				var_act(9);
			flag = 1;
			}
		} else if (key_num == 12) {
			if (!flag)
			{	
			YELLOW_ON();
			if (!flag_reiteration){
				PrintStr("/");
				flag_divide = 1;
				count_divide ++;
				if (flag_act)
			{	
				act_without_print(oper);                      //_----------------------TUT!
				b = 0;
				flag_once= 0;
			}
			//else count_divide --;
				flag_act = 1;
				oper = '/';
			flag = 1;
			flag_reiteration = 1;
			}
		}
	}
			if (key_num == 13)
		{
			if (!flag)
			{	
			RED_ON();
			ClearLCDScreen();
			delay_ms(300);
			Cursor(0,0);
			flag = 1;
			flag = 0;
			flag_act = 0;
			flag_once= 0;
			a = 0;
			b = 0;
			tmp = 0;
			oper = 0;
			flag_reiteration = 0;
		  flag_divide = 0;
			count_divide = 0;
			}
		}else if (key_num == 14) {
			if (!flag)
			{	
			BLUE_ON();
				if (!flag_reiteration){
				PrintStr("+");
				if (flag_act)
			{	
				act_without_print(oper);                      //_----------------------TUT!
				b = 0;
				flag_once= 0;
			}
				flag_act = 1;
				oper = '+';
			flag = 1;
			flag_reiteration = 1;
				}
			
			}
		} else if (key_num == 15) {
			if (!flag)
			{	
			GREEN_ON();
			if (!flag_reiteration){
			PrintStr("-");
				if (flag_act)
			{	
				act_without_print(oper);                      //_----------------------TUT!
				b = 0;
				flag_once= 0;
			}
				flag_act = 1;
				oper = '-';
			flag = 1;
			flag_reiteration = 1; 
			}
			}
		} else if (key_num == 16) {//-------------------------OSOBAYA!
			if (!flag)
			{	
			YELLOW_ON();
				PrintStr("=");
				act(oper);
//				if (oper == '*')      //_----------------------TUT!
//				{
//					sprintf(str, "%d", a * b);
//					Cursor(1,0);
//					delay_ms(30);
//					PrintStr(str);
//				} else if (oper == '/')
//				{
//					float tmp;
//					tmp = (float)a / (float)b;
//					sprintf(str, "%f", tmp);
//					Cursor(1,0);
//					delay_ms(30);
//					PrintStr(str);
//				} else if (oper == '+')
//				{
//					sprintf(str, "%d", a + b);
//					Cursor(1,0);
//					delay_ms(30);
//					PrintStr(str);
//				} else if (oper == '-')
//				{
//					sprintf(str, "%d", a - b);
//					Cursor(1,0);
//					delay_ms(30);
//					PrintStr(str);
//				}
				
				
//				sprintf(str, "%d", a);
//				delay_ms(30);
//				Cursor(1,0);
//				delay_ms(30);
//				PrintStr(str);
//				delay_ms(30);
//				sprintf(str, "%d", b);
//				Cursor(1,7);
//				delay_ms(30);
//				PrintStr(str);
			flag = 1;
			}
		}
		else {
			//ClearLCDScreen();
			delay_ms(300);
			flag = 0;
			RED_OFF();
			BLUE_OFF();
			GREEN_OFF();
			YELLOW_OFF();
		} 
		}
}
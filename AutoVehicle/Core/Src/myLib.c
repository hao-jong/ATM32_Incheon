#include "main.h"
#include <stdio.h>


extern UART_HandleTypeDef huart2;

int __io_getchar(void)
{
	int ch;
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK)
	{
		return ch;
	}
}

int __io_putchar(int ch)
	{
		HAL_UART_Transmit(&huart2, &ch, 1, 10);
		return ch;
	}

void Standby()
{
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin));
}
void cls()
{
	printf("\033[2j");

}
void Cursor(int x, int y)
{
	char buf [20];
	sprintf(buf,"\033[%d;%dH",y,x);
	puts(buf);
}
void ProgramStart (char * str)
{
	cls();
	Cursor(0,0);
	printf("Program Start - %s\r\n",str);
	printf("Press Blue-button(b1)to start\r\n");
	Standby();
}


double*  Sonar_result ()
{

}

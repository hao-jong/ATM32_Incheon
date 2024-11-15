/*
 * myLib.c
 *
 *  Created on: Nov 15, 2024
 *      Author: user
 */
void ProgramStart (char * str)
{
	printf("\033[2J\033[0;0H");
	printf("Program Start - %s\r\n",str);
	printf("Press Blue-button(b1)to start");
	Standby();
}

void Standby()
{
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin));
}


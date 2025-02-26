/*
 * usonic.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */
#include "main.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;

void microDelay(int us)// us : micro second
{
//	int t1 = htim2.Instance->CNT;
//	while (htim2.Instance->CNT - t1 < us);

	htim1.Instance->CNT = 0;
	int t1 = htim1.Instance->CNT;
	while (htim1.Instance->CNT - t1 < us);

}
int Distance()
{
	int t1,t2;
	htim1.Instance->CNT = 0;
	//wait until Echo_High
	while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 0)
	{
		if(htim1.Instance->CNT > 30000)
		{
			return -1;
		}
	}
	t1 = htim1.Instance->CNT;
	while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 1)
	{
		if(htim1.Instance->CNT > t1 + 30000)
		{
			return -1;
		}
	}
	t2 = htim1.Instance->CNT;
	double dist =(t2 - t1)*0.17; // mili meter
	return (int)dist;
}

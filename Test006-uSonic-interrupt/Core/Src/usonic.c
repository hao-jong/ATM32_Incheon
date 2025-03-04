/*
 * usonic.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */
#include "main.h"
#include "usonic.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim2;

void microDelay(int us)// us : micro second
{
//	int t1 = htim2.Instance->CNT;
//	while (htim2.Instance->CNT - t1 < us);

	htim2.Instance->CNT = 0;
	int t1 = htim2.Instance->CNT;
	while (htim2.Instance->CNT - t1 < us);

}

void Trigger0()
{
	HAL_GPIO_WritePin(Trig0_GPIO_Port, Trig0_Pin, 0);
	microDelay(10);
	HAL_GPIO_WritePin(Trig0_GPIO_Port, Trig0_Pin, 1);
	microDelay(10);
	HAL_GPIO_WritePin(Trig0_GPIO_Port, Trig0_Pin, 0);
}
void Trigger1()
{
	HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, 0);
	microDelay(10);
	HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, 1);
	microDelay(10);
	HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, 0);
}
void Trigger2()
{
	HAL_GPIO_WritePin(Trig2_GPIO_Port, Trig2_Pin, 0);
	microDelay(10);
	HAL_GPIO_WritePin(Trig2_GPIO_Port, Trig2_Pin, 1);
	microDelay(10);
	HAL_GPIO_WritePin(Trig2_GPIO_Port, Trig2_Pin, 0);
}

double Distance()
{
	int t0 = 0 ,t1,t2;
	htim2.Instance->CNT = 0;
	Trigger();
	//wait until Echo_High
	while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 0);
	{
		if(htim2.Instance->CNT > 30000)
		{
			return -1;
		}
	}
	t1 = htim2.Instance->CNT;
	while(HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == 1);
	{
		if(htim2.Instance->CNT > t1 + 30000)
		{
			return -1;
		}
	}
	t2 = htim2.Instance->CNT;

	double dist =(t2 - t1)*0.17; // mili meter
	return dist;
}

double* Distances()
{
	static double dist[3];
	uint32_t t1, t2, t3, t4, t5, t6;
	Trigger0();
	while(HAL_GPIO_ReadPin(Echo0_GPIO_Port, Echo0_Pin) == 0);
	{
		if(htim2.Instance->CNT > 30000)
		{
			return NULL;
		}
	}
	t1 = htim2.Instance->CNT;
	while(HAL_GPIO_ReadPin(Echo0_GPIO_Port, Echo0_Pin) == 1);
	{
		if(htim2.Instance->CNT > t1 + 30000)
		{
			return NULL;
		}
	}
	t2 = htim2.Instance->CNT;
	Trigger1();
	while(HAL_GPIO_ReadPin(Echo1_GPIO_Port, Echo1_Pin) == 0);
	{
		if(htim2.Instance->CNT > t2 + 30000)
		{
			return NULL;
		}
	}
	t3 = htim2.Instance->CNT;
	while(HAL_GPIO_ReadPin(Echo1_GPIO_Port, Echo1_Pin) == 1);
	{
		if(htim2.Instance->CNT > t3 + 30000)
		{
			return NULL;
		}
	}
	t4 = htim2.Instance->CNT;
	Trigger2();
	while(HAL_GPIO_ReadPin(Echo2_GPIO_Port, Echo2_Pin) == 0);
	{
		if(htim2.Instance->CNT > t4 + 30000)
		{
			return NULL;
		}
	}
	t5 = htim2.Instance->CNT;
	while(HAL_GPIO_ReadPin(Echo2_GPIO_Port, Echo2_Pin) == 1);
	{
		if(htim2.Instance->CNT > t5 + 30000)
		{
			return NULL;
		}
	}
	t6 = htim2.Instance->CNT;

	double dist[0] =(t2 - t1)*0.17;
	double dist[1] =(t4 - t3)*0.17;
	double dist[2] =(t6 - t5)*0.17;

	return dist;

}

/*
 * lcd1602.c
 *
 *  Created on: Nov 21, 2024
 *      Author: user
 *      Function : 1602 LCD device control
 */
#include <stdio.h>
#include "main.h"
extern I2C_HandleTypeDef hi2c1;
#define I2C_ADDR 0x4E  //  0x27 << 1

void lcd_command(char cmd) // cmd_bit : abcd efgh
{
	char n1, n2;
	char n3, n4;
	char dd[4];
	n1 = cmd & 0xf0;			// n1: abcd 0000 ==> upper nibble
	n2 = (cmd & 0x0f) << 4;		// n2: efgh 0000 ==> lower nibble to upper
	n3 = (1<<3)|(1<<2)	|0|0; //RW|EN|NC|RS; 0x0c
	n4 = (1<<3)|	0	|0|0; //RW|EN|NC|RS; 0x08

	dd[0] = n1 | n3;			//
	dd[1] = n1 | n4;
	dd[2] = n2 | n3;
	dd[3] = n2 | n4;
	HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, dd, 4, 10);

}
void lcd_data(char ch)
{
	char n1, n2;
	char n3, n4;
	char dd[4];
	n1 = ch & 0xf0;			// n1: abcd 0000 ==> upper nibble
	n2 = (ch & 0x0f) << 4;		// n2: efgh 0000 ==> lower nibble to upper
	n3 = (1<<3)|(1<<2)	|0|(1<<0); //RW|EN|NC|RS; 0x0d
	n4 = (1<<3)|	0	|0|(1<<0); //RW|EN|NC|RS; 0x09

	dd[0] = n1 | n3;			//
	dd[1] = n1 | n4;
	dd[2] = n2 | n3;
	dd[3] = n2 | n4;
	HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, dd, 4, 10);
}
void lcd_init()
{
	lcd_command(0x01); // screen clear
	lcd_command(0x02); // cursor home
	lcd_command(0x06);
	lcd_command(0x0f);
}
//int I2C_init(I2C_HandleTypeDef p)
//{
//	*hi2c = p;
//}

int I2C_scan()
{
//	if (hi2c = NULL)
//	{
//		printf("hi2c is not delivered");
//		return;
//	}
		for(int addr = 0; addr <127; addr++)
	{

		if(addr%16 == 0)
		{
			printf("\r\n");
		}

		if(HAL_I2C_IsDeviceReady(&hi2c1,addr,1,10) == HAL_OK)
		{
			printf("  %02x ", addr);
		}

		else
		{
			printf("  .  ");
		}


	}
}


void lcd_test()
{
	lcd_data('H');
	lcd_data('e');
	lcd_data('l');
	lcd_data('l');
	lcd_data('o');

}

void lcd_print(char *str)
{
	while(*str)
	{
		lcd_data(*str++);
	}
}

void lcd_printEx(char *str, int ln)
{
	if(ln == 0)
	{
		lcd_command(0x80);

	}
	if(ln == 1)
	{
		lcd_command(0xc0);

	}
	lcd_print(str);
}

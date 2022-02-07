/*
 * main.c
 *
 *  Created on: 5 Feb 2022
 *      Author: ahmed
 */
#include"ConsolePublisher.h"
#include"ConsoleUser1_Task.h"
#include"ConsoleUser2_Interrupt.h"
#include<stdio.h>


int main(void)
{
	printf("*****************main started*********************");
	//initialize
	ConsolePublisher();
	CU1T_Initalize();
	CU2I_Initalize();
	while(1)
	{
		//Write
		CU1T_WriteToConsole();
		CU2I_WriteToConsole();
		//show on screen
		CP_ShowData();
		CP_ShowData();
	}
	return 0;
}


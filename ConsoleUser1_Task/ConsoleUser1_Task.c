/*
 * ConsoleUser1_Task.c
 *
 *  Created on: 6 Feb 2022
 *      Author: ahmed
 */

#include "ConsoleUser1_Task.h"
#include "ConsolePublisher.h"

#define CU1T_DATA_CAPACITY 			10

CP_GCQ_TYPE ConsoleUser1_Task_data[CU1T_DATA_CAPACITY];

PUBLIC void CU1T_Initalize(void)
{
	for(uint32_t iterator = 0; iterator < 10; iterator++)
	{
		ConsoleUser1_Task_data[iterator] = iterator;
	}

}

PUBLIC void CU1T_WriteToConsole(void)
{
	static uint32_t data_idx = 0;
	CP_BufferData(ConsoleUser1_Task_data[data_idx]);
	data_idx++;
	if(CU1T_DATA_CAPACITY <= data_idx)
	{
		data_idx = 0;
	}
}

/*
 * ConsoleUser1_Task.c
 *
 *  Created on: 6 Feb 2022
 *      Author: ahmed
 */

#include "ConsoleUser2_Interrupt.h"

#include "ConsolePublisher.h"

#define CU2T_DATA_CAPACITY 			10

CP_GCQ_TYPE ConsoleUser2_Interrupt_data[CU2T_DATA_CAPACITY];

PUBLIC void CU2I_Initalize(void)
{
	for(uint32_t iterator = 0; iterator < 10; iterator++)
	{
		ConsoleUser2_Interrupt_data[iterator] = iterator;
	}

}

PUBLIC void CU2I_WriteToConsole(void)
{
	static uint32_t data_idx = 0;

	CP_BufferData(ConsoleUser2_Interrupt_data[data_idx]);
	data_idx++;

	if(CU2T_DATA_CAPACITY == data_idx)
	{
		data_idx = 0;
	}
}

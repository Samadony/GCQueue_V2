/*
 * ConsolePublisher.c
 *
 *  Created on: 2 Feb 2022
 *      Author: ahmed
 */

#include"ConsolePublisher.h"
#include"GCQueue_Interface.h"
#include<stdio.h>

#define CP_GCQ_CAPACITY						8
#define CP_GCQ_TYPE							uint32_t
CREATE_GCQUEUE(CP_GCQ_TYPE, CP_GCQueue, CP_GCQ_CAPACITY)

/*
 * Initialize the ConsolePublisher
 */
PUBLIC_API void ConsolePublisher(void)
{
	GCQ_Status_t Init_Status;
	//init the queue
	Init_Status = GCQ_HARD_ERASE_API(CP_GCQ_TYPE, &CP_GCQueue);
	if(GCQ_OK == Init_Status)
	{
		printf("Console Publisher Initialized\n");
	}
	else
	{
		printf("Console Publisher Error Initializing\n");
	}
}

/*
 * Buffer write wrapper, used by the producer
 * Synchronous writing
 */
PUBLIC_API void CP_BufferData(CP_GCQ_TYPE copy_data_to_buffer)
{
	GCQ_Status_t DataBuffering_Status;
	DataBuffering_Status =
			GCQ_ENQUEUE_API(CP_GCQ_TYPE, &CP_GCQueue, &copy_data_to_buffer);
	if(GCQ_OK == DataBuffering_Status)
	{
		printf("DataBuffered Succefully\n");
	}
	else
	{
		printf("Data Buffering Failed!\n");
	}
}

/*
 * Buffer read wrapper, used by the consumer (this module)
 * This activity is periodic
 */
PUBLIC_API void CP_ShowData()
{
	GCQ_Status_t DataRetrieval_Status;
	CP_GCQ_TYPE Data;
	DataRetrieval_Status =
			GCQ_DEQUEUE_API(CP_GCQ_TYPE, &CP_GCQueue, &Data);

	switch(DataRetrieval_Status)
	{
		case(GCQ_OK):
			printf("Data = %d\n", Data);
		break;
		case(GCQ_EMPTY):
			printf("Buffer Empty\n");
		break;
		default:
			printf("Data Retrieval Error\n");
	}
}

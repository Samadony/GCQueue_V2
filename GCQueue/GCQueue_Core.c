
#include "GCQueue_Cfg.h"
#include<stdint.h>
#include <string.h>
#include"../utils/defines.h"

/*
 * Private Functions
 */
/* Private Definitions*/
#define PRIVATE_FUNCTIONS()\
PRIVATE void Enter_CriticalSection(void);                                                               		 \
PRIVATE void Enter_CriticalSection(void)                                                                 		 \
{   /*TODO: switch case*/                                                                                        \
	if(QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_ZERO)                                                      \
	{                                                                                                            \
		/*Do nothing*/                                                                                           \
	}                                                                                                            \
                                                             					                                 \
	else if(QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_ONE)											         \
	{                                                                                                            \
		/*                                                                                                       \
		 * Take the Mutex here, just make sure you allocated the mutex on the                                    \
		 * consumer and producer(s) of the queue                                                                 \
		 */ 																	                                 \
	}                                                                        	                                 \
	else if (QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_TWO)										         \
	{                                                                                                            \
		/* Disable the OS tick */                                                                                \
	}                                                                                                            \
	else if (QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_THREE)                                               \
	{                                                                                                            \
		/* Disable All Interrupts */                                                                             \
	}                                                                                                            \
}                                                                                                                \
																				                                 \
PRIVATE void Exit_CriticalSection(void);                                                                  		 \
PRIVATE void Exit_CriticalSection(void)                                                                   		 \
{                                                                                                                \
	if(QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_ZERO)                                                      \
	{                                                                                                            \
		/*Do nothing */														                                     \
	}                                                                                                            \
	else if(QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_ONE)                                                  \
	{                                                                                                            \
		/*                                                                                                       \
		* Leave the same Mutex here, just make sure you allocated the mutex on                                   \
		* the consumer and producer(s) of the queue                                                              \
		*/                                                                                                       \
	}                                                                                                            \
	else if(QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_TWO)                                                  \
	{                                                                                                            \
		/* Enable the OS tick */                                                                                 \
	}                                                                                                            \
	else if (QUEUE_CONCURRENCY_LVL == QUEUE_CONCURRENCY_LVL_THREE)                                               \
	{                                                                                                            \
		/* Enable All Interrupts */                                                                              \
	}                                                                                                            \
}      																			                                 \

/*
 * Abstractors to achieve complete encapsulation
 */

/*
 * Template to define queue_q_header + queue buffer with types varies between
 * signed/unsigned 8, 16, 32 and 64 bits variables
 */
#define DEFINE_GCQUEUE(TYPE)					DEFINE_GCQUEUE_ABSTRACTOR(TYPE)

/*
 * This is a concatenation helper yet serve abstraction well, hence i changed the name
 */
#define DEFINE_GCQUEUE_ABSTRACTOR(TYPE)																			 \
typedef struct{uint32_t q_head; uint32_t q_tail; TYPE* data_buffer_ptr; const uint32_t q_capacity; uint32_t q_size; GCQ_Status_t gcq_status;}GCQ_##TYPE##_t;\
	PRIVATE_FUNCTIONS()																							 \
	GCQUEUE_ERASEHARD(TYPE)														                                 \
	GCQUEUE_ERASESOFT(TYPE)														                                 \
	GCQUEUE_ISFULL(TYPE)														                                 \
	GCQUEUE_ISEMPTY(TYPE)														                                 \
	GCQUEUE_ENQUEUE(TYPE)														                                 \
	GCQUEUE_DEQUEUE(TYPE)														                                 \
	GCQUEUE_PEEK(TYPE)															                                 \

/* Public Definitions*/
/*
 * Hard erase
 */
#define GCQUEUE_ERASEHARD(TYPE)					GCQUEUE_ERASEHARD_CONC_HELPER(TYPE)
#define GCQUEUE_ERASEHARD_CONC_HELPER(TYPE)																		 \
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Hard_Erase(volatile GCQ_##TYPE##_t* const self);							 \
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Hard_Erase(volatile GCQ_##TYPE##_t* const self)                             \
{                                                                                                                \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                     \
                                                                                                                 \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                        \
	{                                                                                                            \
		Enter_CriticalSection();																				 \
		memset(self->data_buffer_ptr, QUEUE_ERASE_VALUE, (self->q_capacity) * (sizeof(self->data_buffer_ptr[0])));\
		self->q_tail = 0;                                                                                     	 \
		self->q_head = 0;                                                                                        \
		self->q_size = 0;																				 		 \
		Enter_CriticalSection();                                                                                 \
		gcq_status = GCQ_OK;                                                                                     \
	}                                                                                                            \
	else                                                                                                         \
	{                                                                                                            \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                       \
	}                                                                                                            \
	return gcq_status;                                                                                           \
}                                                                                                                \


#define GCQUEUE_ERASESOFT(TYPE)					GCQUEUE_ERASESOFT_CONC_HELPER(TYPE)
#define GCQUEUE_ERASESOFT_CONC_HELPER(TYPE) 																	\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Soft_Erase(volatile GCQ_##TYPE##_t* const self);							\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Soft_Erase(volatile GCQ_##TYPE##_t* const self)							\
{                                                                                                               \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                    \
                                                                                                                \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                       \
	{                                                                                                           \
		Enter_CriticalSection();																				\
		self->q_tail = 0;                                                                                     	\
		self->q_head = 0;                                                                                    	\
		self->q_size = 0;																						\
		gcq_status = GCQ_OK;                                                                                	\
		Exit_CriticalSection();                                                                                 \
	}                                                                                                           \
	else                                                                                                        \
	{                                                                                                           \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                      \
	}                                                                                                           \
	return gcq_status;                                                                                          \
}                                                                                                               \


#define GCQUEUE_ISFULL(TYPE)					GCQUEUE_ISFULL_CONC_HELPER(TYPE)
#define GCQUEUE_ISFULL_CONC_HELPER(TYPE)																		\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_IsFull(const volatile GCQ_##TYPE##_t* const self);							\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_IsFull(const volatile GCQ_##TYPE##_t* const self)                          \
{                                                                                                               \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                    \
                                                                                                                \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                       \
	{   																										\
		Enter_CriticalSection();																				\
		if(self->q_capacity == self->q_size)																	\
		{                                                                                                       \
			gcq_status = GCQ_FULL;                                                                              \
		}                                                                                                       \
		else                                                                                                    \
		{                                                                                                       \
			gcq_status = GCQ_OK;                                                                                \
		}                                                                                                       \
		Exit_CriticalSection();																					\
	}                                                                                                           \
	else                                                                                                        \
	{                                                                                                           \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                      \
	}                                                                                                           \
	return gcq_status;                                                                                          \
}                                                                                                               \


#define GCQUEUE_ISEMPTY(TYPE)					GCQUEUE_ISEMPTY_CONC_HELPER(TYPE)
#define GCQUEUE_ISEMPTY_CONC_HELPER(TYPE)																		\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_IsEmpty(const volatile GCQ_##TYPE##_t* const self);						\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_IsEmpty(const volatile GCQ_##TYPE##_t* const self)							\
{                                                                                                               \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                    \
                                                                                                                \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                       \
	{                                                                                                           \
		Enter_CriticalSection();																				\
		if(0 == self->q_size)																					\
		{                                                                                                       \
			gcq_status = GCQ_EMPTY;                                                                             \
		}                                                                                                       \
		else                                                                                                    \
		{                                                                                                       \
			gcq_status = GCQ_OK;                                                                                \
		}                                                                                                       \
		Exit_CriticalSection();																					\
	}                                                                                                           \
	else                                                                                                        \
	{                                                                                                           \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                      \
	}                                                                                                           \
	return gcq_status;                                                                                          \
}


#define GCQUEUE_ENQUEUE(TYPE)					GCQUEUE_ENQUEUE_CONC_HELPER(TYPE)
#define GCQUEUE_ENQUEUE_CONC_HELPER(TYPE)																				\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Enqueue(volatile GCQ_##TYPE##_t* const self, const TYPE* const TYPE##ptr_data_enqueued); 	\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Enqueue(volatile GCQ_##TYPE##_t* const self, const TYPE* const TYPE##ptr_data_enqueued)	\
{                                                                                                                       \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                            \
                                                                                                                        \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                               \
	{                                                                                                                   \
		Enter_CriticalSection();																						\
		if(NULL != TYPE##ptr_data_enqueued)                                                                         	\
		{                                                                                                               \
			if( QUEUE_ENABLE_OVR_WRT || (GCQ_FULL != GCQueue_##TYPE##_IsFull(self)) )									\
			{                                                                                                           \
				/*                                                                                                      \
				 * 1- Update the head, reset head to start over "circulate" if the head reached the end                 \
				 * 2- Enqueue the data                                                                                  \
				 * 3- Increase current queue size if size < capacity                                                    \
				 */                                                                                                     \
				if(self->q_head == (self->q_capacity - 1))                                                              \
				{                                                                                                       \
					self->q_head = 0;                                                                                   \
				}                                                                                                       \
				else                                                                                                    \
				{                                                                                                       \
					++(self->q_head);                                                                                   \
				}                                                                                                       \
				self->data_buffer_ptr[self->q_head] = *TYPE##ptr_data_enqueued;                                         \
				if(self->q_capacity > self->q_size)																		\
				{																										\
					++(self->q_size) ;																					\
				}																										\
				gcq_status = GCQ_OK;                                                                                    \
			}                                                                                                           \
			else /*Queue is Full*/                                                                                      \
			{                                                                                                           \
				gcq_status = GCQ_FULL;                                                                                  \
			}                                                                                                           \
		}                                                                                                               \
		else                                                                                                            \
		{                                                                                                               \
			gcq_status = GCQ_ENQUEUE_DATA_ADDRESS_NULL;                                                                 \
		}																												\
		Exit_CriticalSection();																							\
	}                                                                                                                   \
	else                                                                                                                \
	{                                                                                                                   \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                              \
	}                                                                                                                   \
	return gcq_status;                                                                                                  \
}                                                                                                                       \


#define GCQUEUE_DEQUEUE(TYPE)					GCQUEUE_DEQUEUE_CONC_HELPER(TYPE)
#define GCQUEUE_DEQUEUE_CONC_HELPER(TYPE)																				\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Dequeue(volatile GCQ_##TYPE##_t* const self, TYPE* const TYPE##ptr_data_dequeued);	\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Dequeue(volatile GCQ_##TYPE##_t* const self, TYPE* const TYPE##ptr_data_dequeued)	\
{                                                                                                                       \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                            \
                                                                                                                        \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                               \
	{                                                                                                                   \
		Enter_CriticalSection();																						\
		if(NULL != TYPE##ptr_data_dequeued)                                                                         	\
		{                                                                                                               \
			if( GCQ_EMPTY != GCQueue_##TYPE##_IsEmpty(self))                                                            \
			{                                                                                                           \
				/*                                                                                                      \
				 * 1- Update the tail, reset tail to start over "circulate" if the tail reached the end                 \
				 * 2- dequeue the data                                                                                  \
				 * 3- Decrease the q_size																				\
				 */                                                                                                     \
				if(self->q_tail == (self->q_capacity - 1))                                                              \
				{                                                                                                       \
					self->q_tail = 0;                                                                                   \
				}                                                                                                       \
				else                                                                                                    \
				{                                                                                                       \
					++(self->q_tail);                                                                                   \
				}                                                                                                       \
				*TYPE##ptr_data_dequeued = self->data_buffer_ptr[self->q_tail];                                         \
				--(self->q_size) ;                                                                                      \
				gcq_status = GCQ_OK;                                                                                    \
			}                                                                                                           \
			else /*Queue is Empty*/                                                                                     \
			{                                                                                                           \
				gcq_status = GCQ_EMPTY;                                                                                 \
			}                                                                                                           \
		}                                                                                                               \
		else                                                                                                            \
		{                                                                                                               \
			gcq_status = GCQ_DEQUEUE_DATA_ADDRESS_NULL;                                                                 \
		}                                                                                                               \
		Exit_CriticalSection();																						 	\
	}                                                                                                                   \
	else                                                                                                                \
	{                                                                                                                   \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                              \
	}                                                                                                                   \
	return gcq_status;                                                                                                  \
}                                                                                                                       \


#define GCQUEUE_PEEK(TYPE)					GCQUEUE_PEEK_CONC_HELPER(TYPE)
#define GCQUEUE_PEEK_CONC_HELPER(TYPE)																					\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Peek(volatile GCQ_##TYPE##_t* const self, TYPE* const TYPE##ptr_data_peeked);		\
PUBLIC GCQ_Status_t GCQueue_##TYPE##_Peek(volatile GCQ_##TYPE##_t* const self, TYPE* const TYPE##ptr_data_peeked)		\
{                                                                                                                       \
	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                            \
	uint32_t lcl_cpy_q_tail;																							\
                                                                                                                        \
	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                               \
	{                                                                                                                   \
		Enter_CriticalSection();																						\
		if(NULL != TYPE##ptr_data_peeked)                                                                    		    \
		{                                                                                                               \
			if( GCQ_EMPTY != GCQueue_##TYPE##_IsEmpty(self))                                                            \
			{   																										\
				/*                                                                                                      \
				 * 1- Update the tail copy, reset tail_cpy to start over "circulate" if the tail reached the end        \
				 * 2- Peek the data                                                                                  	\
				 */                                                                                                     \
				 lcl_cpy_q_tail = self->q_tail;																			\
				if(lcl_cpy_q_tail == (self->q_capacity - 1))                                                            \
				{                                                                                                       \
					lcl_cpy_q_tail = 0;                                                                                 \
				}                                                                                                       \
				else                                                                                                    \
				{                                                                                                       \
					++(lcl_cpy_q_tail);                                                                                 \
				} 																										\
				*TYPE##ptr_data_peeked = self->data_buffer_ptr[lcl_cpy_q_tail];    		                                \
				gcq_status = GCQ_OK;                                                                                    \
			}                                                                                                           \
			else /*Queue is Empty*/                                                                                     \
			{                                                                                                           \
				gcq_status = GCQ_EMPTY;                                                                                 \
			}                                                                                                           \
		}                                                                                                               \
		else                                                                                                            \
		{                                                                                                               \
			gcq_status = GCQ_PEEK_DATA_ADDRESS_NULL;                                                                 	\
		}                                                                                                               \
		Exit_CriticalSection();																							\
	}                                                                                                                   \
	else                                                                                                                \
	{                                                                                                                   \
		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                              \
	}                                                                                                                   \
	return gcq_status;                                                                                                  \
}                                                                                                                       \

/* Pre -requisite: calling DEFINE_GCQUEUE() with the same type used for OBJECT_ADDRESS creation
 * Template to instantiate queue_q_header + queue buffer with types varies between
 * signed/unsigned 8, 16, 32 and 64 bits variables
 */
#define INSTANTIATE_GCQUEUE(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)												\
				INSTANTIATE_GCQUEUE_ABSTRACTOR(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)

/*the abstractor is used to hide the instantiation implementation from the user,
 * not used as a concatenation helper
 */
#define INSTANTIATE_GCQUEUE_ABSTRACTOR(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)									 \
PRIVATE TYPE NAME##_data_buffer[BUFFER_SIZE_IN_TYPE_SIZE];     			                                         \
PRIVATE volatile GCQ_##TYPE##_t NAME = {                                                                         \
	.q_head = 0,                                                                                                 \
	.q_tail = 0,															                                     \
	.data_buffer_ptr = NAME##_data_buffer,			                                                             \
	.q_capacity = BUFFER_SIZE_IN_TYPE_SIZE,									                                     \
	.q_size = 0,															                                     \
	.gcq_status = GCQ_ERROR_NUM,										                                         \
};																												 \

/*
 * APIs Abstractors
 */
#define GCQ_HARD_ERASE_ABSTRACTOR(TYPE, OBJECT_ADDRESS)					GCQueue_##TYPE##_Hard_Erase(OBJECT_ADDRESS)
#define GCQ_SOFT_ERASE_ABSTRACTOR(TYPE, OBJECT_ADDRESS)					GCQueue_##TYPE##_Soft_Erase(OBJECT_ADDRESS)
#define GCQ_IS_FULL_ABSTRACTOR(TYPE, OBJECT_ADDRESS) 					GCQueue_##TYPE##_IsFull(OBJECT_ADDRESS)
#define GCQ_IS_EMPTY_ABSTRACTOR(TYPE, OBJECT_ADDRESS) 					GCQueue_##TYPE##_IsEmpty(OBJECT_ADDRESS)
#define GCQ_ENQUEUE_ABSTRACTOR(TYPE, OBJECT_ADDRESS, DATA_ADDRESS)		GCQueue_##TYPE##_Enqueue(OBJECT_ADDRESS, DATA_ADDRESS)
#define GCQ_DEQUEUE_ABSTRACTOR(TYPE, OBJECT_ADDRESS, DATA_ADDRESS)		GCQueue_##TYPE##_Dequeue(OBJECT_ADDRESS, DATA_ADDRESS)
#define GCQ_PEEK_ABSTRACTOR(TYPE, OBJECT_ADDRESS, DATA_ADDRESS)			GCQueue_##TYPE##_Peek(OBJECT_ADDRESS, DATA_ADDRESS)

/*
 * TODO:
 * Extend the module to handle array data handling(strings or matrices in general)
 */

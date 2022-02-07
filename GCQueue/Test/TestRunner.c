/*Harness*/
#include <gtest/gtest.h>
#include <gmock/gmock.h>
/*Unit under test*/
#include <GCQueue_Core.h>
#include <GCQueue_Interface.h>
#include"../utils/defines.h"
/*utilities and libs needed for testing*/
#include <stddef.h>
#include <string.h>
#include <stdint.h>

#define UTEST_QUEUE_BUFFER_SIZE				1
#define UTEST_TYPE_BEING_TESTED			 int32_t
#define UTEST_GCQ_HARD_ERASE_VALUE		(UTEST_TYPE_BEING_TESTED)0xAAAAAAAAU

/*Full Encabsulation test case */
CREATE_GCQUEUE(UTEST_TYPE_BEING_TESTED, gcqueue_utest, UTEST_QUEUE_BUFFER_SIZE);

/*
 * Goal, test the template against mulitple definitions and instantiations
 */
//DEFINE_GCQUEUE(uint16_t);
//DEFINE_GCQUEUE(uint32_t);
//DEFINE_GCQUEUE(uint64_t);
//DEFINE_GCQUEUE(int8_t);
//DEFINE_GCQUEUE(int16_t);
//DEFINE_GCQUEUE(int32_t);
//DEFINE_GCQUEUE(int64_t);
//
//void test_template_implementation(void)
//{
//	CREATE_GCQUEUE(uint8_t, gcqueue_utest_0, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint16_t, gcqueue_utest_1, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint32_t, gcqueue_utest_2, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint64_t, gcqueue_utest_3, QUEUE_BUFFER_SIZE);
//
//	CREATE_GCQUEUE(int8_t, gcqueue_utest_4, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int16_t, gcqueue_utest_5, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int32_t, gcqueue_utest_6, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int64_t, gcqueue_utest_7, QUEUE_BUFFER_SIZE);
//
//	GCQ_HARD_ERASE_ABSTRACTOR(uint8_t, gcqueue_utest_0);
//	GCQ_SOFT_ERASE_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_IS_FULL_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_IS_EMPTY_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_ENQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//	GCQ_DEQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//	GCQ_PEEK_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//}
class GCQueueTest: public testing::Test
{
public:
	GCQueueTest();
	~GCQueueTest();
	static void SetUpTestSuite(void);
	static void TearDownTestSuite(void);
	void SetUp(void) override;
	void TearDown(void) override;

protected:

};

GCQueueTest::GCQueueTest()
{
//	std::cout << "Constructor of Test Fixture" << std::endl;
	gcqueue_utest.q_head = 0xFF;
	gcqueue_utest.q_tail = 0xFF;
	gcqueue_utest.q_size = 0xFF;
	gcqueue_utest.data_buffer_ptr = gcqueue_utest_data_buffer;
	memset(gcqueue_utest.data_buffer_ptr, 0xFF,
			sizeof(gcqueue_utest_data_buffer));
}
GCQueueTest::~GCQueueTest()
{
//	std::cout << "Destructor of Test Fixture" << std::endl;
}
void GCQueueTest::SetUpTestSuite(void)
{
//	std::cout << "SetUp Of Test Suite, called ONCE" << std::endl;
}
void GCQueueTest::TearDownTestSuite(void)
{
//	std::cout << "TearDown Of Test Suite, called ONCE" << std::endl;
}

void GCQueueTest::SetUp(void)
{
//	std::cout << "SetUp Of test scenario" << std::endl;
}
void GCQueueTest::TearDown(void)
{
//	std::cout << "TearDown Of test scenario" << std::endl;
}

/*
 * Goal: 1- check whether the Hard erase is done in a proper way
 *
 * //Scenario_0
 * Arrange:
 * Act: call EraseHard_GCQueue(&gcqueue_utest_data_buffer)
 * Assert:
 * - gcq_status = Q_OK
 * - q_head = 0
 * - q_tail  = 0
 * - data_buffer_ptr[0 -> QUEUE_BUFFER_SIZE -1 ] = QUEUE_ERASE_VALUE
 *
 * //Scenario_1
 * Arrange:
 * Act: EraseHard_GCQueue(NULL)
 * Assert:
 * - gcq_status = GCQ_NULL_BUFFER
 *
 * //Scenario_2
 * Arrange: gcq_q_header_utest.data_buffer_ptr = NULL
 * Act:
 * Assert:
 * - TEST_ASSERT_NULL(gcq_q_header_utest.data_buffer_ptr)
 * - gcq_status = GCQ_NULL_BUFFER
 *
 */
TEST_F(GCQueueTest, TestHardEraseOfTheGCQueue)
{
	uint16_t iterator;
	GCQ_Status_t gcq_status;
/*
 * Test happy scenario
 */
	//Secenrio_0
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);
	ASSERT_EQ(gcqueue_utest.q_head, 0UL);
	ASSERT_EQ(gcqueue_utest.q_tail, 0UL);
	ASSERT_EQ(gcqueue_utest.q_size, 0UL);
	for(iterator = 0; iterator < UTEST_QUEUE_BUFFER_SIZE; iterator++)
	{
    	ASSERT_EQ((UTEST_TYPE_BEING_TESTED)QUEUE_ERASE_VALUE, gcqueue_utest.data_buffer_ptr[iterator]);
	}
/*
 * Test sad scenario
 */
	//Scenario_1
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	ASSERT_EQ(GCQ_DATA_BUFFER_NULL, gcq_status);
	//Scenario_2
	gcqueue_utest.data_buffer_ptr = NULL;
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED,NULL);
	ASSERT_EQ(GCQ_DATA_BUFFER_NULL, gcq_status);

}
/*
 * Goal: check whether the Soft erase is done in a proper way (only buffer indices are reset to 0)
 *
  * //Scenario_0
 * Arrange:
 * Act: call EraseSoft_GCQueue(&gcqueue_utest_data_buffer)
 * Assert:
 * - gcq_status = Q_OK
 * - q_head = 0
 * - q_tail  = 0
 * - data_buffer_ptr[0 -> QUEUE_BUFFER_SIZE -1 ] != UTEST_GCQ_HARD_ERASE_VALUE
 *
 * //Scenario_1
 * Arrange:
 * Act: EraseSoft_GCQueue(NULL)
 * Assert:
 * - gcq_status = GCQ_NULL_BUFFER
 *
 * //Scenario_2
 * Arrange: gcq_q_header_utest.data_buffer_ptr = NULL
 * Act:
 * Assert:
 * - TEST_ASSERT_NULL(gcq_q_header_utest.data_buffer_ptr)
 * - gcq_status = GCQ_NULL_BUFFER
 *
 */
TEST_F(GCQueueTest, TestSoftEraseOfTheGCQueue)
{
	uint32_t iterator;
	GCQ_Status_t gcq_status;
/*
 * Test happy scenario
 */
	//Secenrio_0
	gcq_status = GCQ_SOFT_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);
	ASSERT_EQ(gcqueue_utest.q_head, 0UL);
	ASSERT_EQ(gcqueue_utest.q_tail, 0UL);
	ASSERT_EQ(gcqueue_utest.q_size, 0UL);
	for(iterator = 0; iterator < UTEST_QUEUE_BUFFER_SIZE; iterator++)
	{
    	ASSERT_NE(UTEST_GCQ_HARD_ERASE_VALUE, gcqueue_utest.data_buffer_ptr[iterator]);
	}
/*
 * Test sad scenario
 */
	//Scenario_1
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	ASSERT_EQ(GCQ_DATA_BUFFER_NULL, gcq_status);

	//Scenario_2
	gcqueue_utest.data_buffer_ptr = NULL;
	gcq_status = GCQ_SOFT_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	ASSERT_EQ(GCQ_DATA_BUFFER_NULL, gcq_status);

}
/*
 * Goal, test GCQueue_IsFull
 *
 * Scenario_0.0: the buffer is Full
 * Arrange: set q_size= buffer capacity
 * Act: call GCQueue_IsFull
 * Assert: 	GCQ_Status_t gcq_status = GCQ_FULL
 *
 * Scenario_1.0: the buffer is Full
 * Arrange: set q_size= buffer size -1
 * Act: call GCQueue_IsFull
 * Assert: 	GCQ_Status_t gcq_status = GCQ_OK
 *
 * Scenario_2.0: the buffer is empty
 * Arrange: set q_size= 0
 * Act: call GCQueue_IsFull
 * Assert: 	GCQ_Status_t gcq_status = GCQ_OK
 *
 */
TEST_F(GCQueueTest, TestGCQueueIsFullInducedTest)
{
	GCQ_Status_t gcq_status;

	//Scenario_0.0
	gcqueue_utest.q_size = UTEST_QUEUE_BUFFER_SIZE;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_FULL, gcq_status);

	//Scenario_1.0
	gcqueue_utest.q_size = UTEST_QUEUE_BUFFER_SIZE - 1;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);

	//Scenario_2.0
	gcqueue_utest.q_size = 0;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);

}

/*
 * Goal, test GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 *
 * Scenario_0: the buffer is Empty
 * Arrange: set q_size = 0
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_Empty
 *
 * Scenario_1: the buffer is not empty
 * Arrange: set q_size = buffer capacity - 1
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_OK
 *
 * Scenario_2: the buffer is Full
 * Arrange: set q_size = buffer capacity
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_OK
 *
 *
 *
 */
TEST_F(GCQueueTest, TestGCQueueIsEmptyInducedTesting)
{
	GCQ_Status_t gcq_status;

	//Scenario_0.0
	gcqueue_utest.q_size = 0;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_EMPTY, gcq_status);

	//Scenario_1.0
	gcqueue_utest.q_size = UTEST_QUEUE_BUFFER_SIZE - 1;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	if(1 >= gcqueue_utest.q_capacity) //capacity = [0:1]
	{
		ASSERT_EQ(GCQ_EMPTY, gcq_status);
	}
	else //capacity = [2:2^32]
	{
		ASSERT_EQ(GCQ_OK, gcq_status);
	}


	//Scenario_2.0
	gcqueue_utest.q_size = UTEST_QUEUE_BUFFER_SIZE;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);
}

/*
 *Goal, Enqueue untill the buffer is full with known pattern
 *
 * Scenario_0.0, fill the buffer till full
 * Arrange: Har
 * Act: Call GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, ) in loop equal to the array`s (size -1)
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 *
 * Assert: check if it full
 * Assert: all data of the buffer shall be enqueued_data = 1377
 */
TEST_F(GCQueueTest, TestGCQENQUEUEAPI)
{
	GCQ_Status_t gcq_status;
	uint32_t iterator = 0;
	UTEST_TYPE_BEING_TESTED enqueued_data = 137;//random u8 number
#if(QUEUE_ENABLE_OVR_WRT == true)
	UTEST_TYPE_BEING_TESTED enqueued_data_marker = 0;
#endif
	//Scenario_0.0
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
	}
	//data integrity
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		ASSERT_EQ(enqueued_data, gcqueue_utest.data_buffer_ptr[iterator]);
	}
	/*
	 * TODO: there are 2 possibilities, define a strategy to perform both tests
	 * passing arguments through the make process works yet it wont be efficient
	 */
#if(QUEUE_ENABLE_OVR_WRT == false)
	//Its now Full queue, enqueue one more time expecting a full status
	gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
	ASSERT_EQ(GCQ_FULL, gcq_status);
	//Make sure our buffer isnt messed with (test data integrity) after a full status
	for(iterator = 0 ; iterator < (UTEST_QUEUE_BUFFER_SIZE) ; iterator++)
	{
		ASSERT_EQ(enqueued_data, gcqueue_utest.data_buffer_ptr[iterator]);
	}
#else
	//Its now Full queue, enqueue one more time expecting a succesfull enqueue
	gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data_marker);
	ASSERT_EQ(GCQ_OK, gcq_status);
	//Make sure the last enqueued data is as expected.
	ASSERT_EQ(enqueued_data_marker, gcqueue_utest.data_buffer_ptr[gcqueue_utest.q_head]);
#endif

}

/*
 *Goal, Dequeue untill the buffer is empty with known pattern
 *
 * Scenario_0.0, dequeue untill empty
 * Arrange: Hard reset then Enqueue the full size
 * Act: Call GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, ) in loop equal to the q_capacity
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 * Assert: the dequeued data is the same like what has been enqueued
 * Assert: the size shall be zero
 *
 * Scenario_1.0 Dequeue on an empty queue
 * Arrange: Hard Reset call
 * Act: Call GCQ_DEQUEUE_API once
 * Assert: the outcome shall be always gcq_status = GCQ_EMPTY
 * Assert: the size shall be zero
 *
 * Scenario_2.0 Dequeue after enqueueing twice the capacity
 * Arrange: Enqueue the (full size * 2) only if over writing is enabled
 * Act: Call GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, ) in loop equal to the q_capacity
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 * Act: perform an extra dequeue
 * Assert: the outcome shall be gcq_status = GCQ_EMPTY
 */
TEST_F(GCQueueTest, TestGCQDEQUEUEAPI)
{
	GCQ_Status_t gcq_status;
	uint32_t iterator;
	UTEST_TYPE_BEING_TESTED enqueued_data = 137;
	UTEST_TYPE_BEING_TESTED dequeued_data = 0;

	//Scenario_0.0
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	ASSERT_EQ(GCQ_OK, gcq_status);
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
	}
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		ASSERT_EQ(enqueued_data, dequeued_data);
		dequeued_data = 0;
	}
	/*
	 * One more dequeue, the status shall be Empty
	 */
	gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
	ASSERT_EQ(GCQ_EMPTY, gcq_status);
	ASSERT_EQ(0UL, gcqueue_utest.q_size);


	//Scenario_1.0
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		//std::cout << "Iterator: " << iterator << " q_head: " << gcqueue_utest.q_head <<  " q_tail: " << gcqueue_utest.q_tail << std::endl;
	}
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		ASSERT_EQ(enqueued_data, dequeued_data);
		//std::cout << "Iterator: " << iterator << " q_head: " << gcqueue_utest.q_head <<  " q_tail: " << gcqueue_utest.q_tail << std::endl;
	}
	//Scenario_2.0
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE * 2 ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, (UTEST_TYPE_BEING_TESTED*)&iterator);
		//std::cout << "Iterator: " << iterator << " q_head: " << gcqueue_utest.q_head <<  " q_tail: " << gcqueue_utest.q_tail << std::endl;
	}
#if(QUEUE_ENABLE_OVR_WRT == true)
	for(iterator = UTEST_QUEUE_BUFFER_SIZE ; iterator < UTEST_QUEUE_BUFFER_SIZE * 2 ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		ASSERT_EQ((UTEST_TYPE_BEING_TESTED)(iterator), dequeued_data);
		//std::cout << "Iterator: " << iterator << " q_head: " << gcqueue_utest.q_head <<  " q_tail: " << gcqueue_utest.q_tail << std::endl;
	}
#else
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		ASSERT_EQ(iterator, dequeued_data);
		//std::cout << "Iterator: " << iterator << " q_head: " << gcqueue_utest.q_head <<  " q_tail: " << gcqueue_utest.q_tail << std::endl;
	}
#endif
	gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
	ASSERT_EQ(GCQ_EMPTY, gcq_status);
}


/*
 *Goal, check peek
 *
 * Scenario_0.0: peek an empty
 *
 * Scenario_1.0, Peek while enqueueing
 * Arrange: Arrange input array 0 to size -1
 * Act: Enqueue till Full, peek, dequeue ... iterate, iterations =  size -1
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 *
 * Scenario_2.0, Dequeue then Peek
 *
 */
TEST_F(GCQueueTest, TestGCQPEEKAPI)
{

	GCQ_Status_t gcq_status;
	uint32_t iterator;
	UTEST_TYPE_BEING_TESTED peeked_data = 0;//random u8 number
	UTEST_TYPE_BEING_TESTED dequeued_data;
	//Scenario_0.0
	//Arrange
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	//Act
	gcq_status = GCQ_PEEK_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &peeked_data);
	//Assert
	ASSERT_EQ(GCQ_EMPTY, gcq_status);

	//Scenario_1.0
	//Arrange
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, (UTEST_TYPE_BEING_TESTED*)&iterator);
		ASSERT_EQ(GCQ_OK, gcq_status);

		gcq_status = GCQ_PEEK_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &peeked_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
	}
	ASSERT_EQ(peeked_data, gcqueue_utest_data_buffer[((gcqueue_utest.q_tail) + 1)]);

	//Scenario 2.0
	//Arrange
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, (UTEST_TYPE_BEING_TESTED*)&iterator);
		ASSERT_EQ(GCQ_OK, gcq_status);
	}
	ASSERT_EQ(gcqueue_utest.q_size, gcqueue_utest.q_capacity);
	//Loop:
	//Act
	//Assert
	for(iterator = 0 ; iterator < UTEST_QUEUE_BUFFER_SIZE ; iterator++)
	{
		gcq_status = GCQ_PEEK_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &peeked_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		ASSERT_EQ(GCQ_OK, gcq_status);
		ASSERT_EQ(dequeued_data, peeked_data);
	}
}


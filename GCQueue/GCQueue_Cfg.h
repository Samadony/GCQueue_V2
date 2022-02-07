/*
 * GCQueue_Cfg.h
 *
 *  Created on: 1 Feb 2022
 *      Author: ahmed
 */

#ifndef INC_GCQUEUE_CFG_H_
#define INC_GCQUEUE_CFG_H_

#include <stdbool.h>
/*
 * Circular buffer configurations
 * preferably for compitability with different embedded target applications
 * the size shall be divisble by 2(16-bit target) and by 4(32 bit target)
 * TODO: warning or error implementations
 */
#define QUEUE_ENABLE_OVR_WRT			true
#define QUEUE_ERASE_VALUE				0x00UL

/*TODO: add macro helper here to add this pattern into the hard erase API*/
/*
 * There will be always one extra place need to be used, best that the user
 * adapt the numbe to be divisible by MEMORY_WORD knowing that there will be
 * always size - 1 used to check the memory status (full not full)
 *
 * The size shall be divisible by memory word if fast access is needed with considerations of packing and padding
 */
#define QUEUE_BUFFER_MEMORY_SECTION
#define QUEUE_BUFFER_PACKING

/*
 * Critical section levels:
 * 	- Level_0: No critical section
 * 	- Level_1: Mutex
 * 	- Level_2: OS interrupt disabling
 * 	- Level_3: Disable all interrupts
 */
#define QUEUE_CONCURRENCY_LVL_ZERO		0
#define QUEUE_CONCURRENCY_LVL_ONE		1
#define QUEUE_CONCURRENCY_LVL_TWO		2
#define QUEUE_CONCURRENCY_LVL_THREE		3

#define QUEUE_CONCURRENCY_LVL		QUEUE_CONCURRENCY_LVL_ZERO

#endif /* INC_GCQUEUE_CFG_H_ */

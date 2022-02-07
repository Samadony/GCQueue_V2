/*
 * ConsolePublisher.h
 *
 *  Created on: 2 Feb 2022
 *      Author: ahmed
 */

#ifndef CONSOLEPUBLISHER_CONSOLEPUBLISHER_H_
#define CONSOLEPUBLISHER_CONSOLEPUBLISHER_H_
#include "defines.h"
#include<stdint.h>

#define CP_GCQ_TYPE							uint32_t
/*
 * Initialize the ConsolePublisher
 */
PUBLIC_API void ConsolePublisher(void);

/*
 * Buffer write wrapper, used by the producer
 * Synchronous writing.
 * Used by the producer
 */
PUBLIC_API void CP_BufferData(CP_GCQ_TYPE copy_data_to_buffer);

/*
 * Buffer read wrapper, used by the consumer (this module)
 * This activity is periodic.
 * Used by the consumer "this module"
 */
PUBLIC_API void CP_ShowData();
#endif /* CONSOLEPUBLISHER_CONSOLEPUBLISHER_H_ */

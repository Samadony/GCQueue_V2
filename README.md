# Queue data structure in C
A Generic Circular FIFO template in C99
- Generic since it takes any premitive type
- Circular since read and write with a configurable over writting (enable/disable)
- Concurrent access through embeddded critical section during writing or reading the queue header

# Usage
- Use the GCQueue_Interface.h to have an access to the API and the buffer instantiator
- Use GCQueue_Cfg to configure the queue:
  - Critical Section Level
  - Circular or Not 

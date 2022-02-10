# GCQueue_V2
A generic circular FIFO template in C99
- generic, takes any premitive type
- Circular read and write with a configurable over writting (enable/disable)
- Concurrent access through embeddded critical section during writing or reading the queue header

# Usage
- Use the GCQueue_Interface.h to have an access to the API and the buffer instantiator
- USe GCQueue_Cfg to configure the queue: 1- critical section level 2- queue overwriting capabilities 

# memory-allocator

This is a virtual memory allocator which keeps track of allocated memory and free memory using two arrays.
When you allocate memory, it gets removed from the free memory array and inserted into the allocated memory.
When you free memory, it gets removed from the allocated memory array and inserted into the free memory array.
The stats of the memory at the given point in time can be recorded through the use of the mem_stats_struct, 
(number of used blocks, number of free blocks, maximim size allocated memory block, minimum size allocated memory block,
maximim size free memory block, minimum size free memory block) 

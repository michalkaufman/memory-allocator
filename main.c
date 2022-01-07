#include <stdio.h>
#include <stdlib.h>

//initialize arrays to keep track of allocated and free memory blocks
int free_mem[10];
int alloc_mem[10];

int main(int argc, char **argv)
{
  unsigned int global_mem_size = 1024 * 1024;
  unsigned char *global_memory = malloc(global_mem_size);

  mem_init(global_memory, global_mem_size);
  print_stats("init");

  unsigned char *ptr_array[10];
  unsigned int sizes[] = {50, 20, 20, 20, 50, 0};

  for (int i = 0; sizes[i] != 0; i++) {
    char buf[1024];
    ptr_array[i] = my_malloc(sizes[i]);
    
    sprintf(buf, "after iteration %d size %d", i, sizes[i]);
    print_stats(buf);
  }

  my_free(ptr_array[1]);  print_stats("after free #1");

  my_free(ptr_array[3]);  print_stats("after free #3");

  my_free(ptr_array[2]);  print_stats("after free #2");

  my_free(ptr_array[0]);  print_stats("after free #0");

  my_free(ptr_array[4]);  print_stats("after free #4");
}

typedef struct  {
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;


struct link{

  int size;       //bytes
  int *prev;       //preceding block in linked list
  int *next;       //succeeding block
};
  typedef struct link Block;


void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
  //initialize the 0th element of free mem array as the size of the memory passed in
  free_mem[0]= my_mem_size;
  
}

void my_malloc(unsigned size){
    //locate a free block that size in array of free blocks or bigger
    int min_big_enough = 0;
    int min_index = -1;
    
    int i;
  for(i=0; i <= 10 != 0; i++){
      if ((free_mem[i] >= size) & ((min_big_enough == 0) | (free_mem[i] <= min_big_enough)) ){
          min_big_enough = free_mem[i];
          min_index = i;
      }
  }
      //if block is bigger than requested size, divide it 
      //allocate the mem you need, leaving behind the remaining mem in a block at same index
      //leave the remaining memory in the same index representing the now smaller block
      //otherwise its fully allocated, and it leaves behind an empty space, set to 0
    free_mem[min_index] = free_mem[min_index]- size;
    
    //insert memory size into allocated mem array at a position of value 0
    int j;
    for(j =-1; alloc_mem[j] != 0 ; j++){}
    
    alloc_mem[j+1]= size;
      }
      


void my_free(void *mem_pointer){
  //free this address thats being pointed to by memory pointer
  //add this address's size to the array of free address sizes
  int mem_size = sizeof(mem_pointer);
  
  //remove chunk of appropriate size, replacing it with 0
  int i;
  for(i =-1; alloc_mem[i] != mem_size ; i++){}
  alloc_mem[i+1]= 0;
  
  //insert memory size into free mem array at a position of value 0
  int j;
  for(j =-1; free_mem[j] != 0 ; j++){}
    
    free_mem[j+1]= mem_size;

}




//collect the stats
void mem_get_stats(mem_stats_ptr mem_stats_ptr){
    //loop through allocated mem array
    //determine num blocks with non-zero value
    int num_used = 0;
    //store the max and min used block values
    int used_min = 0;
    int used_max = 0;
    int i;
    for(i=0; i<=10; i++){
        if (alloc_mem[i] != 0){
            num_used++;
            if (used_min == 0){
                used_min = alloc_mem[i];
            }
            else if (alloc_mem[i] <= used_min){
                used_min = alloc_mem[i];
            }
            if (used_max == 0){
                used_max = alloc_mem[i];
            }
            else if (alloc_mem[i] >= used_max){
                used_max = alloc_mem[i];
            }
            
        } 
    }
    
    //loop through free mem array
    //determine num blocks with non-zero value
    int num_free = 0;
    //store the max and min free block values
    int free_min = 0;
    int free_max = 0;
    int j;
    for(j=0; j<=10; j++){
        if (free_mem[j] != 0){
            num_free++;
            if (free_min == 0){
                free_min = free_mem[j];
            }
            else if (free_mem[j] <= free_min){
                free_min = free_mem[j];
            }
            if (free_max == 0){
                free_max = free_mem[j];
            }
            else if (free_mem[j] >= free_max){
                free_max = free_mem[i];
            }
            
        } 
    }
    
    mem_stats_ptr->num_blocks_used = num_used;
    mem_stats_ptr->num_blocks_free = num_free;
    mem_stats_ptr->smallest_block_free = free_min;
    mem_stats_ptr->smallest_block_used = used_min;
    mem_stats_ptr->largest_block_free = free_max;
    mem_stats_ptr->largest_block_used = used_max;
} 


//print the stats
void print_stats(char *prefix) {
  mem_stats_struct mem_stats;

  mem_get_stats(&mem_stats);
  printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
	 prefix,
	 mem_stats.num_blocks_free,
	 mem_stats.num_blocks_used,
	 mem_stats.smallest_block_free,
	 mem_stats.largest_block_free,
	 mem_stats.smallest_block_used,
	 mem_stats.largest_block_used);
}

extern const unsigned int __attribute__((section("_linkergenerated"))) _splim;
extern const unsigned int __attribute__((section("_linkergenerated"))) _heap;
extern const unsigned int __attribute__((section("_linkergenerated"))) _stack;

#define STACK_VAR_PAD           0x0020
#define STACK_GUARD_BYTE        0xEE
#define BOT_RAM_ADDRESS         (0x80000000U)

#define TOP_OF_STACK_ADDR       (unsigned int)(&_stack)
#define BOT_OF_STACK_ADDR       (unsigned int)(&_splim)

#define TOP_OF_HEAP_ADDR        (BOT_OF_STACK_ADDR - 24U)
#define BOT_OF_HEAP_ADDR        (unsigned int)(&_heap)

#define TOP_OF_DATA_ADDR        (BOT_OF_HEAP_ADDR - 4U)
#define BOT_OF_DATA_ADDR        BOT_RAM_ADDRESS

#include "stack_monitoring.h"

void stack_monitoring_init(MEMORY_OBJ *mem_struct)
{
    char * ptr;
    unsigned int stop_addr;

    //Use a variable on the stack
    char stack_var;

    ptr = &stack_var;
    stop_addr = (unsigned long int)ptr - STACK_VAR_PAD;
    
    ptr = (char *)BOT_OF_STACK_ADDR + 1;
    while((unsigned long int)ptr < stop_addr)
    {
        *ptr = (char)STACK_GUARD_BYTE;
        ptr++;
    }

	mem_struct->data_size = TOP_OF_DATA_ADDR - BOT_OF_DATA_ADDR;
	mem_struct->stack_size = TOP_OF_STACK_ADDR - BOT_OF_STACK_ADDR;
	mem_struct->heap_size = TOP_OF_HEAP_ADDR - BOT_OF_HEAP_ADDR;
	
    return;
}

unsigned int stack_monitoring_measure_unused_stack(void)
{
    char * ptr;
    unsigned int unused_stack_size = 0;
    
    ptr = (char *)BOT_OF_STACK_ADDR + 1;

    while(*ptr == (char)STACK_GUARD_BYTE)
    {
        ptr++;
        unused_stack_size++;
    }
    return unused_stack_size;
}
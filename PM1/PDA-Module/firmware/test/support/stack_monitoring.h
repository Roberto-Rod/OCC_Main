#ifndef STACK_MONITORING_H
#define STACK_MONITORING_H

typedef struct {
	unsigned int data_size;
	unsigned int stack_size;
	unsigned int heap_size;
} MEMORY_OBJ;

void stack_monitoring_init(MEMORY_OBJ *);
unsigned int stack_monitoring_measure_unused_stack(void);

#endif //STACK_MONITORING_H
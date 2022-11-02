#ifndef _DATA_TYPES_H
#define _DATA_TYPES_H

// Como data types meant to be used in Kernel and Userland

typedef struct process_info{
	char * name; 
	unsigned int id;
	uint8_t state;
	uint8_t priority;
	uint64_t stack;
	uint64_t rsp;
	uint64_t pickd;
	uint8_t screen;
}process_info;

typedef struct semaphore_info{
	unsigned int id;
	unsigned int value;
	unsigned int num_blocked;
	unsigned int blocked_pids[10];
}semaphore_info;

typedef struct pipes_info{
	unsigned int id;
	unsigned int usage;
	unsigned int read_num_blocked;
	unsigned int read_blocked_pids[10];
	unsigned int write_num_blocked;
	unsigned int write_blocked_pids[10];
}pipes_info;


#endif

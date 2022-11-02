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


#endif

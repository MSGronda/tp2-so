#include <child_process.h>

#define MAX_WAIT_TASKS 30

#define NOT_TRACKING 0	// singals that space is empty and ready to use
#define RUNNING 1
#define FINISHED 2

typedef struct wait_info{
	unsigned int fatherPid;
	unsigned int childPid;
	uint8_t state;
}wait_info;

static wait_info wait_table[MAX_WAIT_TASKS] = {0};		// TODO: tira warning

uint8_t has_children(unsigned int pid){
	for(int i=0; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].fatherPid == pid){
			return 1;
		}
	}
	return 0;
}

void signal_process_finished(unsigned int pid){

	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if( wait_table[i].state == RUNNING && wait_table[i].childPid == pid){
			wait_table[i].state = FINISHED;
			return;
		}
	}
}

void remove_children(unsigned int fatherPid){
	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].fatherPid == fatherPid){
			wait_table[i].fatherPid = 0;
			wait_table[i].childPid = 0;
			wait_table[i].state = NOT_TRACKING;
		}
	}
}

void add_child(unsigned int fatherPid, unsigned int childPid){
	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].state == NOT_TRACKING){

			wait_table[i].fatherPid = fatherPid;
			wait_table[i].childPid = childPid;
			wait_table[i].state = RUNNING;
			return;
		}
	}
}

// checks if ALL children that are being tracked have finished
uint8_t children_finished(unsigned int fatherPid){

	for(int i=0; i< MAX_WAIT_TASKS; i++){
		if(wait_table[i].state == RUNNING && wait_table[i].fatherPid == fatherPid){
			return 0;
		}	
	}

	return 1;
}




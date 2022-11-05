// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

static wait_info wait_table[MAX_WAIT_TASKS] = {{0}};	

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


			// Check if siblings are alive. If they're all dead wake up parent.

			unsigned int father = wait_table[i].fatherPid;
			if(children_finished(father)){
				remove_children(father);
				alter_process_state(father, ACTIVE_PROCESS);
			}

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


void wait_for_children(){
	int pid = get_current_pid();
	if(!has_children(pid)){
		return;
	}

	alter_process_state(pid, WAITING_FOR_CHILD);

	forceChangeTask();
}


unsigned int add_child_task(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0){
	unsigned int child_pid = add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL , arg0);

	add_child(get_current_pid(), child_pid);

	return child_pid;
}




#include <semaphore.h>

#define MAX_SEMAPHORES 20
#define MAX_WAITING_PROCESS 20


// we will also apply round robin in this case 
// in order to avoid process being continually blocked

typedef struct sem_record{
	unsigned int sem_id;
	unsigned int value;
	unsigned int blocked_pids[MAX_WAITING_PROCESS]; 
	unsigned int currentBlocked;
}sem_record;

static sem_record sem_info[MAX_SEMAPHORES] = {0};

static unsigned int active_sem = 0;

int find_sem(unsigned int sem_id){
	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[i].sem_id == sem_id){
			return i;
		}
	}
	return -1;
}

int find_sem_pid(unsigned int pid){
	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[i].sem_id != 0){

			for(int j=0;j<MAX_WAITING_PROCESS; j++){
				if(sem_info[i].blocked_pids[j] = pid){
					return i;
				}
			}

		}
	}
	return -1;
}

unsigned int create_sem(unsigned int sem_id){
	if(sem_id == 0)				// 0 is reserved to denote empty record
		return INVALID_SEM_ID;
	if(active_sem == MAX_SEMAPHORES)
		return ERROR_NO_MORE_SPACE;

	int freePos = -1;
	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(freePos == -1 && sem_info[i].sem_id == 0){
			freePos = i;
		}
		if(sem_info[i].sem_id == sem_id){
			return INVALID_SEM_ID;
		}
	}

	sem_info[freePos].sem_id = sem_id;
	sem_info[freePos].value = 1;			// default start is always 1

	active_sem++;

	return SUCCESS;
}


// searches (using the sem_id) and decreases the semaphore
void sem_decrease_semid(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos==-1)
		return;
	sem_info[pos].value--;
}
// searches (using the pid of a blocked process) and decreases the semaphore
void sem_decrease_pid(unsigned int pid){
	int pos = find_sem_pid(pid);
	if(pos==-1)
		return;
	sem_info[pos].value--;
}

unsigned int signal_sem(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos == -1){
		return INVALID_SEM_ID;
	}
	return ++sem_info[pos].value;
}


// add the waiting proces to en END OF THE QUEUE
void add_waiting(unsigned int sem_id, unsigned int pid){
	int pos = find_sem(sem_id);
	if(pos == -1)
		return;
	for(int i=sem_info[pos].currentBlocked, counter=0; counter<MAX_WAITING_PROCESS; counter++){
		if(sem_info[pos].blocked_pids[i] == 0){
			sem_info[pos].blocked_pids[i] = pid;
			return;
		}
		i = (i + 1) % MAX_WAITING_PROCESS;
	}
}

void remove_waiting(unsigned int pid){
	int pos = find_sem_pid(pid);
	if(pos == -1)
		return;
	for(int i=0; i<MAX_WAITING_PROCESS; i++ ){
		if(sem_info[pos].blocked_pids[i] == pid){
			sem_info[pos].blocked_pids[i] = 0;
			return;
		}
	}
}


// checks sem > 0 and if there are any other process waiting for this sem
// using the sem id
uint8_t can_continue_semid(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos==-1)
		return -1;
	for(int i=0; i<MAX_WAITING_PROCESS; i++){
		if(sem_info[pos].blocked_pids[i] != 0){
			return 0;		// si hay cualquier otro proceso esperando, no puedo continuar
		}
	}
	return sem_info[pos].value > 0;
}
// checks sem > 0 and if the process is the next in the round robin queue for this sem
// using the pid of a blocked process
uint8_t can_continue_pid(unsigned int pid){
	int pos = find_sem_pid(pid);
	if(sem_info[pos].value == 0){
		return 0;
	}

	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[pos].blocked_pids[sem_info[pos].currentBlocked] != 0){
			if(sem_info[pos].blocked_pids[sem_info[pos].currentBlocked] != pid){
				return 0;
			}
			else{
				return 1;
			}
		} 	
		sem_info[pos].currentBlocked = (sem_info[pos].currentBlocked + 1) % MAX_WAITING_PROCESS;
	}
	return 1;
}
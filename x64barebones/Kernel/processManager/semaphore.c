#include <semaphore.h>

#define MAX_SEMAPHORES 40

typedef struct sem_record{
	unsigned int sem_id;
	unsigned int value;
}sem_record;

typedef struct waiting_process{
	unsigned int sem_id;
	unsigned int pid;
}waiting_process;

static waiting_process waiting[MAX_SEMAPHORES] = {0};
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


unsigned int create_sem(unsigned int sem_id){
	if(sem_id == 0)				// 0 is reserved to denote empty record
		return INVALID_SEM_ID;
	if(active_sem == MAX_SEMAPHORES)
		return ERROR_NO_MORE_SPACE;

	int freePos;
	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[i].sem_id == 0){
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


int update_sem_table(unsigned int sem_id){
	int pos = find_sem(sem_id);

	if(pos == -1){
		return INVALID_SEM_ID;
	}

	if(sem_info[pos].value > 0){
		sem_info[pos].value--;
		return SEM_CONTINUE;
	}
	else{
		return SEM_BLOCK;
	}
}


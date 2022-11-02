#include <semaphore.h>

#define MAX_SEMAPHORES 50
#define MAX_WAITING_PROCESS 20


// we will also apply round robin in this case 
// in order to avoid process being continually blocked

typedef struct sem_record{
	unsigned int sem_id;
	unsigned int sem_value;
	unsigned int lock;


	queueADT queue;
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

int find_available_sem_id(){
	if(active_sem == MAX_SEMAPHORES)
		return ERROR_NO_MORE_SPACE;

	uint8_t found = 0;
	int sem_id = 10;

	while(!found){
		found = 1;
		for(int i=0; i<MAX_SEMAPHORES; i++){
			if(sem_info[i].sem_id == sem_id){
				found = 0;
				sem_id++;
				break;
			}
		}
	}
	return sem_id;
}



int create_sem_available(unsigned int value){
	int id = find_available_sem_id();

	if(id == ERROR_NO_MORE_SPACE){
		return ERROR_NO_MORE_SPACE;
	}

	if( create_sem(id, value) != SUCCESS){
		return ERROR_NO_MORE_SPACE;
	}
	return id;
}

int create_sem(unsigned int sem_id, unsigned int value){
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

	init_queue(&(sem_info[freePos].queue), MAX_WAITING_PROCESS);

	sem_info[freePos].sem_id = sem_id;
	sem_info[freePos].sem_value = value;

	active_sem++;

	return SUCCESS;
}

void destroy_sem(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos == -1)
		return;

	lock(&(sem_info[pos].lock));
	sem_info[pos].sem_id = 0;
	sem_info[pos].sem_value = 0;

	destroy_queue(&(sem_info[pos].queue));

	unlock(&(sem_info[pos].lock));
}

unsigned int wait_sem(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos == -1)
		return -1;

	lock(&(sem_info[pos].lock));
	if(sem_info[pos].sem_value > 0){
		int sem = sem_info[pos].sem_value;
		sem_info[pos].sem_value--;
	}
	else{
		int pid = get_current_pid();
		alter_process_state(pid, WAITING_FOR_SEM);
		enqueue(&(sem_info[pos].queue), pid);

		unlock(&(sem_info[pos].lock));
		forceChangeTask();
		return 1;
	}


	unlock(&(sem_info[pos].lock));

	return 1;
}

unsigned int signal_sem(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos == -1){
		return INVALID_SEM_ID;
	}

	lock(&(sem_info[pos].lock));
	if(size_queue(&(sem_info[pos].queue)) > 0){			// prevent process being eternally blocked

		unsigned int blocked_pid = (unsigned int) dequeue(&(sem_info[pos].queue));
		alter_process_state(blocked_pid, ACTIVE_PROCESS);
	}
	else{
		int sem = sem_info[pos].sem_value;
		sem_info[pos].sem_value++;
	}

	unlock(&(sem_info[pos].lock));
	return 1;
}



/* - - - Print info - - - */

unsigned int get_sem_blocked_process(unsigned int i, unsigned int * blocked_pids){	
	if(size_queue(&(sem_info[i].queue)) > 0){
		unsigned int pos;
		new_iterator_queue(&(sem_info[i].queue), &pos);

		int k=0;
		for( ;has_next_queue(&(sem_info[i].queue), &pos); k++ ){
			blocked_pids[k] = (unsigned int) next_queue(&(sem_info[i].queue), &pos);
		}
		return k;
	}
	return 0;
}

uint64_t get_semaphore_info(semaphore_info * info){
	int j=0;
	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[i].sem_id != 0){
			info[j].id = sem_info[i].sem_id;
			info[j].value = sem_info[i].sem_value;

			info[j].num_blocked = get_sem_blocked_process(i, info[j].blocked_pids);

			j++;
		}
	}
	return j;
}

unsigned int get_blocked_by_sem_id(unsigned int sem_id, unsigned int * blocked_pids){
	int pos = find_sem(sem_id);
	if(pos == -1)
		return;

	return get_sem_blocked_process((unsigned int)pos, blocked_pids);
}



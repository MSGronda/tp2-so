#include <semaphore.h>

#define MAX_SEMAPHORES 50
#define MAX_WAITING_PROCESS 20


// we will also apply round robin in this case 
// in order to avoid process being continually blocked

typedef struct sem_record{
	unsigned int sem_id;
	unsigned int sem_value;
	unsigned int blocked_pids[MAX_WAITING_PROCESS]; 
	unsigned int currentBlocked;
	unsigned int num_blocked; 
	unsigned int lock;
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


unsigned int remove_next_blocked(unsigned int pos){
	for(int i=0; i<MAX_WAITING_PROCESS ; i++){
		if(sem_info[pos].blocked_pids[sem_info[pos].currentBlocked] != 0){
			int pid = sem_info[pos].blocked_pids[sem_info[pos].currentBlocked];
			sem_info[pos].blocked_pids[sem_info[pos].currentBlocked] = 0;
			sem_info[pos].num_blocked--;
			sem_info[pos].currentBlocked = (sem_info[pos].currentBlocked + 1) % MAX_WAITING_PROCESS;
			return pid;
		}
		sem_info[pos].currentBlocked = (sem_info[pos].currentBlocked + 1) % MAX_WAITING_PROCESS;
	}
	return 0;
}

void add_blocked(unsigned int pos, unsigned int pid){
	for(int i=sem_info[pos].currentBlocked, count=0; count<MAX_WAITING_PROCESS; count++){
		if(sem_info[pos].blocked_pids[i] == 0){
			sem_info[pos].blocked_pids[i] = pid;
			sem_info[pos].num_blocked++;
			return;
		}
		i = (i+1) % MAX_WAITING_PROCESS;
	}
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
	sem_info[pos].num_blocked = 0;
	sem_info[pos].currentBlocked = 0;
	for(int i=0; i<MAX_WAITING_PROCESS; i++){
		sem_info[pos].blocked_pids[i] = 0;
	}
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
		add_blocked(pos, pid);
		alter_process_state(pid, WAITING_FOR_SEM);

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
	if(sem_info[pos].num_blocked > 0){			// prevent process being eternally blocked
		int blocked_pid = remove_next_blocked(pos);
		alter_process_state(blocked_pid, ACTIVE_PROCESS);
	}
	else{
		int sem = sem_info[pos].sem_value;
		sem_info[pos].sem_value++;
	}

	unlock(&(sem_info[pos].lock));
	return 1;
}




void print_blocked_by_id(unsigned int sem_id){
	int pos = find_sem(sem_id);
	if(pos == -1)
		return;

	int len;
	char buffer[20];

	int out = get_current_output();

	writeDispatcher(out,"\nBlocked processes: \n", 21);
	for(int j=0; j<MAX_WAITING_PROCESS; j++){
		if(sem_info[pos].blocked_pids[j] != 0){
			writeDispatcher(out,"     -Pid: ", 11);
			len = num_to_string(sem_info[pos].blocked_pids[j], buffer);
			writeDispatcher(out, buffer, len);
			writeDispatcher(out,"\n",1);
		}
	}
	writeDispatcher(out,"\n",1);
}

void print_sem(){
	int len;
	char buffer[20];

	int out = get_current_output();

	writeDispatcher(out,"-=-=-=-=-= Sem Info =-=-=-=-=-\n", 31);

	for(int i=0; i<MAX_SEMAPHORES; i++){
		if(sem_info[i].sem_id != 0){
			writeDispatcher(out,"Sem Id: ",8);
			len = num_to_string(sem_info[i].sem_id, buffer);
			writeDispatcher(out, buffer, len);

			writeDispatcher(out," | Value: ",10);

			len = num_to_string(sem_info[i].sem_value, buffer);
			writeDispatcher(out, buffer, len);

			writeDispatcher(out,"\nBlocked processes: \n", 21);
			for(int j=0; j<MAX_WAITING_PROCESS; j++){
				if(sem_info[i].blocked_pids[j] != 0){
					writeDispatcher(out,"     -Pid: ", 11);
					len = num_to_string(sem_info[i].blocked_pids[j], buffer);
					writeDispatcher(out, buffer, len);
					writeDispatcher(out,"\n",1);
				}
			}
			writeDispatcher(out,"\n",1);
		}
	}
}

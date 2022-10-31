#include <pipes.h>

#define MAX_PIPES 30
#define PIPE_SIZE 1024

/* 
	A clear example of producers and consumers.
   	The write semaphore tracks how many free
   	spaces there are in the buffer and the
   	read semaphore tracks how many filled spaces
   	there are.
*/

typedef struct pipe_record{
	unsigned int pipe_id;

	int read_sem_id;
	int write_sem_id;

	unsigned int write_pos;
	unsigned int read_pos;
	uint8_t * pipe;
	unsigned int amount;
}pipe_record;

static pipe_record pipe_info[MAX_PIPES];
static unsigned int num_pipes = 0;

int find_pipe(unsigned int pipe_id){
	for(int i=0; i<MAX_PIPES; i++){
		if(pipe_info[i].pipe_id == pipe_id){
			return i;
		}
	}
	return -1;
}

int find_available_pipe_id(){
	if(num_pipes == MAX_PIPES)
		return ERROR_NO_MORE_SPACE;

	uint8_t found = 0;
	int pipe_id = 10;

	while(!found){
		found = 1;
		for(int i=0; i<MAX_PIPES; i++){
			if(pipe_info[i].pipe_id == pipe_id){
				found = 0;
				pipe_id++;
				break;
			}
		}
	}
	return pipe_id;
}


int create_pipe_available(){
	int id = find_available_pipe_id();

	if(id == ERROR_NO_MORE_SPACE){
		return ERROR_NO_MORE_SPACE;
	}
	
	if( create_pipe(id) != SUCCESS){
		return ERROR_NO_MORE_SPACE;
	}
	

	return id;
}

int create_pipe(unsigned int pipe_id){
	if(pipe_id == 0)				// 0 is reserved to denote empty record
		return INVALID_PIPE_ID;
	if(num_pipes == MAX_PIPES)
		return ERROR_NO_MORE_SPACE;

	int freePos = -1;
	for(int i=0; i<MAX_PIPES; i++){
		if(freePos == -1 && pipe_info[i].pipe_id == 0){
			freePos = i;
		}
		if(pipe_info[i].pipe_id == pipe_id){
			return INVALID_PIPE_ID;
		}
	}

	// create semaphore
	int sem_id1 = create_sem_available(0);
	int sem_id2 = create_sem_available(PIPE_SIZE);
	if(sem_id1 == -1 || sem_id2 == -1){
		destroy_sem(sem_id1);
		destroy_sem(sem_id2);
		return ERROR_NO_MORE_SPACE;
	}
	// create pipe
	pipe_info[freePos].pipe = mm_malloc(PIPE_SIZE);
	if(pipe_info[freePos].pipe == NULL){
		destroy_sem(sem_id1);
		destroy_sem(sem_id2);
		return ERROR_NO_MORE_SPACE;
	}

	pipe_info[freePos].pipe_id = pipe_id;
	pipe_info[freePos].read_sem_id  = sem_id1;
	pipe_info[freePos].write_sem_id  = sem_id2;
	pipe_info[freePos].write_pos = 0;
	pipe_info[freePos].read_pos = 0;
	pipe_info[freePos].amount = 0;
	
	num_pipes++;

	return SUCCESS;
}


void destroy_pipe(unsigned int pipe_id){
	int pos = find_pipe(pipe_id);
	if(pos == -1)
		return;
	destroy_sem(pipe_info[pos].write_sem_id);	
	destroy_sem(pipe_info[pos].read_sem_id);
	mm_free(pipe_info[pos].pipe);

	pipe_info[pos].read_sem_id  = 0;
	pipe_info[pos].write_sem_id  = 0;
	pipe_info[pos].pipe_id = 0;
	pipe_info[pos].write_pos = 0;
	pipe_info[pos].read_pos = 0;
	pipe_info[pos].amount = 0;
	pipe_info[pos].pipe = 0;

	num_pipes--;
}


void write_to_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count){
	int pos = find_pipe(pipe_id);
	if(pos == -1)
		return;
	
	for(int i=0; i<count; i++){
		wait_sem(pipe_info[pos].write_sem_id);

		pipe_info[pos].pipe[pipe_info[pos].write_pos] = src[i];
		INCREASE_MOD(pipe_info[pos].write_pos, PIPE_SIZE);
		pipe_info[pos].amount++;

		signal_sem(pipe_info[pos].read_sem_id);
	}
}

void read_from_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count){
	int pos = find_pipe(pipe_id);
	if(pos == -1)
		return;
		
	for(int i=0; i<count; i++){
		wait_sem(pipe_info[pos].read_sem_id);

		dest[i] = pipe_info[pos].pipe[pipe_info[pos].read_pos];
		INCREASE_MOD(pipe_info[pos].read_pos, PIPE_SIZE);
		pipe_info[pos].amount--;
		
		signal_sem(pipe_info[pos].write_sem_id);
	}
}

void print_pipe(){
	int len;
	char buffer[20];

	writeDispatcher(get_current_output(),"-=-=-=-=-= Pipe Info =-=-=-=-=-\n", 32);

	for(int i=0; i<MAX_PIPES; i++){
		if(pipe_info[i].pipe_id != 0){
			writeDispatcher(get_current_output(),"Pipe Id: ",9);
			len = num_to_string(pipe_info[i].pipe_id, buffer);
			writeDispatcher(get_current_output(), buffer, len);

			writeDispatcher(get_current_output()," | Usage: ",10);

			len = num_to_string(pipe_info[i].amount / PIPE_SIZE, buffer);
			writeDispatcher(get_current_output(), buffer, len);

			writeDispatcher(get_current_output(),"\n",1);
		}
	}
}



#include <pipes.h>

#define MAX_PIPES 30
#define PIPE_SIZE 10

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
	unsigned int sem_resp1 = INVALID_SEM_ID, sem_resp2 = INVALID_SEM_ID;
	int sem_id1 = 1, sem_id2 = 2;
	for( ; sem_resp1 == INVALID_SEM_ID || sem_resp2 == INVALID_SEM_ID; ){
		if(sem_resp1 == INVALID_SEM_ID){
			sem_resp1 = create_sem(++sem_id1, 0);
		}
		if(sem_resp2 == INVALID_SEM_ID){
			sem_resp2 = create_sem(++sem_id2, PIPE_SIZE);
		}
	}
	if(sem_resp1 == ERROR_NO_MORE_SPACE || sem_resp2 == ERROR_NO_MORE_SPACE){
		return ERROR_NO_MORE_SPACE;
	}
	
	// create pipe
	pipe_info[freePos].pipe = mm_malloc(PIPE_SIZE);
	if(pipe_info[freePos].pipe == NULL){
		destroy_sem(pipe_info[freePos].read_sem_id);
		destroy_sem(pipe_info[freePos].write_sem_id);
		return ERROR_NO_MORE_SPACE;
	}

	pipe_info[freePos].read_sem_id  = sem_id1;
	pipe_info[freePos].write_sem_id  = sem_id2;
	pipe_info[freePos].pipe_id = pipe_id;
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
	
}


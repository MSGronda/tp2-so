#include <semaphore.h>

#define MAX_SEMAPHORES 40

static unsigned int newSemId = 0;

typedef struct sem_record{
	char * indentifier;
	unsigned int sem_id;
	unsigned int value;
}sem_record;

typedef struct waiting_process{
	unsigned int sem_id;
	unsigned int pid;
}waiting_process;

static waiting_process waiting[MAX_SEMAPHORES];
static sem_record sem_info[MAX_SEMAPHORES];

void wait(sem_id){

}


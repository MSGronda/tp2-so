// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <multitasking.h>

// ---- Constantes ----
#define TOTAL_TASKS 20
#define STACK_SIZE 4096

#define MAX_PRIORITY 5

// ---- Valores default para el armado del stack ----
#define FLAG_VALUES 0x202
#define SS_VALUE 0x0				// en nuestro caso se mantiene constante
#define CS_VALUE 0x8

// ------Posiciones para el armado de stack para cada proceso------
										/*		 -=-=STACK=-=-		*/
#define STACK_POINT_OF_ENTRY (21*8)   	/*  	|	RAX, RBX  |		*/
										/*  	|	RCX, etc  |		*/   
#define RDI_POS   (12*8)				/*		---------------		*/ 
#define IP_POS    (6*8)					/*  	|	 RIP	  |		*/				
#define CS_POS 	  (5*8)					/*  	|	  CS	  |		*/
#define FLAGS_POS (4*8)					/*  	|	 RFLAGS	  |		*/
#define SP_POS 	  (3*8)					/*  	|	 RSP	  |		*/
#define SS_POS	  (2*8)					/*  	|	  SS	  |		*/
#define RET_POS 	8 					/*  	|	 RET	  |		*/
#define ALINGMENT 8		 				/*   	 -------------		*/

#define STACK_POS(POS) (uint64_t *) (stackStart - (POS))


// -----Informacion sobre cada task-----
typedef struct process_control_block{
		unsigned int pid;				// unique identifier. value is > 0

		uint64_t  stackPointer;			// value of rsp 
		uint64_t  stackSegment;  		// value of ss. This one is constant = 0
		void * stackStart;
		void * stackEnd;
		char ** params;

		uint8_t state;
		uint8_t priority;				// the amount of ticks it has to run
		uint8_t immortal;				// whether it can or can't be killed/blocked/paused

		uint8_t input;
		uint8_t output;

		uint64_t ticks;					// the amount of times the scheduler picked it to run
}process_control_block;

// ------ Queue de tasks -------
static process_control_block tasks[TOTAL_TASKS];

static unsigned int newPidValue = 1;					// identificador para cada proceso
	
static unsigned int currentTask = 0;				// posicion en el array
static unsigned int currentRemainingTicks = 0;			// How many timer ticks are remaining for the current process.
static unsigned int currentDimTasks = 0;

static unsigned int idleTaskPid = 1;

/* =========== CODE =========== */

/* --- Init --- */
static char * idleArg[] = {"idle", NULL};

void idleTask(){
	while(true)
		_hlt();
}

void enableMultiTasking(){

	idleTaskPid = add_task((uint64_t)&idleTask, STDIN, BACKGROUND, DEFAULT_PRIORITY, IMMORTAL,idleArg);
	
	alter_process_state(idleTaskPid, PAUSED_PROCESS);		// we pause the idle task until its actually needed (that being when all other tasks are paused)

	forceCurrentTask();
}


/* --- Getters --- */
unsigned int get_current_pid(){
	return tasks[currentTask].pid;
}
uint64_t getRSP(){
	return tasks[currentTask].stackPointer;
}
uint64_t getSS(){
	return tasks[currentTask].stackSegment;
}
uint8_t get_current_output(){
	return tasks[currentTask].output;
}
uint8_t get_current_input(){
	return tasks[currentTask].input;
}

uint8_t get_state(unsigned int pid){
	int pos = findTask(pid);
	if(pos==NO_TASK_FOUND)
		return NO_TASK_FOUND;
	
	return tasks[pos].state;
}

// Encuentro el task usando el pid
int findTask(unsigned int pid){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].pid == pid && tasks[i].state != DEAD_PROCESS)
			return i;
	}	
	return NO_TASK_FOUND;			// no existe task con ese pid
}




/* --- Creation and destruction --- */

uint64_t build_stack(uint64_t entrypoint, char ** arg0, uint64_t stackEnd){

	// Get end of stack and allign it 
	uint64_t stackStart = stackEnd + STACK_SIZE;
	stackStart -= stackStart % ALINGMENT;

	// --- Function parameters ---
	*(STACK_POS(RDI_POS)) = (uint64_t) arg0;

	// --- We put all registers to 0 ---
	for(int i=7 ; i<21 ; i++){
		if(i!=12)
			*(STACK_POS(i * 8)) = 0;
	}

	// --- "Stack frame" for process ---

	*(STACK_POS(IP_POS)) = entrypoint;	
	*(STACK_POS(CS_POS)) = CS_VALUE;				
	
	*(STACK_POS(FLAGS_POS)) = FLAG_VALUES;
	
	*(STACK_POS(SP_POS)) = stackStart - RET_POS;
	*(STACK_POS(SS_POS)) = SS_VALUE;
	
	*(STACK_POS(RET_POS)) = (uint64_t) &removeCurrentTask;		// the RET of the function will automatically remove it from the queue

	return stackStart;
}

int add_task(uint64_t entrypoint, uint8_t input, uint8_t output, uint8_t priority, uint8_t immortal, char ** arg0){
	if(currentDimTasks>=TOTAL_TASKS){
		return ERROR_NO_SPACE_FOR_TASK;
	}
	currentDimTasks++;

	int pos;
	for(pos=0; tasks[pos].state!=DEAD_PROCESS ;pos++);	// find a free space

	uint8_t * stackEnd = mm_malloc(STACK_SIZE);

	if(stackEnd == NULL)
		return ERROR_NO_SPACE_FOR_TASK;

	uint8_t * stackStart = (uint8_t *) build_stack(entrypoint, arg0, (uint64_t) stackEnd);

	// --- Datos de task ---
	tasks[pos].stackPointer = (uint64_t) stackStart - STACK_POINT_OF_ENTRY;	// stack start
	tasks[pos].stackSegment = SS_VALUE;							// is constant

	tasks[pos].pid = newPidValue++;
	tasks[pos].state = ACTIVE_PROCESS;
	tasks[pos].priority = priority;
	tasks[pos].immortal = immortal;

	tasks[pos].stackStart = stackStart;
	tasks[pos].stackEnd = stackEnd;

	tasks[pos].params = arg0;
	tasks[pos].ticks = 1;

	tasks[pos].input = input;
	tasks[pos].output = output;

	return tasks[pos].pid;
}

// params are null terminated array of pointers to strings
void free_params(char ** params){
	if(params==NULL)
		return;

	for(int i=0; params[i]!=NULL; i++){
		mm_free(params[i]);
	}
	mm_free(params);
}


void destroy_process(unsigned int pos){
	signal_process_finished(tasks[pos].pid);
	free_params(tasks[pos].params);
	tasks[pos].state = DEAD_PROCESS;
	currentDimTasks--;
	mm_free(tasks[pos].stackEnd);
}

void removeCurrentTask(){
	// We must insure that this is atomic, since we are freeing memory
	// that could be used by another process if this function were to
	// be interrupted by a timer tick.
	_cli();

	destroy_process(currentTask);
	
	// If the process is being piped, we signal that pipe will no longer
	// be use by process. 
	uint8_t out = tasks[currentTask].output;
	if(out != STDOUT && out != STDOUT_LEFT && out != STDOUT_RIGHT){
		signal_eof(out);
	}

	forceChangeTask();

}

void forceChangeTask(){
	currentRemainingTicks = tasks[currentTask].priority + 1;
	forceTimerTick();
}




/* --- Process management --- */

// alter state of all tasks that have a specific state
void alter_state_if(uint8_t old_state, uint8_t new_state){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS && tasks[i].state == old_state){
			tasks[i].state = new_state;
		}
	}
}

// alter state of a specific task
void alter_process_state(unsigned int pid, uint8_t new_state){
	int pos = findTask(pid);
	if(pos == NO_TASK_FOUND)
		return;

	tasks[pos].state = new_state;
}

void pauseScreenProcess(unsigned int screen){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != WAITING_FOR_CHILD && tasks[i].state != DEAD_PROCESS && tasks[i].output == screen){
			tasks[i].state = tasks[i].state==PAUSED_PROCESS ? ACTIVE_PROCESS : PAUSED_PROCESS; 	// pausado -> despausado  | despausado -> pausado
		}
	}
}

void kill_screen_processes(){
	uint8_t currentTaskKilled = false;
	for(int i=0; i< TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS &&  tasks[i].immortal != IMMORTAL ){		//TODO: que vuelva a ser solo los screen processes
			destroy_process(i);

			if(i == currentTask){
				currentTaskKilled = true;
			}
		}
	}

	// If the current process is killed, we do not want
	// to return to executing it, so we force the next
	// task.

	if(currentTaskKilled){
		forceChangeTask();
	}
}

// pauso o despauso proceso con el pid
int pauseOrUnpauseProcess(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// se quiere pausar task que no existe
		return NO_TASK_FOUND;

	if(tasks[pos].immortal)
		return TASK_NOT_ALTERED;

	tasks[pos].state = tasks[pos].state==PAUSED_PROCESS ? ACTIVE_PROCESS : PAUSED_PROCESS; 	// pausado -> despausado  | despausado -> pausado


	if(pos == currentTask){
		forceChangeTask();
	}

	return TASK_ALTERED;
}

int removeTask(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// se quiere remover task que no existe
		return NO_TASK_FOUND;

	if(tasks[pos].immortal)
		return TASK_NOT_ALTERED;

	destroy_process(pos);

	if(pos == currentTask){
		forceChangeTask();
	}

	return TASK_ALTERED;
}

unsigned int change_priority(unsigned int pid, int delta){
	int pos = findTask(pid);
	if(pos < 0)
		return NO_TASK_FOUND;

	if(delta > MAX_PRIORITY)
		tasks[pos].priority = MAX_PRIORITY;
	else if(delta < 1)
		tasks[pos].priority = DEFAULT_PRIORITY;
	else 	
		tasks[pos].priority = delta;

	return true;
}




/* --- Scheduling --- */

// se fija si le queda tiempo, si le queda, decrementa esa cantidad y
uint8_t has_or_decrease_time(){
	if(currentRemainingTicks < tasks[currentTask].priority - 1){
		tasks[currentTask].ticks++;
		currentRemainingTicks++;
		return true;
	}
	return false;

}
/*	
	Pasa al proximo task que se tiene que ejecutar. 
	Parametros:  stackPointer: puntero al stack del task anterior  |  stackSegment: valor del stack segment del task anterior  
*/

uint64_t next_task(uint64_t stackPointer, uint64_t stackSegment){

	tasks[currentTask].stackPointer = stackPointer;			// updateo el current
	tasks[currentTask].stackSegment = stackSegment;
	
	char found=0;
	unsigned int counter = 0;
	while( !found && counter < currentDimTasks ){			// busco el proximo stack
		
		currentTask = (currentTask +  1) % TOTAL_TASKS;

		if(tasks[currentTask].state != DEAD_PROCESS)		// to check if we have already passed by all the none dead processes 
			counter++;

		if(tasks[currentTask].state == ACTIVE_PROCESS){
			found = 1;
			tasks[currentTask].ticks++;
		}
	}

	// Special case: idle tasks. The idle task is only necesary when all of the other tasks are paused/waiting. 
	// By enabling it only in this special case, we save a lot of cpu usage (compared to leaving the idle task running constantly)

	if(counter == currentDimTasks){				// all tasks are none active (paused, waiting for...) -> we must wake up idle task
		currentTask = findTask(idleTaskPid);
		alter_process_state(idleTaskPid, ACTIVE_PROCESS);
	}
	else if(tasks[currentTask].pid != idleTaskPid){			// if a normal tasks is chosen -> pause idle task
		alter_process_state(idleTaskPid, PAUSED_PROCESS);
	}

	currentRemainingTicks = 0;		// reset del current task

	return tasks[currentTask].stackPointer;
}




/* --- Other --- */

int get_process_info(process_info * info){
	int j=0;
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS){

			if(tasks[i].params !=NULL){
				info[j].name = tasks[i].params[0];		// params[0] is alocated by user in heap. we are not sharing data from kernel space.
			}
			info[j].id = tasks[i].pid;
			info[j].state = tasks[i].state;
			info[j].priority = tasks[i].priority;
			info[j].stack = (uint64_t) tasks[i].stackStart;
			info[j].rsp = tasks[i].stackPointer;
			info[j].pickd = tasks[i].ticks;
			info[j].screen = tasks[i].output;

			j++;
		}
	}
	return j;
}



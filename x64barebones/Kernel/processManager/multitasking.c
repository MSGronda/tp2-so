#include <multitasking.h>

// ---- Constantes ----
#define TOTAL_TASKS 20
#define STACK_SIZE 4096

#define MAX_PRIORITY 5

#define NULL 0 // !!!! REMOVE !!!!

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
										/*   	 -------------		*/

#define STACK_POS(POS) (uint64_t *) (stackStart + STACK_SIZE - (POS))

// -----Informacion sobre cada task-----
typedef struct process_control_block{
		unsigned int pid;				// unique identifier. value is > 0

		uint64_t  stackPointer;			// value of rsp 
		uint64_t  stackSegment;  		// value of ss. This one is constant = 0
		void * stackStart;
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

/* =========== CODE =========== */

/* --- Init --- */

void idleTask(){
	while(1)
		_hlt();
}

char * idleArg[] = {"idle", NULL};
void enableMultiTasking(){

	add_task((uint64_t)&idleTask, 1, BACKGROUND, 1, IMMORTAL,idleArg);
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

int add_task(uint64_t entrypoint, uint8_t input, uint8_t output, uint8_t priority, uint8_t immortal, uint64_t arg0){
	if(currentDimTasks>=TOTAL_TASKS){		// no acepto mas tasks al estar lleno
		return ERROR_NO_SPACE_FOR_TASK;
	}
	currentDimTasks++;

	int pos;
	for(pos=0; tasks[pos].state!=DEAD_PROCESS ;pos++);											// encuentro posicion libre en el array de tasks

	uint8_t * stackStart = mm_malloc(STACK_SIZE);

	if(stackStart == NULL)
		return ERROR_NO_SPACE_FOR_TASK;


	// --- Parametros de funcion ---
	*(STACK_POS(RDI_POS)) = arg0;

	// --- Pongo todos los registros que no se usan en 0 ---
	for(int i=7 ; i<21 ; i++){
		if(i!=12)
			*(STACK_POS(i * 8)) = 0;
	}

	// --- "Stack frame" minimo para la funcion ---

	*(STACK_POS(IP_POS)) = entrypoint;							// puntero al proceso que se va a correr
	*(STACK_POS(CS_POS)) = CS_VALUE;				
	
	*(STACK_POS(FLAGS_POS)) = FLAG_VALUES;						// tenemos que poner el flag de interrupcion en 1 y otros obligatorios
	
	*(STACK_POS(SP_POS)) = (uint64_t) stackStart + STACK_SIZE - RET_POS;	// agarro el comienzo del stack
	*(STACK_POS(SS_POS)) = SS_VALUE;
	
	*(STACK_POS(RET_POS)) = (uint64_t) &removeCurrentTask;		// para el RET que vaya y se remueva automaticamente de los tasks

	// --- Datos de task ---
	tasks[pos].stackPointer = (uint64_t) stackStart + STACK_SIZE - STACK_POINT_OF_ENTRY;					// comienzo del stack
	tasks[pos].stackSegment = SS_VALUE;				// se mantiene constante
	tasks[pos].pid = newPidValue++;
	tasks[pos].state = ACTIVE_PROCESS;
	tasks[pos].priority = priority;
	tasks[pos].immortal = immortal;
	tasks[pos].stackStart = stackStart;
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
	mm_free(tasks[pos].stackStart);
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
	if(pos == -1)
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
	uint8_t currentTaskKilled = 0;
	for(int i=0; i< TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS &&  tasks[i].immortal != IMMORTAL ){		//TODO: que vuelva a ser solo los screen processes
			destroy_process(i);

			if(i == currentTask){
				currentTaskKilled = 1;
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
		return -1;

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
		return -1;

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

	int newPriority = tasks[pos].priority + delta;
	if(newPriority > MAX_PRIORITY)
		newPriority = MAX_PRIORITY;
	else if(newPriority < 1)
		newPriority = DEFAULT_PRIORITY;
	
	tasks[pos].priority = newPriority;

	return 1;
}





/* --- Scheduling --- */

// se fija si le queda tiempo, si le queda, decrementa esa cantidad y
uint8_t has_or_decrease_time(){
	if(currentRemainingTicks < tasks[currentTask].priority - 1){
		tasks[currentTask].ticks++;
		currentRemainingTicks++;
		return 1;
	}
	return 0;

}
/*	
	Pasa al proximo task que se tiene que ejecutar. 
	Parametros:  stackPointer: puntero al stack del task anterior  |  stackSegment: valor del stack segment del task anterior  
*/

uint64_t next_task(uint64_t stackPointer, uint64_t stackSegment){

	tasks[currentTask].stackPointer = stackPointer;			// updateo el current
	tasks[currentTask].stackSegment = stackSegment;
	
	char found=0;
	while( !found  ){			// busco el proximo stack
		currentTask = (currentTask +  1) % TOTAL_TASKS;

		switch(tasks[currentTask].state){

			case ACTIVE_PROCESS:
				found = 1;
				tasks[currentTask].ticks++;
				break;

			case WAITING_FOR_CHILD:
				if(children_finished(tasks[currentTask].pid)){
					
					remove_children(tasks[currentTask].pid);

					tasks[currentTask].state = ACTIVE_PROCESS;

					found = 1;
				}
				break;
		}
	}

	currentRemainingTicks = 0;		// reset del current task

	return tasks[currentTask].stackPointer;
}




/* --- Other --- */

void list_process(){
	int len;
	char buffer[100];

	writeDispatcher(tasks[currentTask].output, "Name     |  ID  |  State  |  Prty  |  Stack  |   RSP   |  Pickd  |  Screen\n", 75);
	writeDispatcher(tasks[currentTask].output, "---------------------------------------------------------------------------\n", 76);

	for(int i=0; i<TOTAL_TASKS -1 ; i++){
		if(tasks[i].state != DEAD_PROCESS){

			int len = 0;
			if(tasks[i].params !=NULL){
				len = str_len(tasks[i].params[0]);
				writeDispatcher(tasks[currentTask].output, tasks[i].params[0], len );
			}
			writeDispatcher(tasks[currentTask].output, "                  ", 12 - len);
			len = num_to_string(tasks[i].pid, buffer);
			writeDispatcher(tasks[currentTask].output, buffer, len);
			writeDispatcher(tasks[currentTask].output, "                  ", 5 - ((tasks[i].pid >= 10) ? 1 : 0));

			switch(tasks[i].state){
				case ACTIVE_PROCESS: 
					writeDispatcher(tasks[currentTask].output, "Active ", 7);
					break;
				case PAUSED_PROCESS:
					writeDispatcher(tasks[currentTask].output, "Paused ", 7);
					break;

				default:
					writeDispatcher(tasks[currentTask].output, "Blocked", 7);
					break;

			}
			writeDispatcher(tasks[currentTask].output, "                  ", 6);

			len = num_to_string(tasks[i].priority, buffer);
			writeDispatcher(tasks[currentTask].output, buffer, len);
			writeDispatcher(tasks[currentTask].output, "                  ", 4);


			len = num_to_string(tasks[i].stackStart, buffer);
			writeDispatcher(tasks[currentTask].output, buffer, len);
			writeDispatcher(tasks[currentTask].output, "                  ",3);

			len = num_to_string(tasks[i].stackPointer, buffer);
			writeDispatcher(tasks[currentTask].output, buffer, len);
			writeDispatcher(tasks[currentTask].output, "                  ",4);

			len = num_to_string(tasks[i].ticks, buffer);
			writeDispatcher(tasks[currentTask].output, buffer, len);
			writeDispatcher(tasks[currentTask].output, "                  ",8 - len);

			switch(tasks[i].output){
				case BACKGROUND:
					writeDispatcher(tasks[currentTask].output, "Background", 10);
					break;
				case STDOUT:
					writeDispatcher(tasks[currentTask].output, "Stdout", 6);
					break;
				case STDOUT_LEFT:
					writeDispatcher(tasks[currentTask].output, "Stdout left", 11);
					break;
				case STDOUT_RIGHT:
					writeDispatcher(tasks[currentTask].output, "Stdout right", 12);
					break;
				default:
					writeDispatcher(tasks[currentTask].output, "Pipe", 4);
					break;
			}
			writeDispatcher(tasks[currentTask].output, "\n", 1);
		}
	}
}


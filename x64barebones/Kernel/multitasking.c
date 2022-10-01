#include <multitasking.h>

// ---- Constantes ----
#define TOTAL_TASKS 4
#define STACK_SIZE 2000

#define NULL 0 // !!!! REMOVE !!!!

// ----- Estado de task -----
#define DEAD_PROCESS 0
#define ACTIVE_PROCESS 1 
#define PAUSED_PROCESS 2
#define WAITING_PROCESS 3

// ---- Screen ----
#define BACKGROUND_PROCESS 0

// ---- Valores default para el armado del stack ----
#define FLAG_VALUES 0x202
#define SS_VALUE 0
#define CS_VALUE 8

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

#define STACK_POS(POS) (uint64_t *) (stacks[pos] + STACK_SIZE - (POS))

// -----El stack que usa cada task-----
static uint8_t stack1[STACK_SIZE];
static uint8_t stack2[STACK_SIZE];
static uint8_t stack3[STACK_SIZE];
static uint8_t stack4[STACK_SIZE];

static uint8_t * stacks[TOTAL_TASKS] = {stack1, stack2, stack3, stack4};


// -----Informacion sobre cada task-----
typedef struct taskInfo{
		uint64_t  stackPointer;		// valor de rsp 
		uint64_t  stackSegment;  	// valor de ss
		uint8_t screen;				// en que pantalla va a imprimir
		uint8_t pid;				// valor unico identificador
		uint8_t state;				// si el proceso es uno activo o ya se elimino
		uint8_t priority;			// cuantos ticks puede tener por rafaga 
		uint8_t immortal;			// si se puede matar o no
}taskInfo;

// ------ Queue de tasks -------
static taskInfo tasks[TOTAL_TASKS];

static uint8_t newPidValue = 0;					// identificador para cada proceso
	
static unsigned int currentTask = 0;			// posicion en el array
static unsigned int currentRemainingTicks = 0;			// How many timer ticks are remaining for the current process.
static unsigned int currentDimTasks = NO_TASKS;

// Child Processes

#define MAX_WAIT_TASKS 20

#define NOT_TRACKING 0	// singals that space is empty and ready to use
#define RUNNING 1
#define FINISHED 2

typedef struct wait_info{
	uint8_t fatherPid;
	uint8_t childPid;
	uint8_t state;
}wait_info;

static wait_info wait_table[MAX_WAIT_TASKS] = {0};		// TODO: tira warning

/* =========== PROTOYPES =========== */

void idleTask();
void enableMultiTasking();
uint8_t getCurrentPid();
uint64_t getRSP();
uint64_t getSS();
uint8_t getCurrentScreen();
int findTask(unsigned int pid);
uint8_t screenAvailable(unsigned int screen);
int add_task(uint64_t entrypoint, uint8_t screen, uint8_t priority, uint8_t immortal, uint64_t arg0);
void pauseScreenProcess(unsigned int screen);
int pauseOrUnpauseProcess(unsigned int pid);
void kill_screen_processes();
void removeCurrentTask();
int removeTask(unsigned int pid);
uint8_t has_or_decrease_time();
void moveToNextTask(uint64_t stackPointer, uint64_t stackSegment);
uint8_t has_children(uint8_t pid);
void wait_for_children(uint64_t rsp, uint64_t ss);
void signal_process_finished(unsigned int pid);
void remove_children(uint8_t fatherPid);
void add_child(uint8_t fatherPid, uint8_t childPid);
unsigned int add_child_task(uint64_t entrypoint, int screen, uint64_t arg0);
uint8_t children_finished(uint8_t fatherPid);


/* =========== CODE =========== */

/* --- Init --- */

void idleTask(){
	while(1)
		_hlt();
}

void enableMultiTasking(){
	add_task((uint64_t)&idleTask, BACKGROUND_PROCESS, DEFAULT_PRIORITY, IMMORTAL,0);
	forceCurrentTask();
}


/* --- Getters --- */
uint8_t getCurrentPid(){
	return tasks[currentTask].pid;
}
uint64_t getRSP(){
	return tasks[currentTask].stackPointer;
}
uint64_t getSS(){
	return tasks[currentTask].stackSegment;
}
uint8_t getCurrentScreen(){
	return tasks[currentTask].screen;
}
// Encuentro el task usando el pid
int findTask(unsigned int pid){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].pid == pid && tasks[i].state != DEAD_PROCESS)
			return i;
	}	
	return NO_TASK_FOUND;			// no existe task con ese pid
}


/* --- Checkers --- */

uint8_t screenAvailable(unsigned int screen){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS && tasks[i].screen == screen){
			return 0;
		}
	}
	return 1;
}




/* --- Process Management --- */

int add_task(uint64_t entrypoint, uint8_t screen, uint8_t priority, uint8_t immortal, uint64_t arg0){

	if(currentDimTasks>=TOTAL_TASKS){		// no acepto mas tasks al estar lleno
		return ERROR_NO_SPACE_FOR_TASK;
	}
	if(!screenAvailable(screen)){
		return ERROR_SCREEN_NOT_AVAILABLE;
	}
	currentDimTasks++;

	int pos;
	for(pos=0; tasks[pos].state==ACTIVE_PROCESS;pos++);											// encuentro posicion libre en el array de tasks

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
	
	*(STACK_POS(SP_POS)) = (uint64_t) stacks[pos] + STACK_SIZE - RET_POS;	// agarro el comienzo del stack
	*(STACK_POS(SS_POS)) = SS_VALUE;
	
	*(STACK_POS(RET_POS)) = (uint64_t) &removeCurrentTask;		// para el RET que vaya y se remueva automaticamente de los tasks

	// --- Datos de task ---
	tasks[pos].stackPointer = (uint64_t) stacks[pos] + STACK_SIZE - STACK_POINT_OF_ENTRY;					// comienzo del stack
	tasks[pos].stackSegment = SS_VALUE;		
	tasks[pos].screen = screen;
	tasks[pos].pid = newPidValue++;
	tasks[pos].state = ACTIVE_PROCESS;
	tasks[pos].priority = priority;
	tasks[pos].immortal = immortal;

	return tasks[pos].pid;
}


void pauseScreenProcess(unsigned int screen){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != WAITING_PROCESS && tasks[i].state != DEAD_PROCESS && tasks[i].screen == screen){
			tasks[i].state = tasks[i].state==PAUSED_PROCESS ? ACTIVE_PROCESS : PAUSED_PROCESS; 	// pausado -> despausado  | despausado -> pausado
		}
	}
}

// pauso o despauso proceso con el pid
int pauseOrUnpauseProcess(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// se quiere pausar task que no existe
		return NO_TASK_FOUND;

	tasks[pos].state = tasks[pos].state==PAUSED_PROCESS ? ACTIVE_PROCESS : PAUSED_PROCESS; 	// pausado -> despausado  | despausado -> pausado
	return TASK_ALTERED;
}


void kill_screen_processes(){
	for(int i=0; i< TOTAL_TASKS; i++){
		if(tasks[i].state == ACTIVE_PROCESS && tasks[i].immortal != IMMORTAL && tasks[i].screen != BACKGROUND_PROCESS){
			tasks[i].state = DEAD_PROCESS;
			currentDimTasks--;

			signal_process_finished(tasks[i].pid);

			// TODO: quizas sigue corriendo por lo que queda del tick?
		}
	}
}

void removeCurrentTask(){
	tasks[currentTask].state = DEAD_PROCESS;
	currentDimTasks--;

	signal_process_finished(tasks[currentTask].pid);

	// There's no need to reset currentRemainingTicks, eventually moveToNextTask will do so

	forceNextTask(NULL, NULL);				
}

int removeTask(unsigned int pid){

	//TODO: si remuevo el actual entonces tengo que resetear el currentRemainingTicks

	int pos = findTask(pid);
	if(pos < 0)					// se quiere remover task que no existe
		return NO_TASK_FOUND;

	signal_process_finished(pid);

	tasks[pos].state = DEAD_PROCESS;
	currentDimTasks--;
	return TASK_ALTERED;
}




/* --- Scheduling --- */

// se fija si le queda tiempo, si le queda, decrementa esa cantidad y
uint8_t has_or_decrease_time(){
	if(currentRemainingTicks < tasks[currentTask].priority - 1){
		currentRemainingTicks++;
		return 1;
	}
	return 0;

}
/*	
	Pasa al proximo task que se tiene que ejecutar. 
	Parametros:  stackPointer: puntero al stack del task anterior  |  stackSegment: valor del stack segment del task anterior  
*/
void moveToNextTask(uint64_t stackPointer, uint64_t stackSegment){

	tasks[currentTask].stackPointer = stackPointer;			// updateo el current
	tasks[currentTask].stackSegment = stackSegment;
	
	char found=0;
	for(unsigned int i=currentTask; !found ; ){			// busco el proximo stack
		i = (i +  1) % TOTAL_TASKS;

		switch(tasks[i].state){

			case ACTIVE_PROCESS:
				currentTask = i;
				found = 1;
				break;

			case WAITING_PROCESS:
				if(children_finished(tasks[i].pid)){
					
					remove_children(tasks[i].pid);

					tasks[i].state = ACTIVE_PROCESS;

					currentTask = i;
					found = 1;
				}
				break;
		}
	}

	currentRemainingTicks = 0;		// reset del current task
}

/* --- Child processes --- */

// TODO: Por ahora lo dejo separado pero quizas hay que juntar con el resto de las funcionas

uint8_t has_children(uint8_t pid){
	for(int i=0; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].fatherPid == pid){
			return 1;
		}
	}
	return 0;
}


void wait_for_children(uint64_t rsp, uint64_t ss){
	if(!has_children(getCurrentPid())){
		return;
	}

	tasks[currentTask].state = WAITING_PROCESS;

	forceNextTask(rsp, ss); 		//	ya tiene en rdi y rsi los parametros para moveToNextTask
}


void signal_process_finished(unsigned int pid){

	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if( wait_table[i].state == RUNNING && wait_table[i].childPid == pid){
			wait_table[i].state = FINISHED;
			return;
		}
	}
}

void remove_children(uint8_t fatherPid){
	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].fatherPid == fatherPid){
			wait_table[i].fatherPid = 0;
			wait_table[i].childPid = 0;
			wait_table[i].state = NOT_TRACKING;
		}
	}
}

void add_child(uint8_t fatherPid, uint8_t childPid){
	for(int i=0 ; i<MAX_WAIT_TASKS; i++){
		if(wait_table[i].state == NOT_TRACKING){

			wait_table[i].fatherPid = fatherPid;
			wait_table[i].childPid = childPid;
			wait_table[i].state = RUNNING;
			return;
		}
	}
}

unsigned int add_child_task(uint64_t entrypoint, int screen, uint64_t arg0){
	uint8_t child_pid = add_task(entrypoint, screen, DEFAULT_PRIORITY, MORTAL , arg0);

	add_child(getCurrentPid(), child_pid);

	return child_pid;
}

// checks if ALL children that are being tracked have finished
uint8_t children_finished(uint8_t fatherPid){

	for(int i=0; i< MAX_WAIT_TASKS; i++){
		if(wait_table[i].state == RUNNING && wait_table[i].fatherPid == fatherPid){
			return 0;
		}	
	}

	return 1;
}




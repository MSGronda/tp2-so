#include <multitasking.h>

// ---- Constantes ----
#define TOTAL_TASKS 4
#define STACK_SIZE 2000

// ----- Estado de task -----
#define INACTIVE_PROCESS 0
#define ACTIVE_PROCESS 1 
#define PAUSED_PROCESS 2

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
		uint8_t state;			// si el proceso es uno activo o ya se elimino
}taskInfo;

// ------ Queue de tasks -------
static taskInfo tasks[TOTAL_TASKS];

static uint8_t currentPid;					// identificador para cada proceso
static uint8_t isEnabled = 0;				// denota si multitasking se habilito
	
static unsigned int currentTask;			// posicion en el array

static int dimTasks = NO_TASKS;

/* =========== CODIGO =========== */

/*
	Se habilita el multitasking e instantaneamente
	pasa al primer task en el queue.
*/
void enableMultiTasking(){
	isEnabled = 1;
	forceCurrentTask();
}

/*
	Se fija si se habilito el multitasking.
*/
uint8_t multitaskingEnabled(){
	return isEnabled;
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
		if(tasks[i].state == ACTIVE_PROCESS){
			currentTask = i;
			found = 1;
		}	
	}
	
}


/*
	Consigue el Stack Pointer del proceso 
	actual, es decir, el que se esta a punto
	de ejecutar.
*/
uint64_t getRSP(){
	return tasks[currentTask].stackPointer;
}



/*
	Consigue el Stack Segment del proceso 
	actual, es decir, el que se esta a punto
	de ejecutar.
*/
uint64_t getSS(){
	return tasks[currentTask].stackSegment;
}


/*	
	Consigue la pantalla a la cual el proceso
	actual escribe.
*/
uint8_t getCurrentScreen(){
	return tasks[currentTask].screen;
}


/*	
	Elimina el current task y pasa al proximo. 
*/
void removeCurrentTask(){
	tasks[currentTask].state = INACTIVE_PROCESS;
	dimTasks = dimTasks==1 ? NO_TASKS : dimTasks - 1;
	forceNextTask();				
}

// Encuentro el task usando el pid
int findTask(unsigned int pid){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].pid == pid && tasks[i].state != INACTIVE_PROCESS)
			return i;
	}	
	return NO_TASK_FOUND;			// no existe task con ese pid
}
/*	
	Elimina el task con ese pid y pasa al proximo. 
	Un task no se puede matar a si mismo.
*/
int removeTask(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// se quiere remover task que no existe
		return NO_TASK_FOUND;

	tasks[pos].state = INACTIVE_PROCESS;
	dimTasks = dimTasks==1 ? NO_TASKS : dimTasks - 1;
	return TASK_ALTERED;
}
// pauso o despauso proceso con el pid
int pauseOrUnpauseProcess(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// se quiere pausar task que no existe
		return NO_TASK_FOUND;

	tasks[pos].state = tasks[pos].state==PAUSED_PROCESS ? ACTIVE_PROCESS : PAUSED_PROCESS; 	// pausado -> despausado  | despausado -> pausado
	return TASK_ALTERED;
}

/*	
	Agrega una funcion al queue de tasks. 
	Parametros:  entrypoint: puntero a funcion  |  screen: en que pantalla va a imprimir
*/

int addTask(uint64_t entrypoint, int screen, uint64_t arg0){
	if(dimTasks>=TOTAL_TASKS){		// no acepto mas tasks al estar lleno
		return ERROR_NO_SPACE_FOR_TASK;
	}
	dimTasks = dimTasks == NO_TASKS ? 1 : dimTasks+1;

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
	tasks[pos].pid = currentPid++;
	tasks[pos].state = ACTIVE_PROCESS;

	return tasks[pos].pid;
}



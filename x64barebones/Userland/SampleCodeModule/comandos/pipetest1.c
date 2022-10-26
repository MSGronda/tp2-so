#include "../include/comandos.h"
#include "../include/syscalls.h"


#define STRING "Super long string!"

#define PROCESS_AMOUNT 5
#define PIPE_ID 555


void producer(){
	sys_write_pipe(PIPE_ID, "01234567899876543210", 20);
}


void consumer(){
	char buffer[50] = {0};
	sys_read_pipe(PIPE_ID, buffer, 20);

	puts(buffer);
}

void pipetest1(){
	int resp = sys_register_pipe(PIPE_ID);
	if(resp!=0){
		char buf[20];
		int len = num_to_string(resp,buf);
		puts(buf);

		puts("Error creating pipe");
		return;
	}

	sys_register_child_process(&consumer, 1,NORMAL_SCREEN, NULL);
	sys_register_child_process(&producer, 1,NORMAL_SCREEN, NULL);

	sys_wait_for_children();

    sys_destroy_pipe(PIPE_ID);
}
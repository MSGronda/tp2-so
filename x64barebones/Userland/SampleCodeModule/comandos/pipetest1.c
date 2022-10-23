#include "../include/comandos.h"
#include "../include/syscalls.h"


#define STRING "Super long string!"

#define PROCESS_AMOUNT 5
#define PIPE_ID 555


void child(){

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
    // for(int i=0; i<PROCESS_AMOUNT; i++){
    //     int error = sys_register_child_process(&child, BACKGROUND, NULL);
    //     if(error <= 0){
    //         puts("error creating children");
    //     }
    // }
    // sys_wait_for_children();

	uint64_t a = 123123123123;

	sys_write_pipe(PIPE_ID, &a,sizeof(uint64_t));

	uint64_t b = 456456456456;

	sys_read_pipe(PIPE_ID, &b,sizeof(uint64_t));

	if(a == b)
		puts("success");
	else
		puts("fail");

    sys_destroy_pipe(PIPE_ID);
}
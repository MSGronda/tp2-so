#include "../include/comandos.h"
#include "../include/syscalls.h"
#include "../include/stdio.h"

#define PIPE_ID 200

void in(){
	int inc = 0;
	while(1){
		char buff[10] = {0};
		read_line(buff, 1);

		buff[0] += inc;
		inc++;

		if(inc == 26)
			inc = 0;

		print(buff,1);
	}
}


void out(){
	while(1){
		print("a",1);
	}
}


void pipetest(){
	int resp = sys_register_pipe(PIPE_ID);
	if(resp!=0){
		char buf[20];
		int len = num_to_string(resp,buf);
		puts(buf);

		puts("Error creating pipe");
		return;
	}

	sys_register_child_process(&out, 1, PIPE_ID, NULL);
	sys_register_child_process(&in, PIPE_ID, 1, NULL);


	sys_wait_for_children();

    sys_destroy_pipe(PIPE_ID);

}
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"
#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/test_util.h"

static char * string = "This is a super long string and is supposed to test pipes. Write will write parts of the string to the pipe and read will read and check that its correct. All the while, we will be using busy waiting to make this process longer...";
#define STRING_LENGTH 230
#define PIPEID 542
#define AMOUNT 10

void read_pipe(){
	char buffer[20] = {0};

	for(int i=0; i<STRING_LENGTH; ){
		sys_read_pipe(PIPEID, buffer, AMOUNT);

		if(strncmp(buffer, string + i, AMOUNT)){
			puts("Error text doesn't match!");
		}

		i += AMOUNT;


	}
}


void write_pipe(){
	for(int i=0; i<STRING_LENGTH; ){
		sys_write_pipe(PIPEID, string + i, AMOUNT);
		i += AMOUNT;

		bussy_wait(50000000);
	}
}


void test_pipe(){
	sys_destroy_pipe(PIPEID);
	int resp = sys_register_pipe(PIPEID);

	if(resp != 0){
		puts("Error creating pipe!");
		return;
	}

	sys_register_child_process((uint64_t) &read_pipe, STDIN, NORMAL_SCREEN, NULL);
	sys_register_child_process((uint64_t)&write_pipe, STDIN, NORMAL_SCREEN, NULL);

	sys_wait_for_children();


	sys_destroy_pipe(PIPEID);
}
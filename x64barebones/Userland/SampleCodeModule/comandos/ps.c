// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"
#include "../include/stdlib.h"

#define ACTIVE_PROCESS 1
#define PAUSED_PROCESS 2

#define STDOUT 1
#define STDOUT_LEFT 3
#define STDOUT_RIGHT 5

void ps(){

	process_info * info = malloc(20 * sizeof(process_info));
	if(info == NULL) {
		puts("No more space");
		return;
	}

	uint64_t amount =  sys_process_info(info);


	int len;
	char buffer[30] = {0};

	print("Name     |  ID  |  State  |  Prty  |  Stack  |   RSP   |  Pickd  |  Screen\n", 75);
	print("---------------------------------------------------------------------------\n", 76);

	for(int i=0; i<amount; i++){

		// name 
		len = strlen(info[i].name);
		print(info[i].name, len );
		print("                  ", 12 - len);

		// pid
		len = num_to_string(info[i].id, buffer);
		print(buffer, len);
		print("                  ", 5 - ((info[i].id >= 10) ? 1 : 0));

		// state
		switch(info[i].state){
			case ACTIVE_PROCESS: 
				print("Active ", 7);
				break;
			case PAUSED_PROCESS:
				print( "Paused ", 7);
				break;

			default:
				print( "Blocked", 7);
				break;

		}
		print( "                  ", 6);

		len = num_to_string(info[i].priority, buffer);
		print(buffer, len);
		print("                  ", 4);


		len = num_to_string(info[i].stack, buffer);
		print(buffer, len);
		print("                  ",3);

		len = num_to_string(info[i].rsp, buffer);
		print(buffer, len);
		print("                  ",4);

		len = num_to_string(info[i].pickd, buffer);
		print(buffer, len);
		print("                  ",8 - len);

		switch(info[i].screen){
			case BACKGROUND:
				print( "Background", 10);
				break;
			case STDOUT:
				print( "Stdout", 6);
				break;
			case STDOUT_LEFT:
				print( "Stdout left", 11);
				break;
			case STDOUT_RIGHT:
				print( "Stdout right", 12);
				break;
			default:
				print( "Pipe", 4);
				break;
		}
		print( "\n", 1);
	}

	free(info);

}
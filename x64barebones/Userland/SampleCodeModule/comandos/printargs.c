// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"

void printargs(char ** args){
	for(int i=0; args[i] !=NULL; i++){
		puts(args[i]);
	}
}
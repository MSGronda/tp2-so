#include "../include/comandos.h"

void printargs(char ** args){
	for(int i=0; args[i] !=NULL; i++){
		puts(args[i]);
	}
}
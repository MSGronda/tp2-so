// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"


static unsigned int a = 0;


#define ADD 500
#define PROCESS_AMOUNT 2
#define SEM_ID 26984

void slowInc(unsigned int * a, int inc){
    int b;
    b = *a;
    b += inc;
    for(int i=0; i<30000; i++)
        ;
    *a = b;
}


void incTest(char ** argv){
    int inc = 1;
    for(int i=0; i<ADD; i++){

        if(argv[1][0] == 't')
            sys_wait_sem(SEM_ID);

        slowInc(&a,inc);

        if(argv[1][0] == 't')
            sys_signal_sem(SEM_ID);
    }
}

void semtest(uint8_t sem){
    if(sem){
        sys_destroy_sem(SEM_ID);
        int res = sys_register_sem(SEM_ID, 1);
        if(res != 0){
            puts("error creating semaphore");
            return;
        }    
    }
    a = 0;
    char * args[] = {"sem", NULL, NULL};

    if(sem)
        args[1] = "t";
    else
        args[1] = "f";

    for(int i=0; i<PROCESS_AMOUNT; i++){
        int error = sys_register_child_process((uint64_t) &incTest,STDIN, BACKGROUND, (uint64_t) args);
        if(error <= 0){
            puts("error creating children");
        }
    }

    sys_wait_for_children();

    if(sem){
        sys_destroy_sem(SEM_ID);
    }


    char buff[29];
    puts("");
    int len = num_to_string(a, buff);
    print(buff, len);
    print(" ?= ",4);
    len = num_to_string(ADD * PROCESS_AMOUNT, buff);
    print(buff, len);
    puts("\n");

}


void test_sem(){
    semtest(1);
}

void test_no_sem(){
    semtest(0);
}



#include "../include/comandos.h"
#include "../include/syscalls.h"


static unsigned int a = 0;
#define ADD 13000
#define PROCESS_AMOUNT 5

void slowInc(int * a, int inc){
    int b;
    b = *a;
    b += inc;
    for(int i=0; i<450; i++);
    *a = b;
}


void semtest1(){
    int inc = 1;
    for(int i=0; i<ADD; i++){
        sys_wait_sem(555);
        slowInc(&a,inc);
        sys_signal_sem(555);
    }
}



void semtest(){
    a = 0;
    sys_register_sem(555);
    for(int i=0; i<PROCESS_AMOUNT; i++){
        sys_register_child_process(&semtest1, NORMAL_SCREEN, NULL);
    }

    sys_wait_for_children();
    sys_destroy_sem(555);


    char buff[29];
    puts("");
    int len = num_to_string(a, buff);
    print(buff, len);
    print(" ?= ",4);
    len = num_to_string(ADD * PROCESS_AMOUNT, buff);
    print(buff, len);
    puts("\n");

    sys_print_sem();
}

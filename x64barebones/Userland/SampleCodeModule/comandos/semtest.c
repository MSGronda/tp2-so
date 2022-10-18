#include "../include/comandos.h"
#include "../include/syscalls.h"


static unsigned int a = 0;
static char b = 'a';

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
    print(&b,1);
    b+=1;
    int inc = 1;
    for(int i=0; i<ADD; i++){
        sys_wait_sem(555);
        slowInc(&a,inc);
        sys_signal_sem(555);
    }
}



void semtest(){
    a = 0;
    b = 'a';
    sys_register_sem(555);
    for(int i=0; i<PROCESS_AMOUNT; i++){
        sys_register_child_process(&semtest1, NORMAL_SCREEN, NULL);
    }

    sys_wait_for_children();

    char buff[29];
    puts("");
    int len = num_to_string(a, buff);
    print(buff, len);
    print(" ?= ",4);
    len = num_to_string(ADD * PROCESS_AMOUNT, buff);
    print(buff, len);
    puts("");

    sys_print_sem();
}

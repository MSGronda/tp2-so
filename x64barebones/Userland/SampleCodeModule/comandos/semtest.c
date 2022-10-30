#include "../include/comandos.h"
#include "../include/syscalls.h"


static unsigned int a = 0;
#define ADD 500
#define PROCESS_AMOUNT 2
#define SEM_ID 26984

void slowInc(int * a, int inc){
    int b;
    b = *a;
    b += inc;
    for(int i=0; i<30000; i++);
    *a = b;
}


void incTest(){
    int inc = 1;
    for(int i=0; i<ADD; i++){
        sys_wait_sem(SEM_ID);
        slowInc(&a,inc);
        sys_signal_sem(SEM_ID);
    }
}



void semtest(){
    int res = sys_register_sem(SEM_ID, 1);
    if(res != 0){
        puts("error creating semaphore");
        return;
    }
    a = 0;


    for(int i=0; i<PROCESS_AMOUNT; i++){
        int error = sys_register_child_process(&incTest,STDIN, BACKGROUND, NULL);
        if(error <= 0){
            puts("error creating children");
        }
    }

    sys_wait_for_children();
    sys_destroy_sem(SEM_ID);


    char buff[29];
    puts("");
    int len = num_to_string(a, buff);
    print(buff, len);
    print(" ?= ",4);
    len = num_to_string(ADD * PROCESS_AMOUNT, buff);
    print(buff, len);
    puts("\n");

}

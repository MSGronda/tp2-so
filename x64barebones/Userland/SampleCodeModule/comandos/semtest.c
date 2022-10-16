#include "../include/comandos.h"
#include "../include/syscalls.h"

void semtest1(){
    while(1){
        sys_wait_sem(555);
        for(int i=0;i<50000000;i++);
        puts("1");
        sys_signal_sem(555);
    }
}
void semtest2(){
    while(1){
        sys_wait_sem(555);
        for(int i=0;i<5000000;i++);
        puts("2");
        sys_signal_sem(555);
    }
}
void semtest3(){
    while(1){
        sys_wait_sem(555);
        for(int i=0;i<500000;i++);
        puts("3");
        sys_signal_sem(555);
    }
}
void semtest4(){
    while(1){
        sys_wait_sem(555);
        for(int i=0;i<500000;i++);
        puts("4");
        sys_signal_sem(555);
    }
}
void semtest(){
    sys_register_sem(555);
    sys_register_child_process(&semtest1, NORMAL_SCREEN, NULL);
    sys_register_child_process(&semtest2, NORMAL_SCREEN, NULL);
    sys_register_child_process(&semtest3, NORMAL_SCREEN, NULL);
    sys_register_child_process(&semtest4, NORMAL_SCREEN, NULL);
    sys_wait_for_children();
}

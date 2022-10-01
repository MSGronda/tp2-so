#include "../include/syscalls.h"

#define SYS_READ_FROM_SCREEN 0
#define SYS_WRITE_TO_SCREEN 1
#define SYS_CLEAR_SCREEN 2
#define SYS_REGISTER_PROCESS 3 
#define SYS_RTC 4
#define SYS_CONSUME_STDIN 7
#define SYS_KILL_PROCESS 8
#define SYS_PAUSE_PROCESS 9
#define SYS_INFOREG 10
#define SYS_PRINTMEM 11
#define SYS_REGISTER_CHILD_PROCESS 12
#define SYS_WAIT_FOR_CHILDREN 13
#define SYS_RENOUNCE_CPU 14
#define SYS_NICE 15

#define NULL 0

extern uint64_t syscaller(uint64_t syscallID, uint64_t param1, uint64_t param2, uint64_t param3);

unsigned int sys_write(const char * string, unsigned int length){
    return syscaller(SYS_WRITE_TO_SCREEN, (uint64_t) string, (uint64_t) length, NULL);        // feo arreglar
}   

unsigned int sys_read(char * buf, unsigned int length){
    return syscaller(SYS_READ_FROM_SCREEN, (uint64_t) buf, (uint64_t) length, NULL);        // feo arreglar
}

unsigned int sys_clear_screen(){
    return syscaller(SYS_CLEAR_SCREEN, NULL, NULL, NULL );        // feo arreglar
}

unsigned int sys_register_process(uint64_t entryPoint, int screen, uint64_t arg0){
    return syscaller(SYS_REGISTER_PROCESS, (uint64_t) entryPoint, (uint64_t) screen, arg0);        // feo arreglar
}

unsigned int sys_register_child_process(uint64_t entryPoint, int screen, uint64_t arg0){
    return syscaller(SYS_REGISTER_CHILD_PROCESS, (uint64_t) entryPoint, (uint64_t) screen, arg0);        // feo arreglar
}

unsigned int sys_wait_for_children(){
    return syscaller(SYS_WAIT_FOR_CHILDREN, NULL, NULL, NULL);
}

unsigned int sys_renounce_cpu(){
    return syscaller(SYS_RENOUNCE_CPU, NULL, NULL, NULL);
}

unsigned int sys_nice(uint8_t pid, int delta){
    return syscaller(SYS_NICE, pid, delta, NULL);
}



unsigned int sys_rtc(unsigned int  mode){
    return syscaller(SYS_RTC, (uint64_t)mode, NULL, NULL);        // feo arreglar
}
unsigned int sys_consume_stdin(char * buf, unsigned int count){
    return syscaller(SYS_CONSUME_STDIN, (uint64_t)buf, (uint64_t)count, NULL);
}
unsigned int sys_kill_process(unsigned int pid){
    return syscaller(SYS_KILL_PROCESS,(uint64_t) pid,NULL,NULL);
}
unsigned int sys_pause_process(unsigned int pid){
    return syscaller(SYS_PAUSE_PROCESS,(uint64_t) pid,NULL,NULL);
}
unsigned int sys_inforeg(uint64_t * buffer){
    return syscaller(SYS_INFOREG,(uint64_t) buffer,NULL,NULL);
}

unsigned int sys_printmem(uint64_t position, char * buffer){
    return syscaller(SYS_PRINTMEM, position, (uint64_t) buffer, NULL);
}
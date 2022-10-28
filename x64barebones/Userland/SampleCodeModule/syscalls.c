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
#define SYS_GET_PID 16
#define SYS_LIST_PROCESS 17
#define SYS_ALLOC 18
#define SYS_FREE 19
#define SYS_WAIT_SEM 20
#define SYS_REGISTER_SEM 21
#define SYS_SIGNAL_SEM 22
#define SYS_PRINT_SEM 23
#define SYS_DESTROY_SEM 24

#define SYS_WRITE_PIPE 25
#define SYS_REGISTER_PIPE 26
#define SYS_READ_PIPE 27
#define SYS_PRINT_PIPE 28
#define SYS_DESTROY_PIPE 29

#define NULL 0

extern uint64_t syscaller(uint64_t syscallID, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4);


uint64_t sys_print_pipe(){
    return syscaller(SYS_PRINT_PIPE, NULL, NULL, NULL , NULL );
}
uint64_t sys_destroy_pipe(unsigned int pipe_id){
    return syscaller(SYS_DESTROY_PIPE, (uint64_t) pipe_id, NULL, NULL , NULL );
}
uint64_t sys_read_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count){
    return syscaller(SYS_READ_PIPE, (uint64_t) pipe_id, (uint64_t) dest, (uint64_t) count , NULL );
}
uint64_t sys_write_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count){
    return syscaller(SYS_WRITE_PIPE, (uint64_t) pipe_id, (uint64_t) src, (uint64_t) count , NULL );
}
uint64_t sys_register_pipe(unsigned int pipe_id){
    return syscaller(SYS_REGISTER_PIPE, (uint64_t) pipe_id, NULL, NULL , NULL );    
}

uint64_t  sys_destroy_sem(unsigned int sem_id){
    return syscaller(SYS_DESTROY_SEM, (uint64_t) sem_id, NULL, NULL , NULL );
}

uint64_t  sys_signal_sem(unsigned int sem_id){
    return syscaller(SYS_SIGNAL_SEM, (uint64_t) sem_id, NULL, NULL , NULL );
}

uint64_t  sys_wait_sem(unsigned int sem_id){
    return syscaller(SYS_WAIT_SEM, (uint64_t) sem_id, NULL, NULL , NULL );
}

uint64_t  sys_register_sem(unsigned int sem_id, unsigned int value){
    return syscaller(SYS_REGISTER_SEM, (uint64_t) sem_id, (uint64_t) value, NULL , NULL );
}
uint64_t  sys_print_sem(){
    return syscaller(SYS_PRINT_SEM, NULL, NULL, NULL , NULL );
}



uint64_t sys_free(void * ptr){
    return syscaller(SYS_FREE, (uint64_t) ptr, NULL, NULL, NULL );
}
uint64_t sys_alloc(uint64_t len){
    return syscaller(SYS_ALLOC, (uint64_t)len, NULL, NULL, NULL );
}

uint64_t  sys_list_process(){
    return syscaller(SYS_LIST_PROCESS, NULL, NULL, NULL, NULL );
}


uint64_t  sys_write(const char * string, unsigned int length){
    return syscaller(SYS_WRITE_TO_SCREEN, (uint64_t) string, (uint64_t) length, NULL, NULL );        // feo arreglar
}   

uint64_t  sys_read(char * buf, unsigned int length){
    return syscaller(SYS_READ_FROM_SCREEN, (uint64_t) buf, (uint64_t) length, NULL, NULL );        // feo arreglar
}

uint64_t  sys_clear_screen(){
    return syscaller(SYS_CLEAR_SCREEN, NULL, NULL, NULL , NULL );        // feo arreglar
}

uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0){
    return syscaller(SYS_REGISTER_PROCESS, (uint64_t) entrypoint, (uint64_t) input, (uint64_t) output, arg0);        // feo arreglar
}

uint64_t  sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0){
    return syscaller(SYS_REGISTER_CHILD_PROCESS, (uint64_t) entryPoint, (uint64_t) input, (uint64_t) output, arg0);        // feo arreglar
}

uint64_t  sys_wait_for_children(){
    return syscaller(SYS_WAIT_FOR_CHILDREN, NULL, NULL, NULL, NULL );
}

uint64_t  sys_renounce_cpu(){
    return syscaller(SYS_RENOUNCE_CPU, NULL, NULL, NULL, NULL );
}

uint64_t  sys_nice(uint8_t pid, int delta){
    return syscaller(SYS_NICE, pid, delta, NULL, NULL );
}

uint64_t  sys_get_pid(){
    return syscaller(SYS_GET_PID, NULL, NULL, NULL, NULL );
}



uint64_t  sys_rtc(unsigned int  mode){
    return syscaller(SYS_RTC, (uint64_t)mode, NULL, NULL, NULL );        // feo arreglar
}
uint64_t  sys_consume_stdin(char * buf, unsigned int count){
    return syscaller(SYS_CONSUME_STDIN, (uint64_t)buf, (uint64_t)count, NULL, NULL );
}
uint64_t  sys_kill_process(unsigned int pid){
    return syscaller(SYS_KILL_PROCESS,(uint64_t) pid,NULL,NULL, NULL );
}
uint64_t  sys_pause_process(unsigned int pid){
    return syscaller(SYS_PAUSE_PROCESS,(uint64_t) pid,NULL,NULL, NULL );
}
uint64_t  sys_inforeg(uint64_t * buffer){
    return syscaller(SYS_INFOREG,(uint64_t) buffer,NULL,NULL, NULL );
}

uint64_t  sys_printmem(uint64_t position, char * buffer){
    return syscaller(SYS_PRINTMEM, position, (uint64_t) buffer, NULL, NULL );
}
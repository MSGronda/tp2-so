#include "../include/syscalls.h"
#include "../include/stdio.h"

#define MAX_PHYLOS 30
#define MIN_PHYLOS 5
#define LEFT    (i + currentCount - 1) % currentCount
#define RIGHT   (i + 1) % currentCount
#define THINKING    0
#define HUNGRY      1
#define EATING      2

#define TRUE 1
#define FALSE (!TRUE)

#define MUTEX 777
#define PRINT_MUTEX 888

typedef int sem_t;
int end = FALSE;

int state[MAX_PHYLOS] = { 0 };
sem_t s[MAX_PHYLOS] = { 0 };
int currentCount = 0;

void philosopher(char ** num);
void takeForks(int i);
void addPhylo();
void removePhylo();
void putForks(int i);
void test(int i);
void eat();
void think();

void phylo() {
    end = FALSE;
    currentCount = 0;
    sys_destroy_sem(MUTEX);
    sys_destroy_sem(PRINT_MUTEX);
    sys_register_sem(MUTEX, 1);
    sys_register_sem(PRINT_MUTEX, 1);

    for(int i = 0 ; i < MIN_PHYLOS; i++){
        addPhylo();
    }

    char buf[1];
    while(!end){
        sys_read(buf, 1);
        switch(buf[0]){
            case 'a':
                addPhylo();
                for(int i = 0 ; i < 5000000 ; i++);
                break;
            case 'r':
                removePhylo();
                break;
            case 'q':
                end = TRUE;
                break;
        }
    }

    sys_wait_for_children();

    if(MUTEX)
        sys_destroy_sem(MUTEX);
}

void addPhylo(){
    sys_wait_sem(MUTEX);
    sys_wait_sem(PRINT_MUTEX);
    if(currentCount == MAX_PHYLOS){
        puts("MAX PHYLOS REACHED");
    } else{
        state[currentCount] = THINKING;
        s[currentCount] = sys_register_sem_available(0);

        char string[12] = { "philosopher" };
        char ** philos = { 0 };

        char ** args = (char **) sys_alloc(3 * sizeof(char *));
        char * buf = (char *) sys_alloc(8);
        num_to_string(currentCount, buf);

        args[0] = strncpy(args[0], string, 12);
        args[1] = buf;
        // args = { "philosopher", i, NULL }
        philos = args;

        if(sys_register_child_process(&philosopher, STDIN, NORMAL_SCREEN, philos) <= 0) {
            puts("error creating philosopher. aborting");
            return;
        }
        if(currentCount > MIN_PHYLOS)
            puts("ADDED PHYLO");
        currentCount++;
    }
    sys_signal_sem(PRINT_MUTEX);
    sys_signal_sem(MUTEX);
}

void removePhylo(){
    sys_wait_sem(MUTEX);
    sys_wait_sem(PRINT_MUTEX);
    if(currentCount == MIN_PHYLOS){
        puts("MIN PHYLOS REACHED");
    } else{
        currentCount--;
        puts("REMOVED PHYLO");
    }
    sys_signal_sem(PRINT_MUTEX);
    sys_signal_sem(MUTEX);
}

void philosopher(char ** num) {
    int i = atoi(num[1]);
    while(!end) {
        think();
        takeForks(i);
        eat();
        putForks(i);
    }
}


void takeForks(int i) {
    sys_wait_sem(MUTEX);
    state[i] = HUNGRY;
    test(i);
    sys_signal_sem(MUTEX);
    sys_wait_sem(s[i]);
}


void putForks(int i) {
    sys_wait_sem(MUTEX);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sys_signal_sem(MUTEX);
}


void test(int i) {
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        sys_signal_sem(s[i]);
    }
}

void eat() {
    for(int i = 0; i < 5000000; i++);
    sys_wait_sem(PRINT_MUTEX);
    for(int i = 0; i < currentCount; i++) {
        print(state[i] == EATING? "E " : ". ", 2);
    }
    puts("");
    sys_signal_sem(PRINT_MUTEX);
}

void think() {
    for(int i = 0; i < 5000000; i++);
}

#include "../include/syscalls.h"
#include "../include/stdio.h"

#define N 5
#define LEFT    (i + N - 1) % N
#define RIGHT   (i + 1) % N
#define THINKING    0
#define HUNGRY      1
#define EATING      2

#define TRUE 1
#define FALSE (!TRUE)

#define MUTEX 777
#define EAT_MUTEX 888

typedef int sem_t;

int state[N] = { 0 };
sem_t s[N] = { 0 };

void philosopher(int i);
void takeForks(int i);
void putForks(int i);
void test(int i);
void eat();
void think();

void phylo() {
    sys_register_sem(MUTEX, 1);
    sys_register_sem(EAT_MUTEX, 1);
    for(int i = 0; i < N; i++) {
        state[i] = THINKING;
        s[i] = sys_register_sem_available(0);
    }

    for(int j = 0; j < N; j++) {
        if(sys_register_child_process(&philosopher, STDIN, NORMAL_SCREEN, j) <= 0) {
            puts("error creating philosopher. aborting");
            return;
        }
    }

    sys_wait_for_children();

    if(MUTEX)
        sys_destroy_sem(MUTEX);
}


void philosopher(int i) {
    while(TRUE) {
        think();
        takeForks(i);
        sys_wait_sem(EAT_MUTEX);
        eat();
        sys_signal_sem(EAT_MUTEX);
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

    for(int i = 0; i < N; i++) {
        print(state[i] == EATING? "E " : ". ", 2);
    }

    puts("");
}

void think() {
    for(int i = 0; i < 5000000; i++);
}

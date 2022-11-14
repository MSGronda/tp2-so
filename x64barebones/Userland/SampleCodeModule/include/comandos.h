#ifndef _COMANDOS_H
#define _COMANDOS_H

#include <stdint.h>
#include "stdlib.h"
#include "stdio.h"

#define BUFF_SIZE 20
#define BUFFER_LENGTH 150

void test_pipe();
void test_prio();
void test_processes(char ** argv);
void test_no_sem();
void test_sem();
void test_mm();

void pause(char ** args);
void kill(char ** args);
void printargs(char ** args);

void ps();
void mmstatus();
void print_blocked_processes(unsigned int * blocked_pids, unsigned int amount);
void pipe();
void sem();

void wc();
void cat();

void killTest();

/**
 * @brief   Filters vowels passed as input
*/
void filter();

/**
 * @brief   Prints its pid with a greeting periodically
*/
void loop();

/**
 * @brief   Runs the philosophers problem
*/
void phylo();

/**
 * @brief   Adds 1 priority to a process
*/
void nice(char ** args);

/**
 * @brief   Prints 32bytes of memory from a starting position
*/
void printmem(char ** args);

/**
 * @brief   Prints prime values infinitely
*/
void primos();

/**
 * @brief   Prints the fibonacci sequence infinitely
*/
void fibonacci();

/**
 *  @brief  Explains all commands and kb shortcuts
 */
void help();

/**
 * @brief   Prints current RTC
*/
void time();

/**
 * @brief Prints register values when a snapshot was taken
*/
void inforeg();

#endif


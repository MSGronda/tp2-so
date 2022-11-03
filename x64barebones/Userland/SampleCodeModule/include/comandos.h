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

/*
 * << filter >>
 * ----------------------------------------------------------------------
 * Description: filters vowels passed as input
 * ----------------------------------------------------------------------
*/
void filter();


/*
 * << loop >>
 * ----------------------------------------------------------------------
 * Description: prints its pid with a greeting periodically
 * ----------------------------------------------------------------------
*/
void loop();

/*
 * << loop >>
 * ----------------------------------------------------------------------
 * Description: runs the philosopher's problem
 * ----------------------------------------------------------------------
*/
void phylo();

/*
 * << nice >>
 * ----------------------------------------------------------------------
 * Description: adds 1 priority to a process
 * ----------------------------------------------------------------------
*/
void nice(char ** args);


/*
 * << printmem >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints 32bytes of memory starting from [position] 
 * ----------------------------------------------------------------------
 * Recibe:
 *      (uint64_t) starting position
 * Devuelve: -- 
 */
void printmem(char ** args);

/*
 * << primos >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints prime values infinitely
 */
void primos();

/*
 * << fibonacci >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints the fibonacci sequence
 */
void fibonacci();

/*
 * << help >>
 * ----------------------------------------------------------------------
 * Descripcion: Explains all commands and kb shortcuts
 */
void help();

/*
 * << time >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints current RTC
 */
void time();

/*
 * << inforeg >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints register values when a snapshot was taken
 */
void inforeg();

#endif


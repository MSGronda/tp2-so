#ifndef _COMANDOS_H
#define _COMANDOS_H

#include <stdint.h>
#include "stdlib.h"
#include "stdio.h"

#define BUFF_SIZE 20
#define BUFFER_LENGTH 150

void nice(char ** args);
void semtest();
void pause(char ** args);
void kill(char ** args);
void printargs(char ** args);
void ps();
uint64_t test_mm(uint64_t argc, char *argv[]);

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


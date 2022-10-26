#ifndef IO_H_
#define IO_H_

#include <stdint.h>
/*
 * << read_stdin >>
 * ----------------------------------------------------------------------
 * Descripcion: Writes to corresponding screen
 * ----------------------------------------------------------------------
 * Recibe: 
*       [fd] = screen
 *      [buf] = string to be leave answer
 *      [count] = number of letters to be written
 * Devuelve: 
 *      (uint) bytes read
 */
unsigned int read_stdin(unsigned int fd, char * buf, unsigned int count);


/*
 * << readDispatcher >>
 * ----------------------------------------------------------------------
 * Descripcion: Decides how to proceed depending on screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = screen
 *      [buf] = string to be leave answer
 *      [count] = number of letters to be read
 * Devuelve: 
 *      (uint) bytes read
 */
unsigned int readDispatcher(unsigned int fd, char * buf, unsigned int count);

#endif
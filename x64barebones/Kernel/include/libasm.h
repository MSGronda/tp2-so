#ifndef LIB_ASM_H
#define LIB_ASM_H

#include <stdint.h>

int _xadd(int * lock, int value);

int _xchg(int * lock, int value);

/*
 * << readKeyboard >>
 * ----------------------------------------------------------------------
 * Descripcion: Reads input from keyboard
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: 
 *      (char) letter pressed     
 */
char readKeyboard();

/*
 * << registerDump >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints the value of every register
 * ----------------------------------------------------------------------
 * Recibe: 
 *      buffer: pos to write
 * Devuelve:  ---
 */
void registerDump(uint64_t * buffer);

/*
 * << getRTC >>
 * ----------------------------------------------------------------------
 * Descripcion: Acceses RTC 
 * ----------------------------------------------------------------------
 * Recibe: 
 *      option  -> 0x00 seconds
 *              -> 0x02 minutes
 *              -> 0x04 hours
 *              -> 0x06 day of week
 *              -> 0x07 day of month
 *              -> 0x08 month
 *              -> 0x09 year
 * Devuelve: 
 *      (int) *read above*
 */
int getRTC(uint8_t option);

#endif

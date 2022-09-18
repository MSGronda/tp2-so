#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

/*
 * << hex_to_string >>
 * ----------------------------------------------------------------------
 * Descripcion: Converts hexadecimal value to string
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (uint64_t) num : hex num to convert
 *      (char *) buf : buffer to output value
 *      (int) fixedLength : size of register (eg. 0h => 0000 0000d en 4 bytes)
 * Devuelve: 
 *      number of half_bytes written (eg 4bytes = 8 half_bytes)
 */
int hex_to_string(uint64_t num, char * buffer, int fixedLength);

/*
 * << str_len >>
 * ----------------------------------------------------------------------
 * Descripcion: Gets the length of a string
 * ----------------------------------------------------------------------
 * Recibe:
 *      (char *) string
 * Devuelve: 
 *      length of given string (excluding \0)
 */
int str_len(const char * string);


void printRegisters(int screen, uint64_t * registerDumpPos);

#endif

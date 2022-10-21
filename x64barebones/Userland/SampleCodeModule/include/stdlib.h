#ifndef _STDLIB_H
#define _STDLIB_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include "syscalls.h"
/* --- CONSTANTS  --- */
#define NULL 0
void * malloc(uint64_t size);
void free(void * ptr);
long long atosi(const char * string);

/*
 * << num_to_string >>
 * ----------------------------------------------------------------------
 * Descripcion: Converts num to string
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (uint64_t) number to convert
 *      (char*) buffer to leave answer
 * Devuelve: 
 *      (int) bytes written
 */
int num_to_string(uint64_t num, char * buffer);

/*
 * << strcmp >>
 * ----------------------------------------------------------------------
 * Descripcion: Compares two strings
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) s1, s2
 * Devuelve: 
 *      0  <=>  s1 == s2
 *      <0 <=>  s1 < s2
 *      >0 <=>  s1 > s2
 */
int strcmp(const char * s1, const char * s2);

/*
 * << strlen >>
 * ----------------------------------------------------------------------
 * Descripcion: Calculates length of null terminated string
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) null terminated string
 * Devuelve: 
 *      (int) length of string
 */
int strlen(const char * string);

/*
 * << atoi >>
 * ----------------------------------------------------------------------
 * Descripcion: Converts string to int number
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) string
 * Devuelve: 
 *      (int) number
 */
uint64_t atoi(const char * string);

/*
 * << removeEnter >>
 * ----------------------------------------------------------------------
 * Descripcion: Removes enter
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) string to remove enter from
 * Devuelve: --
 */
void removeEnter(char * string);

/*
 * << strncpy >>
 * ----------------------------------------------------------------------
 * Descripcion: Copies up to [n] bytes from [src] into [dest]
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) destination string
 *      (char*) source string
 *      (uint) max characters to copy
 * Devuelve: 
 *      (char*) new string
 */
int strncpy(char * dest, const char * src, unsigned int n);

/*
 * << isNum >>
 * ----------------------------------------------------------------------
 * Descripcion: Checks if a given string is a number
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) string to analyze
 * Devuelve: 
 *      1 <=> true
 *      0 <=> false
 */
uint8_t isNum(const char * string);

int hex_to_string(uint64_t num, char * buffer, int fixedLength);
int strContainsChar(char * string, char c);

#endif

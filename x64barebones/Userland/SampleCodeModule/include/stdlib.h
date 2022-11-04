#ifndef _STDLIB_H
#define _STDLIB_H

#include <stdint.h>
#include "syscalls.h"

#define NULL 0

void * malloc(uint64_t size);

void free(void * ptr);

int strncmp(const char * s1, const char * s2, int n);

/**
 * @return  If 0, then s1 == s2
 *          If <0, then s1 < s2
 *          If >0, then s1 > s2
*/
int strcmp(const char * s1, const char * s2);

/**
 * @param   string NULL terminated string
*/
int strlen(const char * string);

/**
 * @brief   Copies up to n bytes from src into dest
*/
int strncpy(char * dest, const char * src, unsigned int n);

uint8_t isNum(const char * string);

int strContainsChar(char * string, char c);

/**
 * @brief   Converts string to number
*/
uint64_t atoi(const char * string);

/**
 * @brief   Converts string to signed integer
*/
long long atosi(const char * string);

int num_to_string(uint64_t num, char * buffer);

int hex_to_string(uint64_t num, char * buffer, int fixedLength);

void removeEnter(char * string);


#endif

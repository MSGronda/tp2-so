#ifndef LIB_H
#define LIB_H

#include <stdint.h>
/*--------- MACROS ----------*/
#define INCREASE_MOD(x,total)   (x) = ((x) + 1) % total;
#define DECREASE_MOD(x, total)  x--;\
                if((x)<0)\
                        x=((total) + (x)) % (total);\
                else\
                    x = (x) % (total);


/*--------- FUNCTIONS ----------*/

int num_to_string(uint64_t num, char * buffer);
void reverseString(char * string, int length);
int str_len(const char * string);

void printRegisters(int screen, uint64_t * registerDumpPos);
void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

/**
 * @param       num Hexadecimal value to convert 
 * @param       buffer Buffer to leave answer
 * @param       fixedLength Size of register (0h => 0000 0000d => 4 bytes)
 * 
 * @return      Number of bytes written * 2
*/
int hex_to_string(uint64_t num, char * buffer, int fixedLength);

#endif

#ifndef LIB_ASM_H
#define LIB_ASM_H

#include <stdint.h>

int _xadd(unsigned int * lock, int value);

int _xchg(unsigned int * lock, int value);

/**
 * @return  Letter pressed
*/
char readKeyboard();

/**
 * @brief   Prints the value of all registers
 * 
 * @param   buffer Buffer to leave answer
*/
void registerDump(uint64_t * buffer);

/**
 * @brief   Acceses RTC
 * 
 * @param   option  -> 0x00 seconds
 *                  -> 0x02 minutes
 *                  -> 0x04 hours
 *                  -> 0x06 day of week
 *                  -> 0x07 day of month
 *                  -> 0x08 month
 *                  -> 0x09 year
 *  
 * @return  What was requested in option
*/
int getRTC(uint8_t option);

#endif

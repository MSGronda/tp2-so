#include "../include/comandos.h"
#include "../include/syscalls.h"

#define RTC_TIME 1
#define RTC_DAY 2


void formatString(char * string, char character)
{
    char aux[9];
    int length = strlen(string);
    int i = 0;
    
    if(length < 6)
        aux[0] = '0';
    else
        aux[0] = string[i++];

    aux[1] = string[i++];
    aux[2] = character;
    aux[3] = string[i++];
    aux[4] = string[i++];
    aux[5] = character;
    aux[6] = string[i++];
    aux[7] = string[i];
    aux[8] = '\0';
    strncpy(string, aux, 9);
}


void getTime(char * buffer)
{
    unsigned int num = sys_rtc(RTC_TIME);
    num_to_string((uint64_t) num, buffer);
    formatString(buffer, ':');
}


void getDate(char * buffer)
{
    unsigned int num = sys_rtc(RTC_DAY);
    num_to_string((uint64_t) num, buffer);
    formatString(buffer, '/');
}


void time()
{
    char buffer[9];
    print("DATE: ",6);
    getDate(buffer);
    puts(buffer);
    print("TIME: ",6);
    getTime(buffer);
    puts(buffer);
}
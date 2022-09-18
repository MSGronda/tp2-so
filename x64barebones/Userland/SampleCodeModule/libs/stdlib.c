#include "../include/stdlib.h"


void reverseString(char * string, int length)
{
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}


int num_to_string(uint64_t num, char * buffer)
{
    if(num==0) {
        buffer[0] = '0';
        buffer[1] = 0;
        return 2;
    }
    int i = 0;
    while(num > 0) {
        buffer[i++] = num%10 + '0';
        num /= 10;
    }
    reverseString(buffer, i);
    buffer[i] = 0;

    return i;
}

int hex_to_string(uint64_t num, char * buffer, int fixedLength)
{
    int i = 0;

    for(int aux ; num > 0 ; i++, num/=16){
        aux = num % 16;
        if(aux >=0 && aux < 10)                     // convierto a hex
            buffer[i] = aux + '0';
        else
            buffer[i] = aux - 10 + 'A';

    }
    while(i<fixedLength) {                   // le agrego 0 por deltante para llegar a la longitud deseada
        buffer[i++] = '0';
    }
    reverseString(buffer,i);
    buffer[i] = 0;

    return i;
}



// 0 si son ==
// s1 < s2 ==> <0
// s1 > s2 ==> >0
int strcmp(const char * s1, const char * s2)
{
        while(*s1 && (*s1 == *s2)){
            s1++; s2++;
        }
                

        return *s1 - *s2;
}


int strlen(const char * string){
    int i = 0;
    while(string[i])
        i++;

    return i;
}


/* Converts string to int */
uint64_t atoi(const char * string) 
{
    uint64_t result = 0;

    for(int i = 0 ; string[i] ; i++)
        result = result*10 + string[i] - '0';

    return result;
}


char * strncpy(char * dest, const char * src, unsigned int n)
{
        if(dest == NULL)
                return NULL;

        char * out = dest;
        while(*src && n--) {
                *dest = *src;
                dest++; src++;
        }
        *dest = '\0';

        return out;
}
int strContainsChar(char * string, char c){                    // #### REMOVE? #####
    int i;
    for(i=0; string[i]!=0; i++){
        if(string[i]==c){
            return i;
        }
    }
    return -1;
}


void removeEnter(char * string)          // #### REMOVE #####
{                   
    int i; 
    int removed = 0;
    for(i = 0 ; i < strlen(string) && !removed; i++) {
        if(string[i] == '\n') {
            string[i] = '\0';
            removed = 1;
        }
    }
}


uint8_t isNum(const char * string)
{
    for(int i=0; string[i]!=0; i++) {
        if(string[i]>'9' || string[i]<'0') {
            return 0;
        }
    }
    return 1;
}


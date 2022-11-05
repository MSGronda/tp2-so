// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"


// !!! Es ineficiente aproposito, asi no llena la pantalla demasiado rapido !!!
char isPrime(uint64_t num)
{
    for(int i=2; i<num ;i++){
        if(num % i == 0) {
            return 0;
        }
    }

    return 1;
}


void primos() 
{
    char buffer[30];
    uint64_t current = 3;
    int length;

    print("2",1);           // caso especial
    putchar('\n');

    while(1) {
        if(isPrime(current)) {
            length = num_to_string(current,buffer);
            print(buffer,length);
            putchar('\n');
        }
        current++;
    }
}

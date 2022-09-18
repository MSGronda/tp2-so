#include "../include/comandos.h"


#define FIBO_MAX 999999999999999999

void fibonacci()
{
    char buffer[30];
    uint64_t prev1=0, prev2=1, current;
    int length;

    print("0",1);               // casos especiales
    putchar('\n');

    print("1",1);
    putchar('\n');

    while(1) {
        current = prev1 + prev2;
        length = num_to_string(current,buffer);
        print(buffer,length);
        putchar('\n');

        prev1 = prev2;
        prev2 = current;

        if(current >= FIBO_MAX) {            // uint64_t entra en overflow despues de este numero
            prev1 = 0;
            prev2 = 1;
        }
    }
}
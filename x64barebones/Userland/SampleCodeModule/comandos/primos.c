// This is a personal academic project. Dear PVS-Studio, please check it.// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "../include/comandos.h"
#include "../include/syscalls.h"

#define RTC_TIME 1

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
    uint64_t current = 3, count=0;
    int length;

    print("Calculating...\n",15);

    uint64_t init = sys_rtc(RTC_TIME);

    while(current < 100000) {
        if(isPrime(current)) {
            //length = num_to_string(current,buffer);
            //print(buffer,length);
            //putchar('\n');

            count++;
        }

        current++;
    }

    uint64_t end = sys_rtc(RTC_TIME);

    length = num_to_string(count, buffer);
    print("Primes found: ",14);
    print(buffer,length);
    putchar('\n');

    uint64_t init_seconds = (init / 10000) * 3600 + ((init / 100) % 100) * 60 + (init % 100);
    uint64_t end_seconds = (end / 10000) * 3600 + ((end / 100) % 100) * 60 + (end % 100);
    length = num_to_string(end_seconds - init_seconds, buffer);

    print("Time elapsed: ", 14);
    print(buffer, length);
    print(" seconds\n",9);

}
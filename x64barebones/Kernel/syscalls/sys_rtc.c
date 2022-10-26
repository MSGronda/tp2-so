#include <rtc.h>
#include <syscalls.h>

/* constants */
#define HOUR 1
#define DATE 2

uint64_t sys_rtc(unsigned int option) 
{
        int hour, min, sec;
        int day, month, year;

        switch(option) {
                // Me piden horario
                // Devuelve HHMMSS
                case HOUR:
                        hour = getHours();
                        min = getMin();
                        sec = getSec();
                        return (hour - 3) * 10000 + min * 100 + sec;

                // Me piden fecha
                // Devuelve DDMMYY
                case DATE:
                        day = getDay();
                        month = getMonth();
                        year = getYear();
                        return day * 10000 + month * 100 + year;
        }

        return 0;
}



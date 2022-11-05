// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <rtc.h>

int getHours() {
        int hours = getRTC(F_HOURS);     
        return ((hours & 0x0F) + (((hours & 0x70) / 16) * 10)) | (hours & 0x80);
}


int getMin() {
        int min = getRTC(F_MIN);
        return (min & 0x0F) + ((min / 16) * 10);
}


int getSec() {
        int sec = getRTC(F_SEC);
        return (sec & 0x0F) + ((sec / 16) * 10);
}


int getDay() {
        int day = getRTC(F_DAY);             // day
        return (day & 0x0F) + ((day / 16) * 10);
}


int getMonth() {
        int month = getRTC(F_MONTH);       // month
        return (month & 0x0F) + ((month / 16) * 10);
}


int getYear() {
        int year = getRTC(F_YEAR);        // year
        return (year & 0x0F) + ((year / 16) * 10);
}
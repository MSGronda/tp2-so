#ifndef _RTC_H_
#define _RTC_H_

#include <libasm.h>

extern int getRTC(uint8_t field);


/* fields */
#define F_SEC   0x00
#define F_MIN   0x02
#define F_HOURS 0x04

#define F_DAY   0x07
#define F_MONTH 0x08
#define F_YEAR  0x09

int getHours();
int getMin();
int getSec();
int getDay();
int getMonth();
int getYear();

#endif
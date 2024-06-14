#ifndef GREGORIAN_DATE_H
#define GREGORIAN_DATE_H

typedef struct GregorianDate
{
    unsigned char day : 5;   // 2^5 = 32 enough to store 31 days
    unsigned char month : 4; // 2^4 = 16 enough to store 12 months
    long long year;
} gregorian_date;

typedef struct RepublicanDate
{
    unsigned char day : 5;    // 2^5 = 32 enough to store 30 days
    unsigned char decade : 2; // 2^2 = 4 enough to store 3 decades
    unsigned char month : 4;  // 2^4 = 16 enough to store 12 months
    unsigned char season : 3; // 2^3 = 8 enough to store 4 seasons
    long long year;
    unsigned char epagomenal : 3; // 2^3 = 8 enough to store 6 days
} republican_date;

typedef union Date
{
    struct GregorianDate gregorian;
    struct RepublicanDate republican;
} date;

char *english_months(unsigned char month);
char *english_day_extentions(unsigned char day);

#endif
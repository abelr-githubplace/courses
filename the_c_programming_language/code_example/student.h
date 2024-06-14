#ifndef STUDENT_H
#define STUDENT_H

typedef enum
{
    SUP = 1,
    SPE,
    ING1,
    ING2,
    ING3,
} year_batch;

typedef struct Student
{
    char *name; // name of the student
    char age;   // their age
    short year; // the year they are enroled in
} student;

char *batch(short year);

#endif
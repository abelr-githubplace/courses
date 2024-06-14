#include "student.h"

char *batch(short year) {
    switch (year)
    {
    case SUP:
        return "SUP";
    case SPE:
        return "SPE";
    case ING1:
        return "ING1";
    case ING2:
        return "ING2";
    case ING3:
        return "ING3";
    default:
        return "";
    }
}
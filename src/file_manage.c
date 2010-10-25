#include "header.h"

FILE * rfop(char ** argv)
{
    FILE * rfp;
    char ms[32];

    if((rfp = fopen((const char *)argv[1], "r")) == NULL) {
        sprintf(ms, "Wrong Input-file:\"%s\"", argv[1]);
        oem("mif", ms, 0);
    }

    return rfp;
}

#include "header.h"

FILE * rfop(char * argv, char bfn[32])
{
    FILE * rfp;
    char ms[64];
    char fn[32]; /* Function Name */

    if((rfp = fopen((const char *)argv, "r")) == NULL) {
        sprintf(ms, "Wrong Input-file:\"%s\"", argv);
        sprintf(fn, "%s()-->rfop", bfn);
        oem(fn, ms, 0);
    }

    return rfp;
}

FILE * wfop(char * argv, char bfn[32])
{
    FILE * wfp;
    char ms[64];
    char fn[32]; /* Function Name */

    if((wfp = fopen((const char *)argv, "a")) == NULL) {
        sprintf(ms, "Wrong Input-file:\"%s\"", argv);
        sprintf(fn, "%s()-->rfop", bfn);
        oem(fn, ms, 0);
    }

    return wfp;
}

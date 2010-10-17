#include "header.h"

FILE * rfop(char ** argv)
{
    FILE * rfp;

    if((rfp = fopen((const char *)argv[1], "r")) == NULL) {
        /*TODO:error_ms("mif():Can't Open file");*/
        /*DEL*/fprintf(stderr, "mif():Can't Open file\n");
        exit(1);
    }

    return rfp;
}

#include "header.h"

void mif(int argc, char **argv)
{
    FILE * rfp;

    if((rfp = fopen((const char *)argv[1], "r")) == NULL) {
        //error_ms("mif():Can't Open file");
        fprintf(stderr, "mif():Can't Open file\n");
        exit(1);
    }
    fclose(rfp);
}

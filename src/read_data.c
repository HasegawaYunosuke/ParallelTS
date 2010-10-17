#include "header.h"

#define RLINESIZE 256
#define RBUFFSIZE 256

void mif(int argc, char **argv)
{
    FILE * rfp;

    rfop(argv, rfp);
    rif_sd(rfp);
    fclose(rfp);
}

void rif_sd(FILE * rfp)
{
    char buf[RBUFFSIZE];

    for(;;) {
        printf("TEST\n");
        if(fgets(buf, RLINESIZE, rfp) == NULL) {
            break;
        }
        else {
            printf("TEST2\n");
            /*DEL*/printf("READ:%s\n", buf);
        }
    }
}

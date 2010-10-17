#include "header.h"

#define RLINESIZE 256
#define RBUFFSIZE 256

void mif(int argc, char **argv)
{
    FILE * rfp;

    rfp = rfop(argv);
    rif_sd(rfp);
    fclose(rfp);
}

void rif_sd(FILE * rfp)
{
    char buf[RBUFFSIZE];

    for(;;) {
        if(fgets(buf, RLINESIZE, rfp) == NULL) {
            break;
        }
        else {
            /*DEL*/printf("READ:%s", buf);
        }
    }
}

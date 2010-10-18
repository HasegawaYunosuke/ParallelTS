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
    int li; /* Line Index */
    char buf[RBUFFSIZE];

    for(li = 1;; li++) {
        if(fgets(buf, RLINESIZE, rfp) == NULL) {
            break;
        }
        else {
            arld(buf, li);
        }
    }
}

void arld(char * rld, int li)
{
    /*DEL*/printf("%2d %s", li, rld);

    /* Input TSPLIB's problem name */
    if(li == 1) {
        itpn(rld);
    }
    /* Search Time */
    else if(li == 2) {
    }
    /* ON/OFF Muli-core Mode */
    else if(li == 3) {
    }
    /* ON/OFF MPI Mode */
    else if(li == 4) {
    }
    /* What type of result do you use ? */
    else if(li == 5) {
    }
    /* Output Debug-Log-Data:type1 */
    else if(li == 6) {
    }
    /* Output Debug-Log-Data:type2 */
    else if(li == 7) {
    }
    /* Output Debug-Log-Data:type3 */
    else if(li == 8) {
    }
    /* Output Debug-Log-Data:type4 */
    else if(li == 9) {
    }
    /* On Sale */
    /*else if(li == 10) {
    }
    else if(li == 11) {
    }
    else if(li == 12) {
    }
    else if(li == 13) {
    }
    else if(li == 14) {
    }*/
    /* The Percentage of Permission toward Worse */
    else if(li == 15) {
    }
    /* The Number of Permission toward Worse */
    else if(li == 16) {
    }
    /* The Number of Loop */
    else if(li == 17) {
    }
    /* The Size of Tabu-List */
    else if(li == 18) {
    }
    /* The Term of Validity of Tabu-List */
    else if(li == 19) {
    }
}

void itpn(char * rld)
{
    int i, j;
    int pssi = 0; /* Problem Size String Index */
    int ps;
    char pss[64]; /* Problem Size String */
    char pn[64]; /* Problem Name */

    for(i = 0;; i++) {
        if(rld[i] == ':') {
            for(j = i + 1;; j++) {
                if(rld[j] == '\n' || rld[j] == '\0') {
                    break;
                }
                else {
                    else if(rld[j] == '.') {
                        ps = atoi(pss);
                        /*DEL*/printf("ps == %d\n", ps);
                    }
                    else if(rld[j] >= '0' && rld[j] <= '9') {
                        pss[pssi] = rld[j]; pssi++;
                    }
                }
            }
        }
        if(rld[j] == '\n' || rld[j] == '\0') {
            break;
        }
    }
}


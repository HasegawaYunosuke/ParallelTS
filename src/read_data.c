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
        ssti(rld);
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
    int di; /* Data Index */
    int ps; /* Problem Size */
    char pn[64]; /* Problem Name */

    di = gdbl(rld);
    ps = gdnu(rld, di);
    /*DEL*/printf("ps == %d\n", ps);
    gdna(rld, di, pn);
    /*DEL*/printf("pn == %s\n", pn);
}

void ssti(char * rld)
{
    int di = -1; /* Data Index */
    int st; /* Search Time */

    di = gdbl(rld);
    st = gdnu(rld, di);
    /*DEL*/printf("st == %d[sec]\n", st);
}

int gdbl(char * rld)
{
    int i;

    for(i = 0;; i++) {
        if(rld[i] == ':') {
            return i + 1;
        }
        else if(rld[i] == '\0') {
            return -1;
        }
    }
}

int gdnu(char * rld, int di)
{
    int i;
    int pssi = 0; /* Problem Size String Index */
    char pss[64]; /* Problem Size String */

    for(i = di;; i++) {
        if(rld[i] == '\n' || rld[i] == '\0') {
            return atoi(pss);
        }
        else {
            if(rld[i] >= '0' && rld[i] <= '9') {
                pss[pssi] = rld[i]; pssi++;
            }
        }
    }
}

void gdna(char * rld, int di, char * pn)
{
    int i;
    int pni = 0; /* Problem Name Index */

    for(i = di;; i++) {
        if(rld[i] == '\n' || rld[i] == '\0') {
            pn[pni] = '\0';
            break;
        }
        pn[pni] = rld[i]; pni++;
    }
}

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
    /* ON/OFF Multi-core Mode */
    else if(li == 3) {
        smcm(rld);
    }
    /* ON/OFF MPI Mode */
    else if(li == 4) {
        smpim(rld);
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

    if((di = gdbl(rld)) >= 0) {
        ps = gdnu(rld, di);
        /*DEL*/printf("ps == %d\n", ps);
        gdna(rld, di, pn);
        /*DEL*/printf("pn == %s\n", pn);
    }
    else {
        /*todo*///error("itpn():rld error\n");
        exit(1);
    }
}

void ssti(char * rld)
{
    int di = -1; /* Data Index */
    int st; /* Search Time */

    if((di = gdbl(rld)) >= 0) {
        st = gdnu(rld, di);
        /*DEL*/printf("st == %d[sec]\n", st);
    }
    else {
        /*todo*///error("itpn():rld error\n");
        exit(1);
    }
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

void smcm(char * rld)
{
    int di = -1; /* Data Index */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            /*DEL*/printf("Multi-core Mode ON\n");
        }
    }
    else {
        /*todo*///error("itpn():rld error\n");
        exit(1);
    }
}

void smpim(char * rld)
{
    int di = -1; /* Data Index */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            /*DEL*/printf("MPI Mode ON\n");
        }
    }
    else {
        /*todo*///error("itpn():rld error\n");
        exit(1);
    }
}

int gonoff(char * rld, int di)
{
    if(rld[di + 1] == 'N') {
        return ON;
    }
    else if(rld[di + 1] == 'F') {
        return OFF;
    }
    else {
        /*todo*///error("itpn():rld error\n");
        exit(1);
    }
}

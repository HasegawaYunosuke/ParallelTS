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
        wtres(rld);
    }
    /* Output Debug-Log-Data:type1 */
    else if(li == 6) {
        gdld1(rld);
    }
    /* Output Debug-Log-Data:type2 */
    else if(li == 7) {
        gdld2(rld);
    }
    /* Output Debug-Log-Data:type3 */
    else if(li == 8) {
        gdld3(rld);
    }
    /* Output Debug-Log-Data:type4 */
    else if(li == 9) {
        gdld4(rld);
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
        gppw(rld);
    }
    /* The Number of Permission toward Worse */
    else if(li == 16) {
        gplw(rld);
    }
    /* The Number of Loop */
    else if(li == 17) {
        gplt(rld);
    }
    /* The Size of Tabu-List */
    else if(li == 18) {
        gpst(rld);
    }
    /* The Term of Validity of Tabu-List */
    else if(li == 19) {
        gptt(rld);
    }
}

void itpn(char * rld)
{
    int di; /* Data Index */
    int ps; /* Problem Size */
    char pn[64]; /* Problem Name */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        ps = gdnu(rld, di);
        g_bd.ps = ps;
        gdna(rld, di, pn);
        strcpy(g_bd.pn, pn);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("itpn", ms, 0);
        exit(1);
    }
}

void ssti(char * rld)
{
    int di = -1; /* Data Index */
    int st; /* Search Time */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        st = gdnu(rld, di);
        g_bd.st = st;
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("ssti", ms, 0);
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
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.mcm = ON;
        }
        else {
            g_bm.mcm = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("smcm", ms, 0);
        exit(1);
    }
}

void smpim(char * rld)
{
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.mpim = ON;
        }
        else {
            g_bm.mpim = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("smpim", ms, 0);
        exit(1);
    }
}

int gonoff(char * rld, int di)
{
    char ms[32]; /* Message */

    if(rld[di + 1] == 'N') {
        return ON;
    }
    else if(rld[di + 1] == 'F') {
        return OFF;
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gonoff", ms, 0);
        exit(1);
    }
}

void wtres(char * rld)
{
    int i;
    int di = -1; /* Data Index */
    int sdi = 0; /* String Data Index */
    char sd[64]; /* String Data */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        for(i = di;; i++) {
            if(rld[i] == '\n' || rld[i] == '\0') {
                sd[sdi] = '\0';
                break;
            }
            sd[sdi] = rld[i]; sdi++;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("wtres", ms, 0);
        exit(1);
    }

    if(strcmp(sd, "simple") == 0) {
        g_bm.tres = DEFAULT;
    }
    else if(strcmp(sd, "navi") == 0) {
        g_bm.tres = TYPE1;
    }
    else {
        sprintf(ms, "Wrong Result Mode:\"%s\"", sd);
        oem("wtres", ms, 0);
        exit(1);
    }
}

void gdld1(char * rld)
{
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.dld1 = ON;
        }
        else {
            g_bm.dld1 = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gdld1", ms, 0);
        exit(1);
    }
}

void gdld2(char * rld)
{
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.dld2 = ON;
        }
        else {
            g_bm.dld2 = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gdld2", ms, 0);
        exit(1);
    }
}

void gdld3(char * rld)
{
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.dld3 = ON;
        }
        else {
            g_bm.dld3 = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gdld3", ms, 0);
        exit(1);
    }
}

void gdld4(char * rld)
{
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if(gonoff(rld, di)) {
            g_bm.dld4 = ON;
        }
        else {
            g_bm.dld4 = OFF;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gdld4", ms, 0);
        exit(1);
    }
}

void gppw(char * rld)
{
    int di = -1; /* Data Index */
    double pw; /* Percentage toward Worse[%] */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pw = (double)gdnu(rld, di);
        /*TODO*/printf("gppw():pw == %f\n", pw);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gppw", ms, 0);
        exit(1);
    }
}

void gplw(char * rld)
{
    int pn; /* Part of Number */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pn = gnxn(di, rld);
        printf("gplw():pn == %d\n", pn);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplw", ms, 0);
        exit(1);
    }
}

void gplt(char * rld)
{
    int pn; /* Part of Number */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pn = gnxn(di, rld);
        printf("gplt():pn == %d\n", pn);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplt", ms, 0);
        exit(1);
    }
}

void gpst(char * rld)
{
    int pn; /* Part of Number */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pn = gnxn(di, rld);
        /*TODO*/printf("gpst():pn == %d\n", pn);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplt", ms, 0);
        exit(1);
    }
}

void gptt(char * rld)
{
    int pn; /* Part of Number */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pn = gnxn(di, rld);
        /*TODO*/printf("gptt():pn == %d\n", pn);
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplt", ms, 0);
        exit(1);
    }
}

int gnxn(int di, char * rld)
{
    int i;
    char pns[16]; /* Part of Number: String ver */
    int pnsi = 0; /* Part of Number: String ver  Index */
    int pn = 1;
    /*DEL*/int tspsize = 2;

    for(i = di;; i++) {
        if(rld[i] == '\n' || rld[i] == '\0') {
            pns[pnsi] = '\0';
            if(atoi(pns) != 0) {
                pn *= atoi(pns);
            }
            return pn;
        }

        if(rld[i] >= '0' && rld[i] <= '9') {
            pns[pnsi] = rld[i]; pnsi++;
        }
        else if(rld[i] == 'N') {
            pn *= tspsize;
        }
    }
}


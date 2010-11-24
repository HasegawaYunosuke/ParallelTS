#include "header.h"

#define RLINESIZE 256
#define RBUFFSIZE 256

void mif(int argc, char **argv)
{
    FILE * rfd; /* Readonly-File Disctpriter */

    cnd("tsplib");
    rfd = rfop(argv[1], "mif");
    rif_sd(rfd);
    fclose(rfd);
}

void rif_sd(FILE * rfd)
{
    int li; /* Line Index */
    char buf[RBUFFSIZE];

    for(li = 1;; li++) {
        memset(buf, '0', RBUFFSIZE);
        buf[RBUFFSIZE - 1] = '\0';
        if(fgets(buf, sizeof(buf), rfd) == NULL) {
            break;
        }
        else {
            arld(buf, li);
        }
    }
}

void arld(char * rld, int li)
{
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
    /* Initialize Path Create Mode */
    else if(li == 6) {
        ipcm(rld);
    }
    /* Output Debug-Log-Data:type1 */
    else if(li == 7) {
        gdld1(rld);
    }
    /* Output Debug-Log-Data:type2 */
    else if(li == 8) {
        gdld2(rld);
    }
    /* Output Debug-Log-Data:type3 */
    else if(li == 9) {
        gdld3(rld);
    }
    /* Output Debug-Log-Data:type4 */
    else if(li == 10) {
        gdld4(rld);
    }
    /* On Sale */
    /*else if(li == 11) {
    }
    else if(li == 12) {
    }
    else if(li == 13) {
    }*/
    /* The Number of Thread */
    else if(li == 14) {
        gpnth(rld);
        /* Memory Allocation about "struct ig_p" */
        aig_p();
    }
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
    }
}

void ipcm(char * rld)
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
        oem("ipcm", ms, 0);
    }

    if(strcmp(sd, "rand") == 0) {
        g_bm.ipcm = DEFAULT;
    }
    else if(strcmp(sd, "nn") == 0) {
        g_bm.ipcm = TYPE1;
    }
    else {
        sprintf(ms, "Wrong Result Mode:\"%s\"", sd);
        oem("ipcm", ms, 0);
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
    }
}

void gpnth(char * rld)
{
    int di = -1; /* Data Index */
    int nth = 1; /* Number of Thread */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        if((nth = gdnu(rld, di)) == 0) {
            nth = 1;
        }
        g_bd.nth = nth;
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gpnth", ms, 0);
    }
}

void gppw(char * rld)
{
    int i;
    int di = -1; /* Data Index */
    double pw; /* Percentage toward Worse[%] */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        pw = (double)gdnu(rld, di);
        for(i = 0; i < g_bd.nth; i++) {
            ig_p[i].pw = pw;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gppw", ms, 0);
    }
}

void gplw(char * rld)
{
    int i;
    int lw; /* Loop times toward Worse */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        lw = gnxn(di, rld);
        for(i = 0; i < g_bd.nth; i++) {
            ig_p[i].lw = lw;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplw", ms, 0);
    }
}

void gplt(char * rld)
{
    int i;
    int lt; /* Loop times */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        lt = gnxn(di, rld);
        for(i = 0; i < g_bd.nth; i++) {
            ig_p[i].lt = lt;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gplt", ms, 0);
    }
}

void gpst(char * rld)
{
    int i;
    int stl; /* Size of Tabu List */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        stl = gnxn(di, rld);
        for(i = 0; i < g_bd.nth; i++) {
            ig_p[i].stl = stl;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gpst", ms, 0);
    }
}

void gptt(char * rld)
{
    int i;
    int ttl; /* Part of Number */
    int di = -1; /* Data Index */
    char ms[32]; /* Message */

    if((di = gdbl(rld)) >= 0) {
        ttl = gnxn(di, rld);
        for(i = 0; i < g_bd.nth; i++) {
            ig_p[i].ttl = ttl;
        }
    }
    else {
        sprintf(ms, "Wrong Data Format:\"%s\"", rld);
        oem("gptt", ms, 0);
    }
}

int gnxn(int di, char * rld)
{
    int i;
    char pns[16]; /* Part of Number: String ver */
    int pnsi = 0; /* Part of Number: String ver  Index */
    int pn = 1;

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
            pn *= g_bd.ps;
        }
    }
}

void mtsplib(void)
{
    char ofp[64]; /* Open File Path */
    FILE * rfd; /* Readonly-File Disctpriter */
    char ms[64]; /* Message */

    sprintf(ofp, "tsplib/%s", g_bd.pn);
    rfd = rfop(ofp, "mtsplib");
    rtsplib_sd(rfd);
    fclose(rfd);
    sgd();
}

void rtsplib_sd(FILE * rfp)
{
    char buf[RBUFFSIZE];
    char mychmpbuf[RBUFFSIZE]; /* My-Chomp-Buffer */
    int dlf = OFF; /* Data Line Flag */
    int dli = 0; /* Data Line Index */

    for(;;) {
        if(fgets(buf, RLINESIZE, rfp) == NULL) {
            if(dlf == OFF) {
                oem("rtsplib_sd", "Wrong TSPLIB Problem.", 0);
            }
            break;
        }
        else if(dlf == OFF) {
            mychmp(buf, mychmpbuf);
            if(strcmp(mychmpbuf, "NODE_COORD_SECTION") == 0) {
                dlf = ON;
            }
            else if(strcmp(mychmpbuf, "EDGE_WEIGHT_SECTION") == 0) {
                oem("rtsplib_sd", "This Program is Only-Available: \"NODE_COORD_SECTION\"", 0);
            }
        }
        else if(dlf == ON && dli < g_bd.ps) {
            artsplibld(buf, dli);
            dli++;
        }
        else {
            break;
        }
    }
}

void mychmp(char * buf, char * mychmpbuf)
{
    int i;

    for(i = 0; i < RBUFFSIZE; i++) {
        if(buf[i] == ' ' || buf[i] == '\n') {
            mychmpbuf[i] = '\0';
            break;
        }
        else {
            mychmpbuf[i] = buf[i];
        }
    }
}

void artsplibld(char * rld, int dli)
{
    int i, j, di; /* Index, Data-Index */
    int sl = (int)strlen(rld); /* String Length */
    int df = OFF; /* Data-Flag */
    int cf = OFF; /* City-Flag */
    int xf = OFF; /* X-Flag */
    int yf = OFF; /* Y-Flag */
    int csdi = 0;
    int xsdi = 0;
    int ysdi = 0;
    char csd[128] = {0}; /* City String Data */
    char xsd[128] = {0}; /* X String Data */
    char ysd[128] = {0}; /* Y String Data */

    if(strcmp(rld, "EOF\n") != 0) {
        for(i = 0; i < sl; i++) {
            if(cf == OFF && xf == OFF && yf == OFF) {
                if(rld[i] >= '0' && rld[i] <= '9') {
                    if(df == OFF) {
                        df = ON;
                    }
                    csd[csdi] = rld[i];
                    if(csdi < 128) {
                        csdi++;
                    }
                    else {
                        oem("artsplibld", "csd[]:Over Buffer Size", 128);
                    }
                }
                else if(rld[i] == ' ' || rld[i] == '\t') {
                    if(df == ON) {
                        cf = ON; df = OFF;
                        csd[csdi] = '\0';
                    }
                }
            }
            else if(cf == ON && xf == OFF && yf == OFF) {
                if((rld[i] >= '0' && rld[i] <= '9') || rld[i] == '.' || rld[i] == 'e' || rld[i] == '+' || rld[i] == '-') {
                    if(df == OFF) {
                        df = ON;
                    }
                    xsd[xsdi] = rld[i];
                    if(xsdi < 128) {
                        xsdi++;
                    }
                    else {
                        oem("artsplibld", "xsd[]:Over Buffer Size", 128);
                    }
                }
                else if(rld[i] == ' ') {
                    if(df == ON) {
                        xf = ON; df = OFF;
                        xsd[xsdi] = '\0';
                    }
                }
            }
            else if(cf == ON && xf == ON && yf == OFF) {
                if((rld[i] >= '0' && rld[i] <= '9') || rld[i] == '.' || rld[i] == 'e' || rld[i] == '+' || rld[i] == '-') {
                    if(df == OFF) {
                        df = ON;
                    }
                    ysd[ysdi] = rld[i];
                    if(ysdi < 128) {
                        ysdi++;
                    }
                    else {
                        oem("artsplibld", "ysd[]:Over Buffer Size", 128);
                    }
                }
                else if(rld[i] == ' ') {
                    if(df == ON) {
                        yf = ON; df = OFF;
                        ysd[ysdi] = '\0';
                        break;
                    }
                }
            }
        }
    }

    /* Input City-Number */
    g_bd.btsp[0][dli] = atof(csd);
    g_bd.btsp[1][dli] = atof(xsd);
    g_bd.btsp[2][dli] = atof(ysd);

    ///*DEL*/printf("%d:(index,x,y) == (%3d,%8f,%8f)\n", dli, (int)g_bd.btsp[0][dli], g_bd.btsp[1][dli], g_bd.btsp[2][dli]);
}

void sgd(void)
{
    int i;
    int sc = 0; /* Start City number */
    int ec = 0; /* City number */
    double temp = 0.0;

    for(sc = 0; sc < g_bd.ps; sc++) {
        for(ec = sc; ec < g_bd.ps; ec++) {
            temp = dif_2p(g_bd.btsp[1][sc], g_bd.btsp[2][sc], g_bd.btsp[1][ec], g_bd.btsp[2][ec]);
            g_bd.bgd[sc][ec] = temp; g_bd.bgd[ec][sc] = temp;
        } }
}

void gbs_bpn(void)
{
    char ms[32]; /* Message */

    if(strcmp(g_bd.pn, "a280.tsp") == 0) {
        g_bd.kn_bs = 2579.0;
    }
    else if(strcmp(g_bd.pn, "ali535.tsp") == 0) {
        g_bd.kn_bs = 202339.0;
    }
    else if(strcmp(g_bd.pn, "att48.tsp") == 0) {
        g_bd.kn_bs = 10628.0;
    }
    else if(strcmp(g_bd.pn, "att532.tsp") == 0) {
        g_bd.kn_bs = 27686.0;
    }
    else if(strcmp(g_bd.pn, "berlin52.tsp") == 0) {
        g_bd.kn_bs = 7542.0;
    }
    else if(strcmp(g_bd.pn, "bier127.tsp") == 0) {
        g_bd.kn_bs = 118282.0;
    }
    else if(strcmp(g_bd.pn, "brd14051.tsp") == 0) {
        g_bd.kn_bs = 469385.0;
    }
    else if(strcmp(g_bd.pn, "burma14.tsp") == 0) {
        g_bd.kn_bs = 3323.0;
    }
    else if(strcmp(g_bd.pn, "ch130.tsp") == 0) {
        g_bd.kn_bs = 6110.0;
    }
    else if(strcmp(g_bd.pn, "ch150.tsp") == 0) {
        g_bd.kn_bs = 6528.0;
    }
    else if(strcmp(g_bd.pn, "d1291.tsp") == 0) {
        g_bd.kn_bs = 50801.0;
    }
    else if(strcmp(g_bd.pn, "d15112.tsp") == 0) {
        g_bd.kn_bs = 1573084.0;
    }
    else if(strcmp(g_bd.pn, "d1655.tsp") == 0) {
        g_bd.kn_bs = 62128.0;
    }
    else if(strcmp(g_bd.pn, "d18512.tsp") == 0) {
        g_bd.kn_bs = 645238.0;
    }
    else if(strcmp(g_bd.pn, "d198.tsp") == 0) {
        g_bd.kn_bs = 15780.0;
    }
    else if(strcmp(g_bd.pn, "d2103.tsp") == 0) {
        g_bd.kn_bs = 80450.0;
    }
    else if(strcmp(g_bd.pn, "d493.tsp") == 0) {
        g_bd.kn_bs = 35002.0;
    }
    else if(strcmp(g_bd.pn, "d657.tsp") == 0) {
        g_bd.kn_bs = 48912.0;
    }
    else if(strcmp(g_bd.pn, "dsj1000.tsp") == 0) {
        g_bd.kn_bs = 18659688.0;
    }
    else if(strcmp(g_bd.pn, "eil101.tsp") == 0) {
        g_bd.kn_bs = 629.0;
    }
    else if(strcmp(g_bd.pn, "eil51.tsp") == 0) {
        g_bd.kn_bs = 426.0;
    }
    else if(strcmp(g_bd.pn, "eil76.tsp") == 0) {
        g_bd.kn_bs = 538.0;
    }
    else if(strcmp(g_bd.pn, "fl1400.tsp") == 0) {
        g_bd.kn_bs = 20127.0;
    }
    else if(strcmp(g_bd.pn, "fl1577.tsp") == 0) {
        g_bd.kn_bs = 22249.0;
    }
    else if(strcmp(g_bd.pn, "fl3795.tsp") == 0) {
        g_bd.kn_bs = 28772.0;
    }
    else if(strcmp(g_bd.pn, "fl417.tsp") == 0) {
        g_bd.kn_bs = 11861.0;
    }
    else if(strcmp(g_bd.pn, "fnl4461.tsp") == 0) {
        g_bd.kn_bs = 182566.0;
    }
    else if(strcmp(g_bd.pn, "gil262.tsp") == 0) {
        g_bd.kn_bs = 2378.0;
    }
    else if(strcmp(g_bd.pn, "gr137.tsp") == 0) {
        g_bd.kn_bs = 69853.0;
    }
    else if(strcmp(g_bd.pn, "gr202.tsp") == 0) {
        g_bd.kn_bs = 40160.0;
    }
    else if(strcmp(g_bd.pn, "gr229.tsp") == 0) {
        g_bd.kn_bs = 134602.0;
    }
    else if(strcmp(g_bd.pn, "gr431.tsp") == 0) {
        g_bd.kn_bs = 171414.0;
    }
    else if(strcmp(g_bd.pn, "gr666.tsp") == 0) {
        g_bd.kn_bs = 294358.0;
    }
    else if(strcmp(g_bd.pn, "gr96.tsp") == 0) {
        g_bd.kn_bs = 55209.0;
    }
    else if(strcmp(g_bd.pn, "kroA100.tsp") == 0) {
        g_bd.kn_bs = 21282.0;
    }
    else if(strcmp(g_bd.pn, "kroA150.tsp") == 0) {
        g_bd.kn_bs = 26524.0;
    }
    else if(strcmp(g_bd.pn, "kroA200.tsp") == 0) {
        g_bd.kn_bs = 29368.0;
    }
    else if(strcmp(g_bd.pn, "kroB100.tsp") == 0) {
        g_bd.kn_bs = 22141.0;
    }
    else if(strcmp(g_bd.pn, "kroB150.tsp") == 0) {
        g_bd.kn_bs = 26130.0;
    }
    else if(strcmp(g_bd.pn, "kroB200.tsp") == 0) {
        g_bd.kn_bs = 29437.0;
    }
    else if(strcmp(g_bd.pn, "kroC100.tsp") == 0) {
        g_bd.kn_bs = 20749.0;
    }
    else if(strcmp(g_bd.pn, "kroD100.tsp") == 0) {
        g_bd.kn_bs = 21294.0;
    }
    else if(strcmp(g_bd.pn, "kroE100.tsp") == 0) {
        g_bd.kn_bs = 22068.0;
    }
    else if(strcmp(g_bd.pn, "lin105.tsp") == 0) {
        g_bd.kn_bs = 14379.0;
    }
    else if(strcmp(g_bd.pn, "lin318.tsp") == 0) {
        g_bd.kn_bs = 42029.0;
    }
    else if(strcmp(g_bd.pn, "linhp318.tsp") == 0) {
        g_bd.kn_bs = 41345.0;
    }
    else if(strcmp(g_bd.pn, "nrw1379.tsp") == 0) {
        g_bd.kn_bs = 56638.0;
    }
    else if(strcmp(g_bd.pn, "p654.tsp") == 0) {
        g_bd.kn_bs = 34643.0;
    }
    else if(strcmp(g_bd.pn, "pcb1173.tsp") == 0) {
        g_bd.kn_bs = 56892.0;
    }
    else if(strcmp(g_bd.pn, "pcb3038.tsp") == 0) {
        g_bd.kn_bs = 137694.0;
    }
    else if(strcmp(g_bd.pn, "pcb442.tsp") == 0) {
        g_bd.kn_bs = 50778.0;
    }
    else if(strcmp(g_bd.pn, "pla33810.tsp") == 0) {
        g_bd.kn_bs = 66048945.0;
    }
    else if(strcmp(g_bd.pn, "pla7397.tsp") == 0) {
        g_bd.kn_bs = 23260728.0;
    }
    else if(strcmp(g_bd.pn, "pla85900.tsp") == 0) {
        g_bd.kn_bs = 142382641.0;
    }
    else if(strcmp(g_bd.pn, "pr1002.tsp") == 0) {
        g_bd.kn_bs = 259045.0;
    }
    else if(strcmp(g_bd.pn, "pr107.tsp") == 0) {
        g_bd.kn_bs = 44303.0;
    }
    else if(strcmp(g_bd.pn, "pr124.tsp") == 0) {
        g_bd.kn_bs = 59030.0;
    }
    else if(strcmp(g_bd.pn, "pr136.tsp") == 0) {
        g_bd.kn_bs = 96772.0;
    }
    else if(strcmp(g_bd.pn, "pr144.tsp") == 0) {
        g_bd.kn_bs = 58537.0;
    }
    else if(strcmp(g_bd.pn, "pr152.tsp") == 0) {
        g_bd.kn_bs = 73682.0;
    }
    else if(strcmp(g_bd.pn, "pr226.tsp") == 0) {
        g_bd.kn_bs = 80369.0;
    }
    else if(strcmp(g_bd.pn, "pr2392.tsp") == 0) {
        g_bd.kn_bs = 378032.0;
    }
    else if(strcmp(g_bd.pn, "pr264.tsp") == 0) {
        g_bd.kn_bs = 49135.0;
    }
    else if(strcmp(g_bd.pn, "pr299.tsp") == 0) {
        g_bd.kn_bs = 48191.0;
    }
    else if(strcmp(g_bd.pn, "pr439.tsp") == 0) {
        g_bd.kn_bs = 107217.0;
    }
    else if(strcmp(g_bd.pn, "pr76.tsp") == 0) {
        g_bd.kn_bs = 108159.0;
    }
    else if(strcmp(g_bd.pn, "rat195.tsp") == 0) {
        g_bd.kn_bs = 2323.0;
    }
    else if(strcmp(g_bd.pn, "rat575.tsp") == 0) {
        g_bd.kn_bs = 6773.0;
    }
    else if(strcmp(g_bd.pn, "rat783.tsp") == 0) {
        g_bd.kn_bs = 8806.0;
    }
    else if(strcmp(g_bd.pn, "rat99.tsp") == 0) {
        g_bd.kn_bs = 1121.0;
    }
    else if(strcmp(g_bd.pn, "rd100.tsp") == 0) {
        g_bd.kn_bs = 7910.0;
    }
    else if(strcmp(g_bd.pn, "rd400.tsp") == 0) {
        g_bd.kn_bs = 15281.0;
    }
    else if(strcmp(g_bd.pn, "rl11849.tsp") == 0) {
        g_bd.kn_bs = 923288.0;
    }
    else if(strcmp(g_bd.pn, "rl1304.tsp") == 0) {
        g_bd.kn_bs = 252948.0;
    }
    else if(strcmp(g_bd.pn, "rl1323.tsp") == 0) {
        g_bd.kn_bs = 270199.0;
    }
    else if(strcmp(g_bd.pn, "rl1889.tsp") == 0) {
        g_bd.kn_bs = 316536.0;
    }
    else if(strcmp(g_bd.pn, "rl5915.tsp") == 0) {
        g_bd.kn_bs = 565530.0;
    }
    else if(strcmp(g_bd.pn, "rl5934.tsp") == 0) {
        g_bd.kn_bs = 556045.0;
    }
    else if(strcmp(g_bd.pn, "st70.tsp") == 0) {
        g_bd.kn_bs = 675.0;
    }
    else if(strcmp(g_bd.pn, "ts225.tsp") == 0) {
        g_bd.kn_bs = 126643.0;
    }
    else if(strcmp(g_bd.pn, "tsp225.tsp") == 0) {
        g_bd.kn_bs = 3916.0;
    }
    else if(strcmp(g_bd.pn, "u1060.tsp") == 0) {
        g_bd.kn_bs = 224094.0;
    }
    else if(strcmp(g_bd.pn, "u1432.tsp") == 0) {
        g_bd.kn_bs = 152970.0;
    }
    else if(strcmp(g_bd.pn, "u159.tsp") == 0) {
        g_bd.kn_bs = 42080.0;
    }
    else if(strcmp(g_bd.pn, "u1817.tsp") == 0) {
        g_bd.kn_bs = 57201.0;
    }
    else if(strcmp(g_bd.pn, "u2152.tsp") == 0) {
        g_bd.kn_bs = 64253.0;
    }
    else if(strcmp(g_bd.pn, "u2319.tsp") == 0) {
        g_bd.kn_bs = 234256.0;
    }
    else if(strcmp(g_bd.pn, "u574.tsp") == 0) {
        g_bd.kn_bs = 36905.0;
    }
    else if(strcmp(g_bd.pn, "u724.tsp") == 0) {
        g_bd.kn_bs = 41910.0;
    }
    else if(strcmp(g_bd.pn, "ulysses16.tsp") == 0) {
        g_bd.kn_bs = 6859.0;
    }
    else if(strcmp(g_bd.pn, "ulysses22.tsp") == 0) {
        g_bd.kn_bs = 7013.0;
    }
    else if(strcmp(g_bd.pn, "usa13509.tsp") == 0) {
        g_bd.kn_bs = 19982859.0;
    }
    else if(strcmp(g_bd.pn, "vm1084.tsp") == 0) {
        g_bd.kn_bs = 239297.0;
    }
    else if(strcmp(g_bd.pn, "vm1748.tsp") == 0) {
        g_bd.kn_bs = 336556.0;
    }
    else {
        sprintf(ms, "Couldn't Find Out Problem %s's Known Best Solution", g_bd.pn);
        oem("gbs_bpn", ms, 0);
    }
}

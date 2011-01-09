#include "header.h"

struct dld1st {
    char dld1_lfn[256]; /* DEBUG1 Log-File-Name */
};

struct dld1st d1st;

void deb_init(void)
{
    FILE * tfdp; /* Temporary File Discpriter */

    ddeb_lfn();
    tfdp = wfop(d1st.dld1_lfn, "deb_init");
    fclose(tfdp);
}

void ddeb_lfn(void)
{
    char base_lfn[128];
    char mode_lfn1[16];

    sprintf(base_lfn, "debug/%s.%d.%d",
        g_bd.pn,/*Program Name*/
        g_bd.st,/*Search Time*/
        g_bd.nth/*Num of Thread*/
    );

    /* MPI MODE CHECK */
    if(g_bm.mpim == ON) {
        sprintf(mode_lfn1, "MPIMODE_ON");
    }
    else {
        sprintf(mode_lfn1, "MPIMODE_OFF");
    }
#ifdef MPIMODE
    sprintf(d1st.dld1_lfn, "%s.%s.node_%d_of_%d.deblog",
        base_lfn,
        mode_lfn1,
        g_bd.np_ae,
        g_bd.mpi_id
    );
#else
    sprintf(d1st.dld1_lfn, "%s.%s.deblog",
        base_lfn,
        mode_lfn1
    );
#endif
}

void * dld1func(void * temp_rn)
{
    FILE * fdp; /* File Discpriter */
    double rn;

    rn = *(double *)temp_rn;
    fdp = wfop(d1st.dld1_lfn, "deb_init");
    odld1(fdp, rn);
    fclose(fdp);
}

void odld1(FILE * fdp, double rn)
{
    int i;
    int ctls; /* Current Tabu-List Size */
    int intmax = INT_MAX;
    double bsd;

    if((int)(intmax / ig_p[0].stl) < g_bd.tl_lc) {
        ctls = intmax - 1;
    }
    else {
        ctls = g_bd.tl_lc * ig_p[0].stl + g_tli;
    }

    /* Timer */
    fprintf(fdp, "%f,", rn);

    /* Each Thread's Best Solution & Gap between My-Sol and Known Best Sol */
    for(i = 0; i < g_bd.nth; i++) {
        bsd = ig_p[i].bsd;
        fprintf(fdp, "%f,", bsd);
        fprintf(fdp, "%f,", (bsd - g_bd.kn_bs) / g_bd.kn_bs * 100);
    }

    fprintf(fdp, "%d\n", ctls);
}

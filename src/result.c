#include "header.h"

void out_r(void)
{
    FILE * wfd;
    char wfn[64];

    cnd("result");
#ifdef MPIMODE
    sprintf(wfn, "result/%s.%dsec.node_%d.res", g_bd.pn, g_bd.st, g_bd.mpi_id);
#else
    sprintf(wfn, "result/%s.%dsec.res", g_bd.pn, g_bd.st);
#endif
    wfd = wfop(wfn, "out_r");
    pres(wfd);
    fclose(wfd);
}

void pres(FILE * resfp)
{
    int i;

    if(g_bm.tres == DEFAULT) {
        for(i = 0; i < (g_bd.nth - 1); i++) {
            fprintf(resfp, "%f,", ig_p[i].bsd);
        }
        fprintf(resfp, "%f\n", ig_p[(g_bd.nth - 1)].bsd);
    }
    else if(g_bm.tres == TYPE1) {
        /*TODO*/
        for(i = 0; i < (g_bd.nth - 1); i++) {
            fprintf(resfp, "%f,", ig_p[i].bsd);
        }
        fprintf(resfp, "%f\n", ig_p[(g_bd.nth - 1)].bsd);
        /*TODO*/
    }
}

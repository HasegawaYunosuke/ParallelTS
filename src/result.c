#include "header.h"

void out_r(void)
{
    FILE * wfd;
    char wfn[64];
#ifdef MPIMODE
    int i, sdn = g_bd.nth;
    int root = 0;
    double wait;
    double sd[sdn];
    double rd[(sdn * g_bd.np_ae)];
#endif

    cnd("result");

#ifdef MPIMODE
    for(i = 0; i < g_bd.nth; i++) {
        sd[i] = ig_p[i].bsd;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(g_bd.mpi_id == 0) {
        MPI_Gather(sd, sdn, MPI_DOUBLE, rd, sdn, MPI_DOUBLE, root, MPI_COMM_WORLD);
        sprintf(wfn, "result/%s.%dsec.all_node.res", g_bd.pn, g_bd.st);
        wfd = wfop(wfn, "out_r");
        mpi_pres(wfd, rd, (sdn * g_bd.np_ae));
        fclose(wfd);
    }
    else {
        if((wait = g_bd.st / 100) > 1) {
            sleep((int)wait);
        }
        MPI_Gather(sd, sdn, MPI_DOUBLE, rd, sdn, MPI_DOUBLE, root, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
#else
    sprintf(wfn, "result/%s.%dsec.res", g_bd.pn, g_bd.st);
    wfd = wfop(wfn, "out_r");
    pres(wfd);
    fclose(wfd);
#endif
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
        /*TODO*/
    }
}

#ifdef MPIMODE
void mpi_pres(FILE * wfd, double * rd, int size)
{
    int i, j;

    if(g_bm.tres == DEFAULT) {
        for(i = 0; i < size; i = i + g_bd.nth) {
            for(j = i; j < (i + g_bd.nth - 1); j++) {
                fprintf(wfd, "%f,", rd[j]);
            }
            fprintf(wfd, "%f\n", rd[(i + g_bd.nth - 1)]);
        }
    }
    else if(g_bm.tres == TYPE1) {
        /*TODO*/
        /*TODO*/
    }
}
#endif

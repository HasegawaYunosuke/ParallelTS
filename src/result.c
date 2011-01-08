#include "header.h"

void out_r(void)
{
    FILE * wfd;
    char wfn[256];
#ifdef MPIMODE
    int i, sdn = g_bd.nth;
    int root = 0;
    double wait;
    double sd[sdn];
    double rd[(sdn * g_bd.np_ae)];
    char parameters[256];
#endif

    cnd("result");

#ifdef MPIMODE
    for(i = 0; i < g_bd.nth; i++) {
        sd[i] = ig_p[i].bsd;
    }
    if(g_bd.mpi_id == 0) {
        MPI_Gather(sd, sdn, MPI_DOUBLE, rd, sdn, MPI_DOUBLE, root, MPI_COMM_WORLD);
        set_pn(parameters);
        sprintf(wfn, "result/%s.%dsec.%s.node_%d.res", g_bd.pn, g_bd.st, parameters, g_bd.mpi_id);
        wfd = wfop(wfn, "out_r");
        mpi_pres(wfd, rd, (sdn * g_bd.np_ae));
        fclose(wfd);
        for(i = 0; i < g_bd.np_ae; i++) {
            for(;;) {
                if(MPI_Barrier(MPI_COMM_WORLD) == MPI_SUCCESS) {
                    break;
                }
            }
        }
    }
    else {
        MPI_Gather(sd, sdn, MPI_DOUBLE, rd, sdn, MPI_DOUBLE, root, MPI_COMM_WORLD);
        for(i = 0; i < g_bd.np_ae; i++) {
            for(;;) {
                if(MPI_Barrier(MPI_COMM_WORLD) == MPI_SUCCESS) {
                    break;
                }
            }
        }
    }
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
                fprintf(wfd, "%16.6f,%16.6f,", rd[j], (rd[j] - g_bd.kn_bs) / g_bd.kn_bs * 100);
            }
            fprintf(wfd, "%16.6f,%16.6f\n", rd[(i + g_bd.nth - 1)], (rd[(i + g_bd.nth - 1)] - g_bd.kn_bs) / g_bd.kn_bs * 100);
        }
    }
    else if(g_bm.tres == TYPE1) {
        /*TODO*/
        /*TODO*/
    }
}
#endif

#include "header.h"

double g_st_t;

void st_t(void)
{
    struct timeval t;
    double now_t;

    gettimeofday(&t, NULL);
    g_st_t = (double)t.tv_sec + (double)t.tv_usec * 1e-6;
}

double diff_t(void)
{
    struct timeval t;
    double rn; /* Return Number */
    /*DEL*/int i, show_t = 30;

    gettimeofday(&t, NULL);
    rn = ((double)t.tv_sec + (double)t.tv_usec * 1e-6) - g_st_t;

/*DEL*/
#ifdef MPIMODE
    if(pthread_equal(ig_p[0].ptn, pthread_self())) {
        if((int)rn % show_t == 0 && timerf == OFF && rn > 1) {
            //printf("Node %d Now:%f\n", g_bd.mpi_id, rn);
            printf("Node %d , clw_max == %d Now:%f\n", g_bd.mpi_id, ig_p[0].clw_max, rn);
            timerf = ON;
        }
        else if((int)rn % show_t != 0 && timerf == ON) {
            timerf = OFF;
        }
    }
#else
    if(pthread_equal(ig_p[0].ptn, pthread_self())) {
        if((int)rn % show_t == 0 && timerf == OFF && rn > 1) {
            printf("Now:%fsec. Best:(", rn);
            for(i = 0; i < g_bd.nth - 1; i++) {
                printf("%f,", ig_p[i].bsd);
            }
            printf("%f)\n", ig_p[(g_bd.nth - 1)].bsd);
            timerf = ON;
        }
        else if((int)rn % show_t != 0 && timerf == ON) {
            timerf = OFF;
        }
    }
#endif
/*DEL*/

#ifdef MPIMODE
    if(rn > (double)(g_bd.st - 5) && g_bm.mpi_recvsw == ON) {
        if(pthread_equal(ig_p[0].ptn, pthread_self()) && g_bm.mpim == ON) {
            pthread_cancel(g_recv_pth);
            g_bm.mpi_recvsw = OFF;
            /*DEL*/printf("Node:%d, Killed Recv-Thread\n", g_bd.mpi_id);
        }
    }
#endif

    return rn;
}

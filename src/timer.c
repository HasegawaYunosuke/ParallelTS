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

    gettimeofday(&t, NULL);
    rn = ((double)t.tv_sec + (double)t.tv_usec * 1e-6) - g_st_t;

/*DEL*/
#ifdef MPIMODE
    if(pthread_equal(ig_p[0].ptn, pthread_self())) {
        if((int)rn % 30 == 0 && timerf == OFF) {
            printf("Node %d Now:%f\n", g_bd.mpi_id, rn);
            timerf = ON;
        }
        else if((int)rn % 30 != 0 && timerf == ON) {
            timerf = OFF;
        }
    }
#else
    if(pthread_equal(ig_p[0].ptn, pthread_self())) {
        if((int)rn % 30 == 0 && timerf == OFF && g_bd.nth ==2) {
            printf("Now:%fsec. Best:(%f,%f)\n", rn, ig_p[0].bsd, ig_p[1].bsd);
            timerf = ON;
        }
        else if((int)rn % 30 != 0 && timerf == ON) {
            timerf = OFF;
        }
    }
#endif
/*DEL*/

    return rn;
}

#include "header.h"

void ptp(void)
{
    int i;
    int pid[g_bd.nth];

    pthread_mutex_init(&g_tb_mutex, NULL);
    for(i = 0; i < g_bd.nth; i++) {
        pid[i] = i;
        pthread_create(&ig_p[i].ptn, NULL, threp, (void *)&pid[i]);
    }
    for(i = 0; i < g_bd.nth; i++) {
        pthread_join(ig_p[i].ptn, NULL);
    }
}

void * threp(void * arg)
{
    srand(time(NULL)*(*(int *)arg + 1));
    initp((int *)arg);
    do {
        do {
            ts_proc((int *)arg);
        } while ((ig_p[*(int *)arg].clw < ig_p[*(int *)arg].lw) && (diff_t() < (double)g_bd.st));
#ifdef MPIMODE
        ig_p[*(int *)arg].clw = 0;
        if(g_bm.mpim == ON && pthread_equal(ig_p[0].ptn, pthread_self())) {
            if(diff_t() < (double)(g_bd.st - 10)) {
                mpi_want(*(int *)arg);
            }
        }

        if(g_bm.GAsm == ON) {
            if(chman(*(int *)arg) == YES) {
                if(diff_t() < (double)(g_bd.st - 10)) {
                    if(ig_p[*(int *)arg].tGA == TYPE3) {
                        ig_p[*(int *)arg].tGA = DEFAULT;
                        ga_proc((int *)arg);
                        ig_p[*(int *)arg].tGA = TYPE3;
                    }
                    else if(ig_p[*(int *)arg].tGA == TYPE4) {
                        ig_p[*(int *)arg].tGA = TYPE1;
                        ga_proc((int *)arg);
                        ig_p[*(int *)arg].tGA = TYPE4;
                    }
                    else {
                        rand_sm((int *)arg);
                    }
                }
            }
            else {
                if(diff_t() < (double)(g_bd.st - 10)) {
                    ga_proc((int *)arg);
                }
            }
        }
        else {
            if(diff_t() < (double)(g_bd.st - 10)) {
                ga_proc((int *)arg);
            }
        }
#endif
    } while (diff_t() < (double)g_bd.st);
}

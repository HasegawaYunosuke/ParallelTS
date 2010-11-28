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
    /*DEL*/
    /*if(pthread_equal(ig_p[*(int *)arg].ptn, pthread_self())) {
        printf("HYA HHA---!!!\n");
    }
    else {
        printf("HIDEBUUUUUU!\n");
    }*/
    /*DEL*/

    srand(time(NULL)*(*(int *)arg + 1));
    initp((int *)arg);
    do {
        do {
            ts_proc((int *)arg);
        } while ((ig_p[*(int *)arg].clw < ig_p[*(int *)arg].lw) && (diff_t() < (double)g_bd.st));
#ifdef MPIMODE
        ig_p[*(int *)arg].clw = 0;
        if(g_bm.mpim == ON) {
            //pthread_mutex_lock(&g_send_mutex);
            if(diff_t() < (double)(g_bd.st - 10)) {
                mpi_want(*(int *)arg);
            }
            //pthread_mutex_unlock(&g_send_mutex);
        }
#endif
    } while (diff_t() < (double)g_bd.st);
}

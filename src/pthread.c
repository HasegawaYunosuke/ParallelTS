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
    /* Create Initial-Path */
    initp((int *)arg);
    do {
        do {
            /* Tabu-Search Procedure */
            ts_proc((int *)arg);
        } while ((ig_p[*(int *)arg].clw < ig_p[*(int *)arg].lw) && (diff_t() < (double)g_bd.st));

#ifdef MPIMODE
        /* Procedure related GA */
        proc_rGA(arg);
#endif
    } while (diff_t() < (double)g_bd.st);
}

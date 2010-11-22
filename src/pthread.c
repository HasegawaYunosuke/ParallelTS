#include "header.h"

void ptp(void)
{
    int i;
    int pid[g_bd.nth];

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
        ts_proc((int *)arg);
    } while (diff_t() < (double)g_bd.st);
}

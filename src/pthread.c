#include "header.h"

void ptp(void)
{
    int i;
    int pid[g_bd.nth];

    for(i = 0; i < g_bd.nth; i++) {
        pid[i] = i;
        pthread_create(&ig_p[i].ptn, NULL, procedure, (void *)&pid[i]);
    }
    for(i = 0; i < g_bd.nth; i++) {
        pthread_join(ig_p[i].ptn, NULL);
    }
}

void * procedure(void * arg)
{
    if(pthread_equal(ig_p[*(int *)arg].ptn, pthread_self())) {
        printf("HYA HHA---!!!\n");
    }
    else {
        printf("HIDEBUUUUUU!\n");
    }
}

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

    gettimeofday(&t, NULL);

    return (((double)t.tv_sec + (double)t.tv_usec * 1e-6) - g_st_t);
}

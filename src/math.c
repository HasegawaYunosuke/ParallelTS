#include "header.h"

double dif_2p(double x1, double y1, double x2, double y2)
{
    double x = 0.0;
    double y = 0.0;

    if((x = x1 - x2) < 0) {
        x *= -1;
    }
    if((y = y1 - y2) < 0) {
        y *= -1;
    }

    return sqrt(x*x + y*y);
}

/* return 0 ~ (max - 1) */
int grn(int max)
{
    return rand() % max;
}

double gpd(int * path)
{
    int i;
    double sum = 0.0; /* Sum of All Distance */

    for(i = 0; i < g_bd.ps - 1; i++) {
        sum += g_bd.bgd[(path[i] - 1)][(path[i + 1] - 1)];
    }
    sum += g_bd.bgd[(path[g_bd.ps - 1])][(path[0] - 1)];

    return sum;
}

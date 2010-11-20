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

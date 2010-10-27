#include "header.h"

void abmem(void)
{
    ag_bd();
}

void faam(void)
{
    fg_bd();
}

void ag_bd(void)
{
    int i, j;

    if((g_bd.btsp = (double **)malloc(sizeof(double *) * 3)) == NULL) {
        oem("ag_bd", "Can't Allocate Memory (double **)", 0);
    }
    for(i = 0; i < 3; i++) {
        if((g_bd.btsp[i] = (double *)calloc(g_bd.ps, sizeof(double))) == NULL) {
            for(j = i; i > 0; i--) {
                free(g_bd.btsp[i - 1]);
            }
            free(g_bd.btsp);
            oem("ag_bd", "Can't Allocate Memory (double *)", 0);
        }
    }
}

void fg_bd(void)
{
    int i;

    for(i = 0; i < 3; i++) {
        free(g_bd.btsp[i]);
    }
    free(g_bd.btsp);
}

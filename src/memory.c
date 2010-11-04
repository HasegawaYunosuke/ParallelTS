#include "header.h"

void ffi(void)
{
    g_iamc_f.f_btsp = OFF;
    g_iamc_f.f_bgd = OFF;
    g_iamc_f.f_ipm = OFF;
}

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
        oem("ag_bd", "Can't Allocate Memory (double **)btsp", 0);
    }
    for(i = 0; i < 3; i++) {
        if((g_bd.btsp[i] = (double *)calloc(g_bd.ps, sizeof(double))) == NULL) {
            for(j = i; i > 0; i--) {
                free(g_bd.btsp[i - 1]);
            }
            free(g_bd.btsp);
            oem("ag_bd", "Can't Allocate Memory (double *)btsp", 0);
        }
    }
    g_iamc_f.f_btsp = ON;

    if((g_bd.bgd = (double **)malloc(sizeof(double *) * g_bd.ps)) == NULL) {
        oem("ag_bd", "Can't Allocate Memory (double **)bgd", 0);
    }
    for(i = 0; i < g_bd.ps; i++) {
        if((g_bd.bgd[i] = (double *)calloc(g_bd.ps, sizeof(double))) == NULL) {
            for(j = i; i > 0; i--) {
                free(g_bd.bgd[i - 1]);
            }
            free(g_bd.bgd);
            oem("ag_bd", "Can't Allocate Memory (double *)bgd", 0);
        }
    }
    g_iamc_f.f_bgd = ON;
}

void fg_bd(void)
{
    int i;


    for(i = 0; i < 3; i++) {
        free(g_bd.btsp[i]);
    }
    free(g_bd.btsp);

    for(i = 0; i < g_bd.ps; i++) {
        free(g_bd.bgd[i]);
    }
    free(g_bd.bgd);
}

void fnyfp(void)
{
    int i;

    if(g_iamc_f.f_btsp == ON) {
        for(i = 0; i < 3; i++) {
            free(g_bd.btsp[i]);
        }
        free(g_bd.btsp);
    }

    if(g_iamc_f.f_bgd == ON && g_iamc_f.f_btsp == ON) {
        fg_bd();
    }
}

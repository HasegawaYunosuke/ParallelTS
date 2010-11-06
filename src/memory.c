#include "header.h"

void ffi(void)
{
    g_amc_f.f_btsp = OFF;
    g_amc_f.f_bgd = OFF;
    g_amc_f.f_ipm = OFF;
}

void faam(void)
{
    fg_bd();
    fig_p();
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
    g_amc_f.f_btsp = ON;

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
    g_amc_f.f_bgd = ON;
}

void aig_p(void)
{
    if((ig_p = (struct _individual_parameter *)malloc(sizeof(struct _individual_parameter) * g_bd.nth)) == NULL) {
        oem("aig_p", "Can't Allocate Memory ig_p", 0);
    }
    else {
        g_amc_f.f_ipm = ON;
    }
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

    if(g_amc_f.f_btsp == ON) {
        for(i = 0; i < 3; i++) {
            free(g_bd.btsp[i]);
        }
        free(g_bd.btsp);
    }

    if(g_amc_f.f_btsp == ON) {
        for(i = 0; i < g_bd.ps; i++) {
            free(g_bd.bgd[i]);
        }
        free(g_bd.bgd);
    }

    if(g_amc_f.f_ipm == ON) {
        free(ig_p);
    }
}

void fig_p(void)
{
    free(ig_p);
}

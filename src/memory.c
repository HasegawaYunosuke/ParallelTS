#include "header.h"

void ffi(void)
{
    g_amc_f.f_btsp = OFF;
    g_amc_f.f_bgd = OFF;
    g_amc_f.f_ipm = OFF;
    g_amc_f.f_ipm_csp = OFF;
    g_amc_f.f_ipm_bsp = OFF;
    g_amc_f.f_to_tl = OFF;
    g_amc_f.f_bsp_mutex = OFF;
    g_amc_f.f_MPI_sdp_sp = OFF;
}

void ag_bd(void)
{
    int i, j;

    if((g_bd.btsp = (double **)malloc(sizeof(double) * 3)) == NULL) {
        oem("ag_bd", "Can't Allocate Memory (double **)btsp", 0);
    }
    for(i = 0; i < 3; i++) {
        if((g_bd.btsp[i] = (double *)calloc(g_bd.ps, sizeof(double))) == NULL) {
            for(j = i; j > 0; j--) {
                free(g_bd.btsp[j - 1]);
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
            for(j = i; j > 0; j--) {
                free(g_bd.bgd[j - 1]);
            }
            free(g_bd.bgd);
            oem("ag_bd", "Can't Allocate Memory (double *)bgd", 0);
        }
    }
    g_amc_f.f_bgd = ON;
}

void aig_p(void)
{
    int i, j;

    if((ig_p = (struct _individual_parameter *)malloc(sizeof(struct _individual_parameter) * g_bd.nth)) == NULL) {
        oem("aig_p", "Can't Allocate Memory ig_p", 0);
    }
    else {
        g_amc_f.f_ipm = ON;
    }

    for(i = 0; i < g_bd.nth; i++) {
        if((ig_p[i].csp = (int *)calloc(g_bd.ps, sizeof(int))) == NULL) {
            for(j = i; j > 0; j--) {
                free(ig_p[j - 1].csp);
            }
            oem("aig_p", "Can't Allocate Memory ig_p.csp", i);
        }
    }
    g_amc_f.f_ipm_csp = ON;

    for(i = 0; i < g_bd.nth; i++) {
        if((ig_p[i].bsp = (int *)calloc(g_bd.ps, sizeof(int))) == NULL) {
            for(j = i; j > 0; j--) {
                free(ig_p[j - 1].bsp);
            }
            oem("aig_p", "Can't Allocate Memory ig_p.bsp", i);
        }
    }
    g_amc_f.f_ipm_bsp = ON;

}

void fnyfp(void)
{
    int i;

    if(g_amc_f.f_btsp == ON) {
        free(g_bd.btsp);
        g_amc_f.f_btsp = OFF;
    }

    if(g_amc_f.f_bgd == ON) {
        free(g_bd.bgd);
        g_amc_f.f_bgd = OFF;
    }

    if(g_amc_f.f_ipm_csp == ON) {
        g_amc_f.f_ipm_csp = OFF;
    }

    if(g_amc_f.f_ipm_bsp == ON) {
        g_amc_f.f_ipm_bsp = OFF;
    }

    if(g_amc_f.f_to_tl == ON) {
        //free(g_tl.to_tl);
        g_amc_f.f_to_tl = OFF;
    }
#ifdef MPIMODE
    if(g_amc_f.f_bsp_mutex == ON) {
        free(g_bsp_mutex);
    }
#endif
    if(g_amc_f.f_MPI_sdp_sp == ON) {
        free(mpi_sdp.sp);
    }
}

void ma_tl(void)
{
    if((g_tl.to_tl = (int *)malloc(sizeof(int) * 4 * ig_p[0].stl)) == NULL) {
        oem("ma_tl", "Can't Allocate Memory", 0);
    }
    else {
        g_amc_f.f_to_tl = ON;
    }
}

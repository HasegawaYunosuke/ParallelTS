#include "header.h"

void ts_proc(int * npthr)
{
    int ccs[4] = {EMPTY}; /* Choiced Cities */
    int ccsi[4] = {EMPTY}; /* Choiced Cities Indexes */

    gminex_etb(ig_p[*npthr].csp, ccs, ccsi, npthr);
    ex_addtl(ig_p[*npthr].csp, ccs, ccsi, npthr);
    ig_p[*npthr].csd = gpd(ig_p[*npthr].csp, npthr);
    if(ig_p[*npthr].csd < ig_p[*npthr].bsd) {
        copyc_b(npthr);
    }
}

void gminex_etb(int * path, int * ccs, int * ccsi, int * npthr)
{
    int i, j, k;
    int t_ccs[4] = {EMPTY}; /* Temporary Choiced CitieS */
    int b_ccs[4] = {EMPTY}; /* Best Choiced CitieS */
    int h_ccs[4] = {EMPTY}; /* Have been Choiced CitieS */
    int hw_ccs[4] = {EMPTY}; /* Have been Choiced and Worse CitieS */
    int b_ccsi[4] = {EMPTY}; /* Best Choiced CitieS Indexes */
    int h_ccsi[4] = {EMPTY}; /* Have been Choiced CitieS Indexes */
    int hw_ccsi[4] = {EMPTY}; /* Have been Choiced and Worse CitieS Indexes */
    double bef, aft, diff;
    double b_diff = DBL_MAX; /* Best Difference (0 < is better, 0 > is worse) */
    double bbt_diff = DBL_MAX; /* Best, But Tabu Difference (0 < is better, 0 > is worse) */
    double bow_diff = DBL_MAX; /* Best, But Tabu Difference of Worse (0 < is better, 0 > is worse) */

    for(i = 0; i < g_bd.ps - 3; i++) {
        for(j = i + 2; j < g_bd.ps - 1; j++) {
            t_ccs[0] = path[i]; t_ccs[1] = path[i + 1]; /* Branch: A-A' */
            t_ccs[2] = path[j]; t_ccs[3] = path[j + 1]; /* Branch: B-B' */
            bef = g_bd.bgd[(t_ccs[0] - 1)][(t_ccs[1] - 1)] + g_bd.bgd[(t_ccs[2] - 1)][(t_ccs[3] - 1)];
            aft = g_bd.bgd[(t_ccs[0] - 1)][(t_ccs[2] - 1)] + g_bd.bgd[(t_ccs[1] - 1)][(t_ccs[3] - 1)];
            diff = aft - bef;
            if(diff < b_diff) {

                if(ch_tb(t_ccs) == NO) {
                    /* if Choiced Cities are NOT Tabu */
                    b_diff = diff;
                    if(b_diff < bbt_diff) {
                        bbt_diff = b_diff;
                        for(k = 0; k < 4; k++) {
                            b_ccs[k] = t_ccs[k];
                        }
                        b_ccsi[0] = i; b_ccsi[1] = i + 1;
                        b_ccsi[2] = j; b_ccsi[3] = j + 1;
                    }
                    /* if Choiced Cities are Tabu */
                }
                else {
                    /* Toward Better */
                    if(diff < 0) {
                        if(diff < bbt_diff) {
                            bbt_diff = diff;
                            for(k = 0; k < 4; k++) {
                                h_ccs[k] = t_ccs[k];
                            }
                        }
                        h_ccsi[0] = i; h_ccsi[1] = i + 1;
                        h_ccsi[2] = j; h_ccsi[3] = j + 1;
                    }
                    /* Toward Worse */
                    else {
                        if(diff < bow_diff) {
                            bow_diff = diff;
                            for(k = 0; k < 4; k++) {
                                hw_ccs[k] = t_ccs[k];
                            }
                        }
                        hw_ccsi[0] = i; hw_ccsi[1] = i + 1;
                        hw_ccsi[2] = j; hw_ccsi[3] = j + 1;
                    }
                }
            }
        }
    }

    if(b_ccs[0] != EMPTY && alw_wors(b_diff, npthr) == YES) {
        for(k = 0; k < 4; k++) {
            ccs[k] = b_ccs[k];
            ccsi[k] = b_ccsi[k];
        }
    }
    else if(h_ccs[0] != EMPTY) {
        for(k = 0; k < 4; k++) {
            ccs[k] = h_ccs[k];
            ccsi[k] = h_ccsi[k];
        }
    }
    else if(hw_ccs[0] != EMPTY){
        for(k = 0; k < 4; k++) {
            ccs[k] = hw_ccs[k];
            ccsi[k] = hw_ccsi[k];
        }
    }
    else {
        oem("gminex_etb", "Can't Choice Target Cities???", 0);
    }
}

void ex_addtl(int * path, int * ccs, int * ccsi, int * npthr)
{
    int i, sum = 0;
    int buf[g_bd.ps];

    /* Exchange */
    for(i = 0; i <= ccsi[0]; i++) {
        buf[i] = path[i];
    }
    for(i = ccsi[1]; i <= ccsi[2]; i++) {
        buf[(ccsi[2] - sum)] = path[i];
        sum++;
    }
    for(i = ccsi[3]; i < g_bd.ps; i++) {
        buf[i] = path[i];
    }
    for(i = 0; i < g_bd.ps; i++) {
        path[i] = buf[i];
    }

    /* Add Tabu List */
    pthread_mutex_lock(&g_tb_mutex);
    addtl(ccs, npthr);
    pthread_mutex_unlock(&g_tb_mutex);
}

int alw_wors(double b_diff, int * npthr)
{
    if(b_diff < 0) {
        return YES;
    }
    else {
        if(ig_p[*npthr].pw > (b_diff / ig_p[*npthr].bsd * 100)) {
            return YES;
        }
        else {
            return NO;
        }
    }
}

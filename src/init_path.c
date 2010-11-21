#include "header.h"

void initp(int * npthr)
{
    /* Rondom */
    if(g_bm.ipcm == DEFAULT) {
        cip_brn(npthr);
    }
    /* Nearest Neighbor */
    else if(g_bm.ipcm == TYPE1) {
        cip_bnn(npthr);
    }
}

void cip_brn(int * npthr)
{
    int i;
    int ci; /* Choiced Index */
    int ucf = -1; /* Used City Flag */
    int yet[g_bd.ps]; /* Not yet used Cities */
    double dis; /* All Distance of Current Sol-Path */

    for(i = 0; i < g_bd.ps; i++) {
        yet[i] = i + 1;
    }

    for(i = 0; i < g_bd.ps; i++) {
        ci = grn(g_bd.ps - i);
        ig_p[*npthr].csp[i] = yet[ci];
        cuc_pa(yet, (g_bd.ps - i), ci, ucf);
    }

    ig_p[*npthr].csd = gpd(ig_p[*npthr].csp, npthr);
}

void cuc_pa(int * ary, int max, int target, int flag)
{
    int i;

    for(i = target; i < max - 1; i++) {
        ary[i] = ary[i + 1];
    }
    ary[max - 1] = flag;
}

void cip_bnn(int * npthr)
{
    int i;
    int cc = grn(g_bd.ps) + 1; /* Choiced City */
    int ci; /* Choiced Index (at array:yet[]) */
    int ucf = -1; /* Used City Flag */
    int yet[g_bd.ps]; /* Not yet used Cities */
    double dis; /* All Distance of Current Sol-Path */

    for(i = 0; i < g_bd.ps; i++) {
        yet[i] = i + 1;
    }

    ig_p[*npthr].csp[0] = cc;
    cuc_pa(yet, g_bd.ps, cc - 1, ucf);

    for(i = 1; i < g_bd.ps; i++) {
        cc = gnc_eu(cc, yet, (g_bd.ps - i));
        ig_p[*npthr].csp[i] = cc;
        ci = guci_bc(cc, yet, (g_bd.ps - i));
        cuc_pa(yet, (g_bd.ps - i), ci, ucf);
    }

    ig_p[*npthr].csd = gpd(ig_p[*npthr].csp, npthr);
}

int gnc_eu(int sc, int * yet, int surplus)
{
    int eci; /* End City Index */
    int min_ci; /* Minimum City Index */
    double min = DBL_MAX;

    for(eci = 0; eci < g_bd.ps; eci++) {
        if(g_bd.bgd[sc - 1][eci] != 0.0 &&
            g_bd.bgd[sc - 1][eci] < min &&
                is_u(eci + 1, yet, surplus) == NO) {
            min = g_bd.bgd[sc - 1][eci];
            min_ci = eci;
        }
    }

    return (min_ci + 1);
}

int is_u(int city, int * ary, int max)
{
    int i;

    for(i = 0; i < max; i++) {
        if(ary[i] == city) {
            return NO;
        }
    }

    return YES;
}

int guci_bc(int city, int * ary, int max)
{
    int i;

    for(i = 0; i < max; i++) {
        if(ary[i] == city) {
            return i;
        }
    }

    oem("guci_bc", "Couldn't Find Out city", city);
}

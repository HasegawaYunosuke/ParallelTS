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

    for(i = 0; i < g_bd.ps; i++) {
        yet[i] = i + 1;
    }

    for(i = 0; i < g_bd.ps; i++) {
        ci = grn(g_bd.ps - i);
        ig_p[*npthr].csp[i] = yet[ci];
        cuc_pa(yet, (g_bd.ps - i), ci, ucf);
    }
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
}

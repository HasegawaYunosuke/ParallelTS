#include "header.h"

int ch_tb(int * ccs)
{
    int i, j;
    pthread_t pid[4];
    int ccs_c[4][5] = {{ccs[0],ccs[1],ccs[2],ccs[3], EMPTY},
                       {ccs[2],ccs[3],ccs[0],ccs[1], EMPTY},
                       {ccs[1],ccs[0],ccs[3],ccs[2], EMPTY},
                       {ccs[3],ccs[2],ccs[1],ccs[0], EMPTY}};

    for(i = 0; i < 4; i++) {
        ch_tb_c((void *)ccs_c[i]);
        if(ccs_c[i][4] == TIMEUP) {
            return TIMEUP;
        }
        else if(ccs_c[i][4] == YES) {
            return YES;
        }
    }

    return NO;
}

void * ch_tb_c(void * css)
{
    int i;

    for(i = 0; i < ig_p[0].stl; i++) {
        if(diff_t() > (double)g_bd.st) {
            ((int *)css)[4] = TIMEUP;
            break;
        }
        else if(g_tl.to_tl[4 * i] == EMPTY) {
            break;
        }
        else if(g_tl.to_tl[4 * i] == ((int *)css)[0]) {
            if(g_tl.to_tl[4 * i + 1] == ((int *)css)[1]) {
                if(g_tl.to_tl[4 * i + 2] == ((int *)css)[2]) {
                    if(g_tl.to_tl[4 * i + 3] == ((int *)css)[3]) {
                        ((int *)css)[4] = YES;
                        break;
                    }
                }
            }
        }
    }
}

void addtl(int * ccs, int * npthr)
{
    if(diff_t() < (double)g_bd.st) {
        g_tl.to_tl[4 * g_tli + 0] = ccs[0];
        g_tl.to_tl[4 * g_tli + 1] = ccs[2];
        g_tl.to_tl[4 * g_tli + 2] = ccs[1];
        g_tl.to_tl[4 * g_tli + 3] = ccs[3];

        if(g_tli < ig_p[*npthr].stl - 1) {
            g_tli = g_tli + 1;
        }
        else {
            g_tli = 0;
        }

        if(diff_t() < (double)g_bd.st) {
            g_tl.to_tl[4 * g_tli + 0] = ccs[0];
            g_tl.to_tl[4 * g_tli + 1] = ccs[1];
            g_tl.to_tl[4 * g_tli + 2] = ccs[2];
            g_tl.to_tl[4 * g_tli + 3] = ccs[3];

            if(g_tli < ig_p[*npthr].stl - 1) {
                g_tli = g_tli + 1;
            }
            else {
                g_tli = 0;
            }
        }
    }
}

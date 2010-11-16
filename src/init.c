#include "header.h"

void init(int argc, char **argv)
{
    /* Memory Flag Initialize */
    ffi();
    /* Command Line Argument Error Check */
    cif(argc, argv);
    /* Command Line Input File Management */
    mif(argc, argv);
    /* Memory Allocation about "struct g_bd" */
    ag_bd();
    /* Read TSPLIB's Problems & Store Data & Make Glaph Data */
    mtsplib();
    /* First Initialization of All Data */
    fiad();
}

void fiad(void)
{
    int i;

    for(i = 0; i < g_bd.nth; i++) {
        ig_p[i].csd = DBL_MAX;
        ig_p[i].bsd = DBL_MAX;
        ig_p[i].clt = 0;
    }
}

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
    /* Memory Allocation about "struct tblist" */
    ma_tl();
    /* Read TSPLIB's Problems & Store Data & Make Glaph Data */
    mtsplib();
    /* First Initialization of All Data */
    fiad();
    /* Get Best Solution By Problem-Name */
    gbs_bpn();
#ifdef MPIMODE
    /* MPI Initialize Procedure*/
    mpi_ip(argc, argv);
#endif
}

void fiad(void)
{
    int i;

    for(i = 0; i < g_bd.nth; i++) {
        ig_p[i].csd = DBL_MAX;
        ig_p[i].bsd = DBL_MAX;
        ig_p[i].clt = 0;
    }

    g_bd.mpi_id = 0;

    for(i = 0; i < ig_p[0].stl; i++) {
        g_tl.to_tl[i * 4 + 0] = EMPTY;
        g_tl.to_tl[i * 4 + 1] = EMPTY;
        g_tl.to_tl[i * 4 + 2] = EMPTY;
        g_tl.to_tl[i * 4 + 3] = EMPTY;
    }

    g_tli = 0;
}

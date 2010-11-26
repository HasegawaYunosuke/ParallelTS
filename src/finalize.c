#include "header.h"

void fin(void)
{
    out_r();
    fnyfp();
#ifdef MPIMODE
    mpi_fin();
    printf("Tabu Search Program at Node %d is normally terminated...\n", g_bd.mpi_id);
#endif
}

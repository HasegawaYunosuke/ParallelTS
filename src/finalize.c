#include "header.h"

void fin(void)
{
    out_r();
    fnyfp();
#ifdef MPIMODE
    mpi_fin();
#endif
}

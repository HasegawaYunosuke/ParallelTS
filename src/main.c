#include "header.h"

int main(int argc, char **argv)
{
    init(argc, argv);
    ptp();
#ifdef MPIMODE
    mpi_test();
#endif
#ifdef DEBUG1
    printf("DEBUG TEST\n");
#endif
    fin();
}

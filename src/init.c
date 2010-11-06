#include "header.h"

void init(int argc, char **argv)
{
    ffi();
    cif(argc, argv);
    aig_p();
    mif(argc, argv);
    ag_bd();
    mtsplib();
}

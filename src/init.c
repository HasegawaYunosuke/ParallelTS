#include "header.h"

void init(int argc, char **argv)
{
    ffi();
    cif(argc, argv);
    mif(argc, argv);
    abmem();
    mtsplib();
}

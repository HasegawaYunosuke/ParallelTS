#include "header.h"

int main(int argc, char **argv)
{
    init(argc, argv);
    st_t();
    ptp();
#ifdef DEBUG1
    printf("DEBUG TEST\n");
#endif
    fin();

    return 0;
}

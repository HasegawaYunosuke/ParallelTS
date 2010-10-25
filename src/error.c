#include "header.h"

void oem(char func[32], char ms[64], int da)
{
    printf("Program is terminated At \'%s()\'\n", func);
    printf("\tError-Message: %s\n", ms);

    if(da != 0) {
        printf("\tError Number:%d\n", da);
    }

    exit(1);
}

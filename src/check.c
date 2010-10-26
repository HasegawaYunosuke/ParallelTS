#include "header.h"

void cif(int argc, char **argv)
{
    if(argc != 2) {
        oem("cif", "Wrong Number of Command-Line-Argument", argc);
    }
}

void cnd(char dn[32])
{
    DIR * dp;
    char ms[32]; /* Message */

    if((dp = opendir(dn)) == NULL) {
        sprintf(ms, "Can't Find \"%s\" Directory", dn);
        oem("cif", ms, 0);
    }
    else {
        closedir(dp);
    }
}

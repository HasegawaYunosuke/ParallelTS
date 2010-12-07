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

int csac(int * path)
{
    int i, j;
    int sum = 0;

    for(i = 0; i < g_bd.ps; i++) {
        for(j = 0; j < g_bd.ps; j++) {
            if(path[j] == (i + 1)) {
                sum++;
                break;
            }
        }
    }

    if(sum == g_bd.ps) {
        return YES;
    }
    else {
        return NO;
    }
}

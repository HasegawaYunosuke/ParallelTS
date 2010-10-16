#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int argc, char **argv); /*Initialize*/
void cif(int argc, char **argv); /*Check Input-Files*/
void mif(int argc, char **argv); /*Management Input-File*/

#ifdef MPIMODE
void mpi_test(void);
#endif

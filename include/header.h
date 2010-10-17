#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int argc, char **argv); /*Initialize*/
void cif(int argc, char **argv); /*Check Input-Files*/
void mif(int argc, char **argv); /*Management Input-File*/
void rfop(char ** argv, FILE * rfp); /* Readonly-File Open */
void rif_sd(FILE * rfp); /* Read Input-File & Store Data */

#ifdef MPIMODE
void mpi_test(void);
#endif

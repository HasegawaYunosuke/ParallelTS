#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int argc, char **argv); /*Initialize*/
    void cif(int argc, char **argv); /*Check Input-Files*/
    void mif(int argc, char **argv); /*Management Input-File*/
        FILE * rfop(char ** argv); /* Readonly-File Open */
        void rif_sd(FILE * rfp); /* Read Input-File & Store Data */
            void arld(char * rld, int li); /* Analysis Read-Line-Data */
                void itpn(char * rld); /* Input TSPLIB's problem name */
                    int gdbl(char * rld); /* Get Data Boundary-Line */
                    int gdnu(char * rld, int di); /* Get Data Number */
                    void gdna(char * rld, int di, char * pn); /* Get Data Name */
                void ssti(char * rld); /* Set Search Time */
                void smcm(char * rld); /* Set Multi-core Mode */
                    int gonoff(char * rld, int di); /* Get ON or OFF */
                void smpim(char * rld); /* Set MPI Mode */

#ifdef MPIMODE
void mpi_test(void);
#endif

#define YES 1
#define ON 1
#define NO 0
#define OFF 0

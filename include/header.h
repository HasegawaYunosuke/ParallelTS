#include "define.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>

void init(int argc, char **argv); /* Initialize */
    void ffi(void); /* First Flag Initialize */
    void cif(int argc, char **argv); /* Check Input-Files */
        void oem(char func[32], char ms[64], int da); /* Output Error Message */
            void fnyfp(void); /* Free Not Yet Freed Pointer */
    void aig_p(void); /* Allocate Individual Global Pointer */
    void mif(int argc, char **argv); /* Management Input-File */
        void cnd(char dn[32]); /* Check Necessary Directory */
        FILE * rfop(char * argv, char bfn[32]); /* Readonly-File Open */
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
                void wtres(char * rld); /* What type of result do you use ? */
                void gdld1(char * rld); /* Get Debug-Log-Data:type1 */
                void gdld2(char * rld); /* Get Debug-Log-Data:type2 */
                void gdld3(char * rld); /* Get Debug-Log-Data:type3 */
                void gdld4(char * rld); /* Get Debug-Log-Data:type4 */
                void gpnth(char * rld); /* Get Parameter: Number of Thread */
                void gppw(char * rld); /* Get Parameter: Percentage toward Worse */
                void gplw(char * rld); /* Get Parameter: Loop times toward Worse */
                    int gnxn(int di, char * rld); /* Get [Number] * [N(ex:tsp-size)] */
                void gplt(char * rld); /* Get Parameter: Loop times */
                void gpst(char * rld); /* Get Parameter: Size of Tabu-list */
                void gptt(char * rld); /* Get Parameter: Term of Tabu-list */
    void ag_bd(void); /* Allocate Global-Base-Data */
    void spara(void); /* Set Parameter data */
    void mtsplib(void); /* Management TSPLIB's Sample Problems */
        void rtsplib_sd(FILE * rfp); /* Read TSPLIB's problems & Store Data */
            void artsplibld(char * rld, int dli); /* Analysis Read TSPLIB's Line-Data */
                void mychmp(char * buf, char * mychmpbuf); /* My Chomp */
        void sgd(void); /* Store Graph Data */
            double dif_2p(double x1, double y1, double x2, double y2); /* Difference between 2-Point */
void fin(void); /* Finalize */
    void faam(void); /* Free All-Allocated Memory */
        void fg_bd(void); /* Free Global-Base-Data */
        void fig_p(void); /* Free Initialize Global Parameter */

#ifdef MPIMODE
void mpi_test(void);
#endif

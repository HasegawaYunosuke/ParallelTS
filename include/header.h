#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>
#include "define.h"
#include "globals.h"
#ifdef MPIMODE
#include "mpi.h"
#endif

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
                void ipcm(char * rld); /*  Initial Path Creating Mode */
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
    void ag_bd(void); /* Allocate Global-Base-Data */
    void spara(void); /* Set Parameter data */
    void ma_tl(void); /* Memory Allocation about "struct tblist" */
    void mtsplib(void); /* Management TSPLIB's Sample Problems */
        void rtsplib_sd(FILE * rfp); /* Read TSPLIB's problems & Store Data */
            void artsplibld(char * rld, int dli); /* Analysis Read TSPLIB's Line-Data */
                void mychmp(char * buf, char * mychmpbuf); /* My Chomp */
        void sgd(void); /* Store Graph Data */
            double dif_2p(double x1, double y1, double x2, double y2); /* Difference between 2-Point */
    void fiad(void); /* First Initialization of All Data */
    void gbs_bpn(void); /* Get Best Solution By Problem-Name */
void st_t(void); /* Start Timer */
void ptp(void); /* pthread_Procedure */
                    double diff_t(void); /* Difference of Time (How Long the Search start) */
    void * threp(void * arg); /* Thread Procedure */
        void initp(int * npthr); /* Initialize Path */
            void cip_brn(int * npthr); /* Create Initial-Path By Random */
                int grn(int max); /* Get Random Number */
                void cuc_pa(int * ary, int target, int max, int flag); /* Check Used-City and Plug Array */
                double gpd(int * path, int * npthr); /* Locked:Get Path-Distance */
                void copyc_b(int * npthr); /* Copy Current Solution Path & Data as the Best Solution */
            void cip_bnn(int * npthr); /* Create Initial-Path By Nearest Neighbor */
                int gnc_eu(int sc, int * yet, int surplus); /* Get Nearest City Except Used Cities */
                    int is_u(int city, int * ary, int max); /* Is This Used City? (return YES/NO) */
                int guci_bc(int city, int * ary, int max); /* Get Used City Index By City */
        void ts_proc(int * arg); /* Tabu Search Procedure */
            void gminex_etb(int * path, int * ccs, int * ccsi, int * npthr); /* Get Minimum Exchange Except Tabu */
                int ch_tb(int * ccs); /* Check Tabu (return YES/NO) */
                    void * ch_tb_c(void * ccs); /* Check Tabu Child Function */
                int alw_wors(double b_diff, int * npthr); /* Allow exchanging toword Worse */
            void ex_addtl(int * path, int * ccs, int * ccsi, int * npthr); /* Exchange Branches and Add Tabu List */
                void addtl(int * ccs, int * npthr); /* Add Tabu List) */
void fin(void); /* Finalize */
    void out_r(void); /* Out-Put Result */
        FILE * wfop(char * argv, char bfn[32]); /* Write File Open */
        void pres(FILE * resfp); /* Printout Result */
    void fnyfp(void); /* Free Not Yet Freed Pointer */
#ifdef MPIMODE
void mpi_test(void);
void mpi_ip(int argc, char **argv); /* MPI Initialize Procedure */
void mpi_fin(void); /* MPI Finalize Procedure */
void mpi_pres(FILE * wfd, double * rd, int size);
#endif

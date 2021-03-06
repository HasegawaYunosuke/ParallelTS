#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>
#include <limits.h>
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
                void gpncp(char * rld); /* Get Parameter: Number of Cut-Point (For GA) */
                void gptcp(char * rld); /* Get Parameter: Type of Cut-Point (For GA) */
                void gptGA(char * rld); /* Get Parameter: Type of GA */
                void gpnGAsm(char * rld); /* Get Parameter: Number of GA's Swap-Mutation */
                void gptGAsm(char * rld); /* Get Parameter: Type of GA's Swap-Mutation */
                void gpuhd4GAsm(char * rld); /* Get Parameter: Upper Humming-Distance for GA's Swap-Mutation [%] */
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
    void deb_init(void); /* Debug Initialize */
        void ddeb_lfn(void); /* Decide Debug Log-File-Name */
void st_t(void); /* Start Timer */
void ptp(void); /* pthread_Procedure */
                    double diff_t(void); /* Difference of Time (How Long the Search start) */
                        void * dld1func(void * temp_rn);
                            void odld1(FILE * fdp, double rn);
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

int csac(int * path); /* Check Sol-Path's Accuracy */

#ifdef MPIMODE
void mpi_test(void);
void mpi_ip(int argc, char **argv); /* MPI Initialize Procedure */
void mpi_fin(void); /* MPI Finalize Procedure */
void mpi_want(int npthr); /* Want to Gather other Solutions for GA Procedure */
void * mpi_recvp(void * arg); /* MPI_Recv Procedure */
void mpi_pres(FILE * wfd, double * rd, int size);
void ga_proc(int * pthr); /* GA Pcoredure */
void * cpthr4gp(void * arg); /* Child Pthread for MPI_Gather() Procedure */
void * cpthr4gp(void * arg); /* GA Procedure */
void pre_gacp(int pthr, int * sols, int * mysol); /* Previous of GA: Copy Procedure */
int gp4ga_bhd(int pthr, int * sols, int * mysol); /* Get Parent for GA Procedure By Humming Distance */
int gp4ga_br(int pthr, int * sols, int * mysol); /* Get Parent for GA Procedure By Random */
void crossov(int pthr, int * sols, int * mysol, int cpi_ap); /* Cross Over */
    int dns(void); /* Dicide Number of Swap */
    void rand_sm(int * pthr); /* Random Swap Mutation */
    void srand_sm(int * pthr); /* Smart Random Swap Mutation */
    void ccp_br(int * cpi, int pthr); /* Choice Cut-Point By Random */
    void ccp_bndp(int * cpi, int pthr, int * mysol, int * othersol); /* Choice Cut-Point By Non-Double Point */
    void pm_crossov(int * cpi, int * opsol, int * mysol, int pthr); /* Partially Matched Crossover */
    void od_crossov(int * cpi, int * parent2, int * parent1, int pthr); /* Order Clossover */
        void cbc_bcpi(int * cpi, int * child, int * parent1, int * parent2, int pthr); /* Create Base Cities by cpi[] */
        void od_crosovp(int * cpi, int * child, int * parent1, int * parent2, int pthr); /* Oder Crossover Procedure */
void cp_p2sol(int cpi_ap, int * sols, int * mysol); /* Coordinate Path Parent-2 Solution path */
    void sdpcs(int * mysol, int * p4w, int * dp1, int * dp2); /* Set Dupplex Point Check Sheets */
    int gstedpis_ndp(int * dp, int * stedpis, int pthr); /* Get Start & End Point Indexes:Non-Duplex-Points */
    int gstedpis_dp(int * dp, int * stedpis, int pthr); /* Get Start & End Point Indexes:Non-Duplex-Points */
void proc_rGA(void * arg); /* Procedure related GA */
void set_pn(char * parameters); /* Set Parameter-Name */
int chman(int pthr); /* Check Manneri */
#endif

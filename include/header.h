#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int argc, char **argv); /* Initialize */
    void cif(int argc, char **argv); /* Check Input-Files */
        void oem(char func[32], char ms[64], int da); /* Output Error Message */
    void mif(int argc, char **argv); /* Management Input-File */
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
                void wtres(char * rld); /* What type of result do you use ? */
                void gdld1(char * rld); /* Get Debug-Log-Data:type1 */
                void gdld2(char * rld); /* Get Debug-Log-Data:type2 */
                void gdld3(char * rld); /* Get Debug-Log-Data:type3 */
                void gdld4(char * rld); /* Get Debug-Log-Data:type4 */
                void gppw(char * rld); /* Get Parameter: Percentage toward Worse */
                void gplw(char * rld); /* Get Parameter: Loop times toward Worse */
                    int gnxn(int di, char * rld); /* Get [Number] * [N(ex:tsp-size)] */
                void gplt(char * rld); /* Get Parameter: Loop times */
                void gpst(char * rld); /* Get Parameter: Size of Tabu-list */
                void gptt(char * rld); /* Get Parameter: Term of Tabu-list */

#ifdef MPIMODE
void mpi_test(void);
#endif

/* YES/NO ON/OFF */
#define YES 1
#define ON 1
#define NO 0
#define OFF 0

/* Case Devide */
#define DEFAULT 0
#define TYPE1 1
#define TYPE2 2
#define TYPE3 3
#define TYPE4 4
#define TYPE5 5

struct _base_data {
    char pn[64]; /* Problem Name */
    int ps; /* Problem Size */
    int st; /* Search Time */
};

struct _base_mode {
    int mcm; /* Multi-core MODE (ON/OFF) */
    int mpim; /* MPI MODE (ON/OFF) */
    int tres; /* Type of Result MODE (DEFAULT/TYPE1~5) */
    int dld1; /* Debug-Log-Data:type1 (ON/OFF) */
    int dld2; /* Debug-Log-Data:type2 (ON/OFF) */
    int dld3; /* Debug-Log-Data:type3 (ON/OFF) */
    int dld4; /* Debug-Log-Data:type4 (ON/OFF) */
};

struct _individual_parameter {
    double ppw; /* Percentage toward Worse */
    int lw; /* Loop times toward Worse */
    int lt; /* Loop times */
    int stl; /* Size of Tabu-List */
    int ttl; /* Term of Tabu-List */
};

/* Global struct data */
struct _base_data g_bd; /* Global Base Data */
struct _base_mode g_bm; /* Global Base Mode */

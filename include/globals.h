struct _base_data {
    char pn[64]; /* Problem Name */
    int ps; /* Problem Size */
    int st; /* Search Time */
    int nth; /* Number of Thread */
    double kn_bs; /* Known Best Solution */
    double ** btsp; /* Base TSPLIB's x-y Data */
    double ** bgd; /* Base Graph Data */

    int mpi_id; /* If Use MPI, It's ID. If Don't Use MPI, It's "EMPTY" */
    int np_ae; /* If Use MPI, It's Number of Processer at the Environment */
    int mpi_nl; /* If Use MPI, It's MPI Name Length */
    char * id_name; /* If Use MPI, It's MPI Name */
};

struct _base_mode {
    int mcm; /* Multi-core MODE (ON/OFF) */
    int mpim; /* MPI MODE (ON/OFF) */
    int tres; /* Type of Result MODE (DEFAULT/TYPE1~5) */
    int ipcm; /* Initial Path Creating Mode (DEFAULT/TYPE1) */
    int dld1; /* Debug-Log-Data:type1 (ON/OFF) */
    int dld2; /* Debug-Log-Data:type2 (ON/OFF) */
    int dld3; /* Debug-Log-Data:type3 (ON/OFF) */
    int dld4; /* Debug-Log-Data:type4 (ON/OFF) */
};

struct _individual_parameter {
    double pw; /* Percentage toward Worse (Previously Setting) */
    int lw; /* Loop times toward Worse (Previously Setting) */
    int lt; /* Loop times (Previously Setting) */
    int clt; /* Current Loop times */
    int stl; /* Size of Tabu-List (Previously Setting) */
    pthread_t ptn; /* pthread Number */
    int * csp; /* Current Solution Path */
    double csd; /* Current Solution Distance */
    int * bsp; /* Best Solution Path */
    double bsd; /* Best Solution Distance */
};

struct _tabu_list {
    int * to_tl; /* 2-opt Tabu List */
};

struct _allocate_memory_check_flag {
    int f_btsp; /* Flag of "struct _base_data" */
    int f_bgd; /* Flag of "struct _base_mode" */
    int f_ipm; /* Flag of "struct _individual_parameter"'s memory */
    int f_ipm_csp; /* Flag of "struct _individual_parameter"'s member "csp:Current Solution Path"'s memory */
    int f_ipm_bsp; /* Flag of "struct _individual_parameter"'s member "csp:Current Solution Path"'s memory */
    int f_to_tl; /* Flag of "struct _tabu_list"'s to_tl */
};

/* Global struct data */
struct _base_data g_bd; /* Global Base Data */
struct _base_mode g_bm; /* Global Base Mode */
struct _individual_parameter * ig_p; /* Individual Global Parameter */
struct _allocate_memory_check_flag g_amc_f; /* Global "_allocate_memory_check_flag" */
struct _tabu_list g_tl; /* Global Tabu List */

/* Global variable data */
int g_tli; /* Global Tabu List Index */
int timerf;

/* Global Mutex */
pthread_mutex_t g_tb_mutex; /* Global Tabu Mutex */

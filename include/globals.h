struct _base_data {
    char pn[64]; /* Problem Name */
    int ps; /* Problem Size */
    int st; /* Search Time */
    int nth; /* Number of Thread */
    double ** btsp; /* Base TSPLIB's x-y Data */
    double ** bgd; /* Base Graph Data */
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
    double pw; /* Percentage toward Worse (Previously Setting) */
    int lw; /* Loop times toward Worse (Previously Setting) */
    int lt; /* Loop times (Previously Setting) */
    int clt; /* Current Loop times */
    int stl; /* Size of Tabu-List (Previously Setting) */
    int ttl; /* Term of Tabu-List (Previously Setting) */
    pthread_t ptn; /* pthread Number */
    int * csp; /* Current Solution Path */
    double csd; /* Current Solution Distance */
    int * bsp; /* Best Solution Path */
    double bsd; /* Best Solution Distance */
};

struct _allocate_memory_check_flag {
    int f_btsp; /* Flag of "struct _base_data" */
    int f_bgd; /* Flag of "struct _base_mode" */
    int f_ipm; /* Flag of "struct _individual_parameter"'s memory */
    int f_ipm_csp; /* Flag of "struct _individual_parameter"'s member "csp:Current Solution Path"'s memory */
    int f_ipm_bsp; /* Flag of "struct _individual_parameter"'s member "csp:Current Solution Path"'s memory */
};

/* Global struct data */
struct _base_data g_bd; /* Global Base Data */
struct _base_mode g_bm; /* Global Base Mode */
struct _individual_parameter * ig_p; /* Individual Global Parameter */
struct _allocate_memory_check_flag g_amc_f; /* Global "_allocate_memory_check_flag" */

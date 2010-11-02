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
    double pw; /* Percentage toward Worse */
    int lw; /* Loop times toward Worse */
    int lt; /* Loop times */
    int stl; /* Size of Tabu-List */
    int ttl; /* Term of Tabu-List */
};

/* Global struct data */
struct _base_data g_bd; /* Global Base Data */
struct _base_mode g_bm; /* Global Base Mode */

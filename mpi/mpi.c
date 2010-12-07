#include "header.h"

void mpi_test(void)
{
    printf("MPI TEST\n");
}

void mpi_ip(int argc, char **argv)
{
    int i;
    int np_ae; /* Number of Processer at the Environment */
    int mpi_id; /* Myself MPI ID */
    int nl; /* Name Length */
    char id_name[MPI_MAX_PROCESSOR_NAME]; /* Processer Name */
    int arg = 0; /* Is This Necessary??? */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np_ae);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_id);
    MPI_Get_processor_name(id_name, &nl);

    g_bd.np_ae = np_ae;
    g_bd.mpi_id = mpi_id;
    g_bd.mpi_nl = nl;
    g_bd.id_name = (char *)malloc(sizeof(char) * MPI_MAX_PROCESSOR_NAME);
    strcpy(g_bd.id_name, id_name);

    if((g_bsp_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_bd.nth)) != NULL) {
        g_amc_f.f_bsp_mutex = ON;
    }
    else {
        oem("mpi_ip", "Can't Allocate Memory of \"g_bsp_mutex\"", 0);
    }

    if((mpi_sdp_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_bd.np_ae)) != NULL) {
        g_amc_f.f_MPI_sdp_mutex = ON;
    }
    else {
        oem("mpi_ip", "Can't Allocate Memory of \"mpi_sdp_mutex\"", 0);
    }

    if((mpi_sdp.sp = (int *)malloc(sizeof(int) * g_bd.np_ae * g_bd.ps)) != NULL) {
        g_amc_f.f_MPI_sdp_sp = ON;
    }
    else {
        oem("mpi_ip", "Can't Allocate Memory of \"mpi_sdp.sp\"", 0);
    }

    for(i = 0; i < g_bd.nth; i++) {
        pthread_mutex_init(&g_bsp_mutex[i], NULL);
    }

    for(i = 0; i < g_bd.np_ae; i++) {
        pthread_mutex_init(&mpi_sdp_mutex[i], NULL);
    }

    /* Only Recv Thread */
    if(g_bm.mpim == ON) {
        pthread_mutex_init(&g_send_mutex, NULL);
        pthread_create(&g_recv_pth, NULL, mpi_recvp, (void *)&arg);
    }
}

void * mpi_recvp(void * arg)
{
    MPI_Status stat;
    int i;
    int rbf = OFF; /* Recv Buffer Flag */
    int nrecv = 1; /* Number of Recv Element */
    pthread_t cpthr4gathr[g_bd.np_ae]; /* Child Pthread for MPI_Gather() */
    int rbuf4tpc[nrecv]; /* Recv Buffer for Target PC */

    g_bm.mpi_recvsw = ON;

    for(;;) {
        pthread_testcancel();
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_SEND_WANT, MPI_COMM_WORLD, &rbf, &stat);
        if(rbf == ON) {
            pthread_testcancel();
            MPI_Recv(rbuf4tpc, nrecv, MPI_INT, MPI_ANY_SOURCE, MPI_SEND_WANT, MPI_COMM_WORLD, &stat);
            pthread_create(&cpthr4gathr[(rbuf4tpc[0])],NULL, cpthr4gp, (void *)rbuf4tpc);
        }
        pthread_testcancel();
        usleep(100000);
    }
}

void * cpthr4gp(void * arg)
{
    double temp = DBL_MAX;
    int i, rbuf4tpc = *(int *)arg; /* Recv Buffer for Target PC */
    int bsd_pthr; /* Best Solution Distance Pthread */
    int rbuf4sol[(g_bd.ps * g_bd.np_ae)]; /* Recv Buffer for Gater Solution */
    int sbuf[g_bd.ps];

    /* Choice the Best Solution of All Thread */
    for(i = 0; i < g_bd.nth; i++) {
        if(ig_p[i].bsd < temp) {
            bsd_pthr = i;
            temp = ig_p[i].bsd;
        }
    }
    g_bd.mpi_bsd_pthr = bsd_pthr;

    /* Set Send Data */
    pthread_mutex_lock(&g_bsp_mutex[g_bd.mpi_bsd_pthr]);
    for(i = 0; i < g_bd.ps; i++) {
        sbuf[i] = ig_p[g_bd.mpi_bsd_pthr].bsp[i];
    }
    pthread_mutex_unlock(&g_bsp_mutex[g_bd.mpi_bsd_pthr]);

    /* Check Sol-Path's Accuracy */
    if(csac(sbuf) != YES) {
        oem("cpthr4gp", "Detected Un-Collect Solution-Path Before MPI_Gather()'s Send", 0);
    }

    /* Send the Best Solution of All Thread to Root PC:rbuf4tpc */
    MPI_Gather(sbuf, g_bd.ps, MPI_INT, rbuf4sol, g_bd.ps, MPI_INT, rbuf4tpc, MPI_COMM_WORLD);

    pthread_exit(NULL);
}

void mpi_want(int npthr)
{
    int i, j;
    int snode; /* Send Node */
    int nsend = g_bd.ps; /* Number of Send Element */
    int rbuf4sol[(nsend * g_bd.np_ae)]; /* Recv Buffer for Gater Solution */
    int sbuf[nsend];

    /* Copy the Best Solution Path to Send Data Buffer (Locked) */
    pthread_mutex_lock(&g_bsp_mutex[g_bd.mpi_bsd_pthr]);
    for(i = 0; i < g_bd.ps; i++) {
        sbuf[i] = ig_p[g_bd.mpi_bsd_pthr].bsp[i];
    }
    pthread_mutex_unlock(&g_bsp_mutex[g_bd.mpi_bsd_pthr]);

    if(diff_t() < (double)(g_bd.st - 10)) {
        for(snode = 0; snode < g_bd.np_ae; snode++) {
            if(snode != g_bd.mpi_id) {
                MPI_Send(&g_bd.mpi_id, 1, MPI_INT, snode, MPI_SEND_WANT, MPI_COMM_WORLD);
            }
        }
        /* Recv Solutions From all of Other PC */
        MPI_Gather(sbuf, nsend, MPI_INT, rbuf4sol, nsend, MPI_INT, g_bd.mpi_id, MPI_COMM_WORLD);
        /*DEL*/printf("Send By %d-%d\n", g_bd.mpi_id, npthr);
    }

    /* Store Gatered Data to "struct _mpi_shared_data_pool" */
    for(i = 0; i < g_bd.np_ae; i++) {
        if(diff_t() < (double)(g_bd.st - 10)) {
            pthread_mutex_lock(&mpi_sdp_mutex[i]);
            for(j = 0; j < g_bd.ps; j++) {
                mpi_sdp.sp[i * g_bd.ps + j] = rbuf4sol[i * g_bd.ps + j];
            }
            pthread_mutex_unlock(&mpi_sdp_mutex[i]);
        }
        else {
            break;
        }
    }
}

void ga_proc(int * pthr)
{
    int i, j;
    int sols[(g_bd.ps * g_bd.np_ae)]; /* Recv Buffer for Gater Solution */
    int mysol[g_bd.ps];
    int cpi_ap; /* Choiced Path-Index as one of the Parent */

    /* Set Data */
    pre_gacp(*pthr, sols, mysol);
    cpi_ap = gp4ga_bhd(*pthr, sols, mysol);
    //cp_p2sol(cpi_ap, sols, mysol);
    if(cpi_ap != TIMEUP && cpi_ap != EMPTY) {
        crossov(*pthr, sols, mysol, cpi_ap);
    }
}

void cp_p2sol(int cpi_ap, int * sols, int * mysol)
{
    int i, j; /* Current City, Next City */
    int p4w[g_bd.ps]; /* Path for Work */
    int dp1[g_bd.ps]; /* Duplex Point */
    int dp2[g_bd.ps]; /* Duplex Point */

    /* Initialize Data */
    for(i = 0; i < g_bd.ps; i++) {
        dp1[i] = EMPTY;
        dp2[i] = EMPTY;
        p4w[i] = sols[cpi_ap * g_bd.ps + i];
    }

    /* Set Dupplex Point Check Sheets */
    sdpcs(mysol, p4w, dp1, dp2);

    /*DEL*/
    if(g_bd.mpi_id == 0 && pthread_equal(pthread_self(), ig_p[0].ptn)) {
        printf("cpi_ap == %d\n", cpi_ap);

        for(i = 0; i < g_bd.ps; i++) {
            if(i != (g_bd.ps - 1)) {
                if(dp1[i] == ON) {
                    printf("*");
                }
                else {
                    printf("-");
                }
            }
            else {
                if(dp1[i] == ON) {
                    printf("*\n");
                }
                else {
                    printf("-\n");
                }
            }
        }
        for(i = 0; i < g_bd.ps; i++) {
            if(i != (g_bd.ps - 1)) {
                if(dp2[i] == ON) {
                    printf("*");
                }
                else {
                    printf("-");
                }
            }
            else {
                if(dp2[i] == ON) {
                    printf("*\n");
                }
                else {
                    printf("-\n");
                }
            }
        }
        for(i = 0; i < g_bd.ps; i++) {
            if(i != (g_bd.ps - 1)) {
                printf("%2d,", mysol[i]);
            }
            else {
                printf("%2d\n", mysol[i]);
            }
        }
        for(i = 0; i < g_bd.ps; i++) {
            if(i != (g_bd.ps - 1)) {
                printf("%2d,", p4w[i]);
            }
            else {
                printf("%2d\n", p4w[i]);
            }
        }
    }
    /*DEL*/
}
void sdpcs(int * mysol, int * p4w, int * dp1, int * dp2)
{
    int i, j, cc, nc;

    for(i = 0; i < g_bd.ps; i++) {
        /* Set Current & Next City */
        if(i != (g_bd.ps - 1)) {
            cc = mysol[i]; nc = mysol[(i + 1)];
        }
        else {
            cc = mysol[i]; nc = mysol[0];
        }

        /* Mutching */
        for(j = 0; j < g_bd.ps; j++) {
            if(p4w[j] == cc) {
                if(j == 0) {
                    if(p4w[(g_bd.ps - 1)] == nc || p4w[1] == nc) {
                        dp1[i] = ON; dp2[j] = ON;
                    }
                }
                else if(j == (g_bd.ps - 1)) {
                    if(p4w[(g_bd.ps - 2)] == nc || p4w[0] == nc) {
                        dp1[i] = ON; dp2[j] = ON;
                    }
                }
                else {
                    if(p4w[(j - 1)] == nc || p4w[(j + 1)] == nc) {
                        dp1[i] = ON; dp2[j] = ON;
                    }
                }
                break;
            }
        }
    }
}

void pre_gacp(int pthr, int * sols, int * mysol)
{
    int i, j;
    int ta[g_bd.ps]; /* Temporary Arrary */

    if(diff_t() < (double)(g_bd.st)) {
        pthread_mutex_lock(&g_bsp_mutex[pthr]);
        for(i = 0; i < g_bd.ps; i++) {
            mysol[i] = ig_p[pthr].bsp[i];
        }
        pthread_mutex_unlock(&g_bsp_mutex[pthr]);
    }

    for(i = 0; i < g_bd.np_ae; i++) {
        if(diff_t() < (double)(g_bd.st)) {
            pthread_mutex_lock(&mpi_sdp_mutex[i]);
            for(j = 0; j < g_bd.ps; j++) {
                ta[j] = mpi_sdp.sp[(i * g_bd.ps + j)];
            }
            pthread_mutex_unlock(&mpi_sdp_mutex[i]);

            /* Check Recved Array's Accuracy */
            if(csac(ta) == YES) {
                for(j = 0; j < g_bd.ps; j++) {
                    sols[(i * g_bd.ps + j)] = ta[j];
                }
            }
            else {
                for(j = 0; j < g_bd.ps; j++) {
                    sols[(i * g_bd.ps + j)] = EMPTY;
                }
            }
        }
        else {
            break;
        }
    }
}

int gp4ga_bhd(int pthr, int * sols, int * mysol)
{
    int i, j, k;
    int cc, nc; /* Current, Next City */
    int sum = 0;
    int asum = 0;
    int nusol = 0;
    int cii = 0; /* Choiced INdexes's Index */
    int ci[g_bd.np_ae]; /* Choiced Indexes */
    int ta[g_bd.ps]; /* Temporary Arrary */
    double hds[g_bd.np_ae]; /* Humming Distances */
    double ave_hd; /* Average of Humming Distance */

    /* Global Timer */
    if(diff_t() >= (double)(g_bd.st)) {return TIMEUP;}

    /* "sols"'s Data Checking & Data Initialize */
    for(i = 0; i < g_bd.np_ae; i++) {
        ci[i] = EMPTY;
    }

    for(i = 0; i < g_bd.np_ae; i++) {
        for(j = 0; j < g_bd.ps; j++) {
            if((ta[j] = sols[(i * g_bd.ps + j)]) == EMPTY) {
                break;
            }
        }
        if(ta[0] != EMPTY && csac(ta) == YES) {
            /* Compare with Each "i"th Sol-Path */
            for(j = 0; j < g_bd.ps; j++) {

                /* Global Timer */
                if(diff_t() >= (double)(g_bd.st)) {break;}

                /* Set Target Branch: cc, nc */
                if(j != (g_bd.ps - 1)) {
                    cc = mysol[j]; nc = mysol[(j + 1)];
                }
                else {
                    cc = mysol[j]; nc = mysol[0];
                }

                /* Match to Other Sol-Paths */
                for(k = 0; k < g_bd.ps; k++) {
                    if(ta[k] == cc) {
                        if(k == 0) {
                            if(ta[(g_bd.ps - 1)] == nc || ta[1] == nc) {
                                sum++;
                            }
                        }
                        else if(k == (g_bd.ps - 1)) {
                            if(ta[(k - 1)] == nc || ta[0] == nc) {
                                sum++;
                            }
                        }
                        else {
                            if(ta[(k - 1)] == nc || ta[(k + 1)] == nc) {
                                sum++;
                            }
                        }
                        break;
                    }
                }
            }
            hds[i] = (double)sum / (double)g_bd.ps;
            asum += sum;
            sum = 0;
            nusol++;
        }
        else {
            hds[i] = -1;
            sum = 0;
        }
    }

    if(nusol != 0) {
        /* Average of Humming Distance [%] */
        ave_hd = ((double)asum / (double)nusol) / (double)g_bd.ps;

        for(i = 0; i < g_bd.np_ae; i++) {
            if(hds[i] > 0 && hds[i] < ave_hd) {
                ci[cii] = i;
                cii++;
            }
        }

        return (ci[(rand() % cii)]);
    }
    else {
        return EMPTY;
    }
}

void crossov(int pthr, int * sols, int * mysol, int cpi_ap)
{
    int i;
    int opsol[g_bd.ps]; /* Other Parent Solution */
    int cpi[(ig_p[pthr].ncp)]; /* Cut Point Index */

    /* Copy the Choiced Solution Path to Temporary Path */
    for(i = 0; i < g_bd.ps; i++) {
        opsol[i] = sols[(cpi_ap * g_bd.ps + i)];
    }

    /* Choice Cut Point By Random */
    ccp_br(cpi, pthr);

    /* Partially Matched Crossover */
    if(ig_p[pthr].tGA == DEFAULT) {
        pm_crossov(cpi, opsol, mysol, pthr);
    }
    else if(ig_p[pthr].tGA == TYPE1) {
        //od_crossov();
    }
}

void pm_crossov(int * cpi, int * parent2, int * parent1, int pthr)
{
    int i, j, sj;
    int child[g_bd.ps]; /* Child Path */
    int cpii = 0; /* Cut Point Index's Index */
    int copy_p1_child = OFF;
    int ntc = 0; /* Number of Target City */

    /* Create Base Child */
    for(i = 0; i < g_bd.ps; i++) {
        if(i == cpi[cpii]) {
            /* Index Procedure */
            if(cpii != ig_p[pthr].ncp) {
                cpii++;
            }

            if(copy_p1_child == OFF) {
                copy_p1_child = ON;
            }
            else {
                copy_p1_child = OFF;
            }
        }
        if(copy_p1_child == OFF) {
            child[i] = parent1[i];
        }
        else {
            child[i] = parent2[i];
        }
    }

    /* Global Timer */
    if(diff_t() >= (double)(g_bd.st)) {return;}

    cpii = 0;
    copy_p1_child = OFF;

    for(i = 0; i < g_bd.ps; i++) {
        if(i == cpi[cpii]) {
            /* Index Procedure */
            if(cpii != ig_p[pthr].ncp) {
                cpii++;
            }

            if(copy_p1_child == OFF) {
                copy_p1_child = ON;
            }
            else {
                copy_p1_child = OFF;
            }
        }

        if(copy_p1_child == ON) {
            ntc = 0;
            for(j = 0; j < g_bd.ps; j++) {
                if(j != i && child[j] == child[i]) {
                    ntc++;
                    sj = j;
                    break;
                }
            }
            if(ntc == 0) {
                child[i] = parent1[i];
            }
            else if(ntc == 1) {
                child[sj] = parent1[i];
            }
        }
    }

    /* Global Timer */
    if(diff_t() >= (double)(g_bd.st)) {return;}

    if(csac(child) == YES) {
        /* Update Current Sol-Path */
        for(i = 0; i < g_bd.ps; i++) {
            ig_p[pthr].csp[i] = child[i];
        }
        ig_p[pthr].csd = gpd(ig_p[pthr].csp, &pthr);
    }
}

/* 1 >= cpi[*] >= ps */
void ccp_br(int * cpi, int pthr)
{
    int i, test;
    int haba = 80;
    int bef;

    if(ig_p[pthr].ncp == 1) {
        cpi[0] = g_bd.ps - g_bd.ps / 3;
    }
    else if(ig_p[pthr].ncp == 2) {
        /*if((test = (rand() % (g_bd.ps - haba))) == 0) {
            test = 1;
        }
        cpi[0] = test;
        cpi[1] = test + haba;*/
        if((test = (rand() % (g_bd.ps / 2))) == 0) {
            test = 1;
        }
        cpi[0] = test;
        bef = cpi[0];
        for(i = 1; i < ig_p[pthr].ncp; i++) {
            if((test = (rand() % (g_bd.ps - bef))) == 0) {
                test = 1;
            }
            cpi[i] = bef + test;
            bef = cpi[i];
        }
    }
    else {
        if((test = (rand() % (g_bd.ps / 2))) == 0) {
            test = 1;
        }
        cpi[0] = test;
        bef = cpi[0];
        for(i = 1; i < ig_p[pthr].ncp; i++) {
            if((test = (rand() % (g_bd.ps - bef))) == 0) {
                test = 1;
            }
            cpi[i] = bef + test;
            bef = cpi[i];
        }
    }
}

void mpi_fin(void)
{
    MPI_Finalize();
}

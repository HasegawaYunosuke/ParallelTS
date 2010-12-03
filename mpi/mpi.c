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

    /* Send the Best Solution of All Thread to Root PC:rbuf4tpc */
    MPI_Gather(sbuf, g_bd.ps, MPI_INT, rbuf4sol, g_bd.ps, MPI_INT, rbuf4tpc, MPI_COMM_WORLD);
    /*DEL*/printf("Node:%d, Recved From %d\n", g_bd.mpi_id, rbuf4tpc);

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

void mpi_fin(void)
{
    MPI_Finalize();
}

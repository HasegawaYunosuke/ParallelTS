#include "header.h"

void mpi_test(void)
{
    printf("MPI TEST\n");
}

void mpi_ip(int argc, char **argv)
{
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

    /* Only Recv Thread */
    if(g_bm.mpim == ON) {
        pthread_mutex_init(&g_send_mutex, NULL);
        pthread_create(&g_recv_pth, NULL, mpi_recvp, (void *)&arg);
    }
}

void * mpi_recvp(void * arg)
{
    MPI_Status stat;
    int rbf = OFF; /* Recv Buffer Flag */
    int nrecv = 1; /* Number of Recv Element */
    int nsend = g_bd.ps; /* Number of Send Element */
    int rbuf4tpc[nrecv]; /* Recv Buffer for Target PC */
    int rbuf4sol[(nsend * g_bd.np_ae)]; /* Recv Buffer for Gater Solution */
    int sbuf[nsend];

    g_bm.mpi_recvsw = ON;

    for(;;) {
        pthread_testcancel();
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_SEND_WANT, MPI_COMM_WORLD, &rbf, &stat);
        if(rbf == ON) {
            pthread_testcancel();
            MPI_Recv(rbuf4tpc, nrecv, MPI_INT, MPI_ANY_SOURCE, MPI_SEND_WANT, MPI_COMM_WORLD, &stat);
            MPI_Gather(sbuf, nsend, MPI_INT, rbuf4sol, nsend, MPI_INT, rbuf4tpc[0], MPI_COMM_WORLD);
            /*DEL*/printf("Node:%d, Recved From %d\n", g_bd.mpi_id, rbuf4tpc[0]);
        }
        pthread_testcancel();
        usleep(100000);
    }
}

void mpi_want(int npthr)
{
    int snode; /* Send Node */
    int nsend = g_bd.ps; /* Number of Send Element */
    int rbuf4sol[(nsend * g_bd.np_ae)]; /* Recv Buffer for Gater Solution */
    int sbuf[nsend];

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

}

void mpi_fin(void)
{
    MPI_Finalize();
}

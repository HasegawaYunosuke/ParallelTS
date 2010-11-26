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

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np_ae);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_id);
    MPI_Get_processor_name(id_name, &nl);

    g_bd.np_ae = np_ae;
    g_bd.mpi_id = mpi_id;
    g_bd.mpi_nl = nl;
    g_bd.id_name = (char *)malloc(sizeof(char) * MPI_MAX_PROCESSOR_NAME);
    strcpy(g_bd.id_name, id_name);
}

void mpi_fin(void)
{
    /*MPI_Barrier(MPI_COMM_WORLD);*/
    MPI_Finalize();
    //sleep(5);
}

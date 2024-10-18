#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {

    int nproc, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello from %d di %d processi\n", rank, nproc);

    MPI_Finalize();

    return 0;
}

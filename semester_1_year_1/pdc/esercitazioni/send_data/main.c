#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {

    int nproc, rank;
    float a[2];

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
       a[0] = 1, a[1] = 2;
       printf("%d: sending a[0]=%f, a[1]=%f \n", rank,  a[0], a[1]);
       MPI_Send(a, 2, MPI_FLOAT, 1, 10, MPI_COMM_WORLD);
    } else {
       MPI_Recv(a, 2, MPI_FLOAT, 0, 10, MPI_COMM_WORLD, &status);
       printf("%d: received a[0]=%f, a[1]=%f \n", rank,  a[0], a[1]);
    }


    MPI_Finalize();

    return 0;
}

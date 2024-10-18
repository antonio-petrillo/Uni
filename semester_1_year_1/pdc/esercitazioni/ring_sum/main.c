#include <stdio.h>
#include <mpi.h>

typedef enum{ RING } tags;

int main(int argc, char **argv) {

    int nproc, rank;
    int array[10];
    int i, sum = 0, tmp;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // init array and compute local sum
    for(i = 0; i < 10; i++) {
        array[i] = rank * 10 + i;
        sum += array[i];
    }

    tmp = sum;
    for (i = 1; i < nproc; i++) {
        MPI_Send(&tmp, 1, MPI_INT, (rank + i) % nproc, RING, MPI_COMM_WORLD);
        MPI_Recv(&tmp, 1, MPI_INT, (rank - i) % nproc, RING, MPI_COMM_WORLD, &status);
        sum += tmp;
    }

    printf("Sum from process %d (of %d) := %d\n", rank, nproc, sum);

    MPI_Finalize();

    return 0;
}

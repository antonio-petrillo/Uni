#include <mpi.h>
#include <stdio.h>

typedef enum {
  TAG_SHARE_WITH_PREV,
  TAG_SHARE_WITH_NEXT,
} tag_t;

void laplace(float* A, float* B, float* daprev, float* danext, int N, int LD, int Niter){
    int nproc, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int portion = N / nproc;

    int iter, i, j;
    float nord, sud, ovest, est;

    for (iter = 0; iter < Niter; iter++) {
        if (rank > 0) {
           MPI_Send(A, N, MPI_FLOAT, rank - 1, TAG_SHARE_WITH_PREV, MPI_COMM_WORLD);
           MPI_Recv(daprev, N, MPI_FLOAT, rank - 1, TAG_SHARE_WITH_NEXT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        if (rank < nproc - 1) {
           MPI_Send(&A[(portion - 1) * LD], N, MPI_FLOAT, rank + 1, TAG_SHARE_WITH_NEXT, MPI_COMM_WORLD);
           MPI_Recv(danext, N, MPI_FLOAT, rank + 1, TAG_SHARE_WITH_PREV, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (i = 0; i < portion; i++) {
            // Skip first row in first process
            // Skip last row in last process
            if (rank == 0 && i == 0 || i == portion - 1 && rank == nproc - 1) {
                continue;
            }
            for (j = 1; j < N - 1; j++) {
                nord = i == 0 ? daprev[j] : A[(i - 1) * LD + j];
                sud = i == portion - 1 ?  danext[j] : A[(i + 1) * LD + j];
                ovest = A[i * LD + j - 1];
                est = A[i * LD + j + 1];
                B[i * LD + j] = (nord + sud + ovest + est) * 0.25f;
            }
        }

        for (i = 1; i < portion - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                A[i * LD + j] = B[i * LD + j];
            }
        }

        if (rank > 0) {
            for (j = 1; j < N - 1; j++) {
                A[j] = B[j];
            }
        }

        if (rank < nproc - 1) {
            for (j = 1; j < N - 1; j++) {
                A[(portion - 1) * LD + j] = B[(portion - 1) * LD + j];
            }
        }
    }

    return;
}

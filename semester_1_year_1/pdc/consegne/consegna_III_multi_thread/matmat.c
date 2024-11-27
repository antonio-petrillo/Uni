#include<stdio.h>
#include<omp.h>

void matmatijk(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N3; j++) {
            for (int k = 0; k < N2; k++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatkji(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (k = 0; k < N2; k++) {
        for (j = 0; j < N3; j++) {
            for (i = 0; i < N1; i++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatikj(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (i = 0; i < N1; i++) {
        for (k = 0; k < N2; k++) {
            for (j = 0; j < N3; j++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatjik(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (j = 0; j < N3; j++) {
        for (i = 0; i < N1; i++) {
            for (k = 0; k < N2; k++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatkij(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (k = 0; k < N2; k++) {
        for (i = 0; i < N1; i++) {
            for (j = 0; j < N3; j++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatjki(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (j = 0; j < N3; j++) {
        for (k = 0; k < N2; k++) {
            for (i = 0; i < N1; i++) {
                C[i * ldC + j] += A[i * ldA + k] * B[k *ldB + j];
            }
        }
    }
}

void matmatblock(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3, // size A, B, C
    int dbA, int dbB, int dbC // block size A, B, C
) {
    int i,j,k;
    const int portion_1 = N1 / dbA; // cache size
    const int portion_2 = N2 / dbB; // cache size
    const int portion_3 = N3 / dbC; // cache size
    for (i = 0; i < portion_1; i++) {
        for (j = 0; j < portion_3; j++) {
            for (k = 0; k < portion_2; k++) {
                matmatikj(
                    ldA, ldB, ldC,
                    &A[i * ldA * dbA + k * dbA],
                    &B[k * ldB * dbB + j * dbB],
                    &C[i * ldC * dbC + j * dbC],
                    dbA, dbB, dbC);
            }
        }
    }

}

void matmatthread( // algorithm 4
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3, // size A, B, C
    int dbA, int dbB, int dbC, // block size A, B, C
    int NTROW, int NTCOL
) {
    int NT = NTROW * NTCOL;
    omp_set_num_threads(NT);
    int thread_id, id_i, id_j;
    int i, j, k, offset_on_i, offset_on_j;
    const int portion_n1 = N1 / NTROW;
    const int portion_n3 = N3 / NTCOL;
#pragma omp parallel private(thread_id, id_i, id_j, i, j, k, offset_on_i, offset_on_j)
    {
        thread_id = omp_get_thread_num();
        /* id_i = thread_id / NTROW; */
        id_i = thread_id / NTCOL;
        id_j = thread_id % NTCOL;

        offset_on_i = id_i * portion_n1;
        offset_on_j = id_j * portion_n3;
        matmatblock(ldA, ldB, ldC,
                    &A[offset_on_i * ldA],
                    &B[offset_on_j],
                    &C[offset_on_i * ldC + offset_on_j],
                    portion_n1,
                    N2,
                    portion_n3,
                    dbA, dbB, dbC);
    }
}

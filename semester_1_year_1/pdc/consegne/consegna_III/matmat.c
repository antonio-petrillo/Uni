#include<stdio.h>

void matmatijk(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
 ) {
    int i,j,k;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            for (int k = 0; k < N3; k++) {
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
    for (k = 0; k < N3; k++) {
        for (j = 0; j < N2; j++) {
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
        for (k = 0; k < N3; k++) {
            for (j = 0; j < N2; j++) {
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
    for (j = 0; j < N2; j++) {
        for (i = 0; i < N1; i++) {
            for (k = 0; k < N3; k++) {
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
    for (k = 0; k < N3; k++) {
        for (i = 0; i < N1; i++) {
            for (j = 0; j < N2; j++) {
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
    for (j = 0; j < N2; j++) {
        for (k = 0; k < N3; k++) {
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
    const int portion = N1 / dbA; // cache size
    for (i = 0; i < portion; i++) {
        for (j = 0; j < portion; j++) {
            for (k = 0; k < portion; k++) {
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

#ifndef MATMAT_H_
#define MATMAT_H_

void matmatblock(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);

void matmatijk(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);

void matmatkji(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);

void matmatikj(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);


void matmatjik(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);

void matmatkij(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);

void matmatjki(
    int ldA, int ldB, int ldC, // leading dimension A, B, C
    double* A, double* B, double* C, // matrix A, B, C
    int N1, int N2, int N3 // size A, B, C
);


#endif // MATMAT_H_

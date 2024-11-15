#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matmat.h"

#define MAX_DIM 1536
#define MAX_RNG 100

double get_cur_time();
void init_matrix(double* mat, int LD, int N);

#define COMPUTE(s, n1, n2, n3, a, b, c, l1, l2, l3, fn) \
    do { \
        start = get_cur_time(); \
        fn(l1, l2, l3, a, b, c, n1, n2, n3); \
        end = get_cur_time(); \
        diff = end - start; \
        printf("%s, %lu, %lf, %.8e\n", s, n1, diff, n1 * n1 * n1 * 2 / diff * 10.0e-9); \
    } while (0)

int main(int argc, char *argv[]) {

    double* A = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));
    double* B = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));
    double* C = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));

    long N1 = 256, N2 = 256, N3 = 256;
    double start, end, diff;
    printf("ORDER, SIZE, TIME, GFLOPS\n"); // gflops = 2 * n^3 / time * 10e-9
    while (N1 <= MAX_DIM) {

        COMPUTE("ijk", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatijk);
        COMPUTE("kji", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatkji);
        COMPUTE("ikj", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatikj);
        COMPUTE("jik", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatjik);
        COMPUTE("kij", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatkij);
        COMPUTE("jki", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatjki);
        COMPUTE("block", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatblock);

        N1 += 256;
        N2 += 256;
        N3 += 256;
    }

    return 0;
}

void init_matrix(double* mat, int LD, int N) {
    int i,j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            mat[i * LD + j] = rand() % MAX_RNG;
        }
    }
}

double get_cur_time() {
  struct timeval tv;
  struct timezone tz;
  double cur_time;

  gettimeofday(&tv, &tz);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;

  return cur_time;
}

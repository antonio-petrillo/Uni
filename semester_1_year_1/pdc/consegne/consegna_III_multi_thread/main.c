#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matmat.h"

/* #define DEBUG */

#define MAX_DIM 2048
#define MAX_RNG 100

double get_cur_time();
void init_matrix(double* mat, int LD, int N, int zero_out);
void assert_computation(double* mat, int LD, int N, char* strat);

#ifdef DEBUG
#define COMPUTE(s, n1, n2, n3, a, b, c, l1, l2, l3, fn) \
    do { \
        init_matrix(a, l1, n1, 0); \
        init_matrix(b, l2, n2, 0); \
        init_matrix(c, l3, n3, 1); \
        fn(l1, l2, l3, a, b, c, n1, n2, n3); \
        assert_computation(c, l3, n3, s);\
    } while (0)
#else
#define COMPUTE(s, n1, n2, n3, a, b, c, l1, l2, l3, fn) \
    do { \
        start = get_cur_time(); \
        fn(l1, l2, l3, a, b, c, n1, n2, n3); \
        end = get_cur_time(); \
        diff = end - start; \
        printf("%s, %lu, %lf, %.8e\n", s, n1, diff, n1 * n2 * n3 * 2 / diff * 10.0e-9); \
    } while (0)
#endif

#ifdef DEBUG
#define COMPUTE_BLOCK(n1, n2, n3, a, b, c, l1, l2, l3, dba, dbb, dbc) \
    do { \
        init_matrix(a, l1, n1, 0); \
        init_matrix(b, l2, n2, 0); \
        init_matrix(c, l3, n3, 1); \
        matmatblock(l1, l2, l3, a, b, c, n1, n2, n3, dba, dbb, dbc); \
        assert_computation(c, l3, n3, "block");\
    } while (0)
#else
#define COMPUTE_BLOCK(n1, n2, n3, a, b, c, l1, l2, l3, dba, dbb, dbc) \
    do { \
        start = get_cur_time(); \
        matmatblock(l1, l2, l3, a, b, c, n1, n2, n3, dba, dbb, dbc); \
        end = get_cur_time(); \
        diff = end - start; \
        printf("block, %lu, %lf, %.8e\n", n1, diff, n1 * n2 * n3 * 2 / diff * 10.0e-9); \
    } while (0)
#endif

#ifdef DEBUG
#define COMPUTE_MULTI(n1, n2, n3, a, b, c, l1, l2, l3, dba, dbb, dbc, nrow, ncol) \
    do { \
        init_matrix(a, l1, n1, 0); \
        init_matrix(b, l2, n2, 0); \
        init_matrix(c, l3, n3, 1); \
        matmatthread(l1, l2, l3, a, b, c, n1, n2, n3, dba, dbb, dbc, nrow, ncol); \
        assert_computation(c, l3, n3, "thread");\
    } while (0)
#else
#define COMPUTE_MULTI(n1, n2, n3, a, b, c, l1, l2, l3, dba, dbb, dbc, nrow, ncol) \
    do { \
        start = get_cur_time(); \
        matmatthread(l1, l2, l3, a, b, c, n1, n2, n3, dba, dbb, dbc, nrow, ncol); \
        end = get_cur_time(); \
        diff = end - start; \
        printf("thread, %lu, %lf, %.8e\n", n1, diff, n1 * n2 * n3 * 2 / diff * 10.0e-9); \
    } while (0)
#endif

int main(int argc, char *argv[]) {

    double* A = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));
    double* B = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));
    double* C = (double*) calloc(MAX_DIM * MAX_DIM, sizeof(double));

    /* long N1 = 256, N2 = 256, N3 = 256; */
    long N1 = 1024, N2 = 1024, N3 = 1024;
    double start, end, diff;

    #ifndef DEBUG
    printf("ORDER, SIZE, TIME, GFLOPS\n"); // gflops = 2 * n^3 / time * 10e-9
    #endif

    while (N1 <= MAX_DIM) {
    /* while (N1 <= MAX_DIM / 2) { */
        /* COMPUTE("ijk", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatijk); */
        /* COMPUTE("kji", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatkji); */ // slow as fuck
        /* COMPUTE("ikj", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatikj); */
        /* COMPUTE("jik", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatjik); */
        /* COMPUTE("kij", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatkij); */
        /* COMPUTE("jki", N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, matmatjki); */ // slow as fuck
        /* COMPUTE_BLOCK(N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, 256, 256, 256); */
        /* COMPUTE_MULTI(N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, 128, 128, 128, 2, 2); */
        COMPUTE_MULTI(N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, 128, 128, 128, 2, 2);
        COMPUTE_MULTI(N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, 128, 128, 128, 2, 4);
        COMPUTE_MULTI(N1, N2, N3, A, B, C, MAX_DIM, MAX_DIM, MAX_DIM, 128, 128, 128, 4, 2);


        /* N1 += 256; */
        /* N2 += 256; */
        /* N3 += 256; */

        N1 += 256 * 4;
        N2 += 256 * 4;
        N3 += 256 * 4;
    }

    return 0;
}

void init_matrix(double* mat, int LD, int N, int zero_out) {
    int i,j;
    for (i = 0; i < LD; i++) {
        for (j = 0; j < LD; j++) {
            if (zero_out) {
                mat[i * LD + j] = 0;
            } else {
                if (i < N && j < N) {
                    mat[i * LD + j] = 1;
                } else {
                    mat[i * LD + j] = 0;
                }
            }
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

void assert_computation(double* mat, int LD, int N, char* strat) {
    int i,j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (mat[i * LD + j] != N) {
                fprintf(stderr, "Error in '%s', at [%d, %d] with[LD := %d, N:= %d], %lf\n", strat, i, j, LD, N, mat[i * LD + j]);
                return;
            }
        }
    }
}

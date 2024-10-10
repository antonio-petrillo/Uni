#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#include <math.h>
#include <time.h>
#include <sys/time.h>

double run_with_nt(int nt, int size, double* matrix);
double compute(double* matrix, int size, int nt);
double get_cur_time();

int main() {
    for (int n = 800; n <= 5600; n += 800) {
        double* matrix = (double*) calloc(n * n, sizeof(double));
        for(int i = 0; i < n * n; i++) {
            matrix[i] = rand() % 100;
            /* matrix[i] = 1.0; */
        }
        for (int nt = 1; nt <= 8; nt <<= 1) {
            double start = get_cur_time();
            double max = run_with_nt(nt, n, matrix);
            double end = get_cur_time();
            printf("N := %d, NT := %d, time := %lf, result := %lf\n", n, nt, end - start, max);
        }
        printf("\n");
        free(matrix);
    }
    return 0;
}

double run_with_nt(int nt, int size, double* matrix) {
    int old = omp_get_num_threads();
    omp_set_num_threads(nt);

    double maxmat = 0;
    #pragma omp parallel
    {
    int id = omp_get_thread_num();

    double max = compute(matrix + (size / nt) * id, size, nt);

#pragma omp critical
    {
        maxmat = maxmat < max ? max : maxmat;
    }
    }

    omp_set_num_threads(old);
    return maxmat;
}

double compute(double* matrix, int size, int nt) {
  double local_max = .0;
  double* row = matrix;
  for (int i = 0; i < size / nt; i++) { //how many rows I should consider
      double sum = .0;
      for (int j = 0; j < size; j++) {
          sum += sqrt(row[j]);
      }
      local_max = local_max < sum ? sum : local_max;
      row = row + size;
  }
  return local_max;
}

double get_cur_time() {
  struct timeval   tv;
  struct timezone  tz;
  double cur_time;

  gettimeofday(&tv, &tz);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;

  return cur_time;
}

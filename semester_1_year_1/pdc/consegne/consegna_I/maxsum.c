// Author: Antonio Petrillo
// Email: antonio.petrillo4@studenti.unina.it
// Matricola: N97000496
#include <math.h>
#include <omp.h>

double maxsum(int N, int LD, double *A, int NT) {
  double max = 0, local_max = 0, sum = 0;
  int id, row, col;
  const int portion = N / NT;

  omp_set_num_threads(NT);

#pragma omp parallel private(local_max, id, sum, row, col)
  {
    local_max = 0;
    id = omp_get_thread_num();
    for (row = portion * id; row < portion * (id + 1); row++) {
      sum = 0;
      for (col = 0; col < N; col++) {
        sum += sqrt(A[row * LD + col]);
      }
      local_max = local_max < sum ? sum : local_max;
    }

#pragma omp critical
    { max = max < local_max ? local_max : max; }
  }

  return max;
}

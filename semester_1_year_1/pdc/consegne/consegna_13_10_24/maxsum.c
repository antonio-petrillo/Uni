#include <omp.h>
#include <math.h>

double maxsum(int N, int LD, double* A, int NT) {
    double max = 0, local_max = 0, sum = 0;
    int id, i, j;
    const int portion = N / NT;

    omp_set_num_threads(NT);

    #pragma omp parallel private(local_max, id, sum, i, j)
    {
        id = omp_get_thread_num();
        for (i = portion * id; i < portion * (id + 1); i++) {
            sum = 0;
            for (j = 0; j < N; j++) {
                sum += sqrt(A[i * LD + j]);
            }
            local_max = local_max < sum ? sum : local_max;
        }

        #pragma omp critical
        {
            max = max < local_max ? local_max : max;
        }
    }

    return max;
}

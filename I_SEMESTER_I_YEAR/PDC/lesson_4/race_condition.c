#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREAD 4
#define N 100

int arr[N] = {0};

int main() {
    int id, sum = 0, start, end;
    for (int i = 0; i < N; i++) {
        /* arr[i] = rand() % 10; */
        arr[i] = 100;
    }

    omp_set_num_threads(NUM_THREAD);

#pragma omp parallel private(id, start, end)
{
    id = omp_get_thread_num();
    start = id * N / NUM_THREAD;
    end = (id + 1) * N/ NUM_THREAD;

    for(int i = start; i < end; i++) {
        sum += arr[i]; // sum is not guarded by any lock
    }
}

    printf("In thread %d the sum is %d\n", id, sum);

    return 0;
}

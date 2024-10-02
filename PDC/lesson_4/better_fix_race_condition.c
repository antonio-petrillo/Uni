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


#pragma omp parallel private(id, start, end)
{
    id = omp_get_thread_num();
    start = id * N / NUM_THREAD;
    end = (id + 1) * N/ NUM_THREAD;

    for(int i = start; i < end; i++) {
        #pragma omp critical
        sum += arr[i]; // sum is not guarded by any lock
    }
    printf("thread %d work done, partial := %d\n", id, sum);
}

    printf("In thread %d the sum is %d\n", id, sum);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREAD 4
#define N 100

int arr[N] = {0};

int main() {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        /* arr[i] = rand() % 10; */
        arr[i] = 100;
    }


#pragma omp parallel for reduction(+: sum)
    for(int i = 0; i < N; i++) {
        sum += arr[i];
    }

    printf("The sum is %d\n", sum);

    return 0;
}

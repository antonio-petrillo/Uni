#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  omp_set_num_threads(2);
  omp_lock_t lock;
  omp_init_lock(&lock);
  omp_set_lock(&lock);
  int id;

  int gen;

#pragma omp parallel sections private(id)
  {
      // producer
#pragma omp section
    {
        while(1) {
            sleep(2);
            id = omp_get_thread_num();
            gen = rand() % 100;
            printf("[PROD] thread %d := %d", id, gen);
            omp_unset_lock(&lock);
        }
    }
      // consumer
#pragma omp section
    {
        while(1) {
            id = omp_get_thread_num();
            omp_set_lock(&lock);
            printf("[CONS] thread %d := %d", id, gen);
        }
    }
  }

  omp_destroy_lock(&lock);

  return 0;
}

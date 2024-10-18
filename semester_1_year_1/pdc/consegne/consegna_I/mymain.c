#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double get_cur_time();

int main() {
  int NT, i, j, LD;
  double MAX, *A;
  double t1, t2, save;
  double maxsum(int, int, double *, int);

  LD = 5600;
  A = (double *)malloc(sizeof(double) * LD * LD);
  printf("NT,    N,         TIME,        SPEEDUP,     EFFICIENCY,             RESULT\n");
  for (int N = 800; N <= LD; N += 800) {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i * LD + j] = rand() % 100;
      }
    }

    for (NT = 1; NT <= 8; NT <<= 1) {

      /* printf("===============\n"); */
      /* printf(" NUMERO THREAD = %d N = %d \n", NT, N); */

      t1 = get_cur_time();
      MAX = maxsum(N, LD, A, NT);
      t2 = get_cur_time();

      if (NT == 1)
        save = t2 - t1;
      /* printf("il massimo della somma dei moduli con N = %d e' %f \n", N, MAX); */
      /* printf("il tempo totale e' %e , lo speedup = %f , l'efficienza = %f \n", */
      /*        t2 - t1, save / (t2 - t1), save / (t2 - t1) / NT); */

      double delta = t2 - t1;
      printf("%2d, %4d, %12e, %2.12lf, %2.12lf, %8.12lf\n", NT, N, delta, save / delta, save / delta / NT, MAX);
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

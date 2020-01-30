#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// default memory size
#ifndef MEM_TEST_ARRAY_SIZE
#define MEM_TEST_ARRAY_SIZE     1024*1024*1024 / sizeof(double) * 4
#endif

// helper functions
void test_daxpy( double *__restrict__  a, double *__restrict__  b, double scalar );

int main( int argc, char** argv )
{
  printf( "The total memory allocated is %7.3lf MB.\n",
          2.0*sizeof(double)*MEM_TEST_ARRAY_SIZE/1024/1024 );

  double*   a = NULL;
  double*   b = NULL;

  a = (double *) malloc( sizeof(double)*MEM_TEST_ARRAY_SIZE );
  b = (double *) malloc( sizeof(double)*MEM_TEST_ARRAY_SIZE );

  // run the code
  test_daxpy( a, b, 8.0 );

  free(a);
  free(b);

  return 0;
}

void test_daxpy( double * __restrict__ a,  double * __restrict__ b, double scalar) {
  int num_errors = 0;
  double time = 0;
  double start_time = 0;
  int iters = 350;

  // initialize on the host
#pragma omp parallel for 
for (size_t j=0; j<MEM_TEST_ARRAY_SIZE; j++)
    {
      a[j] = 0.0;
      b[j] = j;
    }

#pragma omp target enter data map(to:a[0:MEM_TEST_ARRAY_SIZE])
#pragma omp target enter data map(to:b[0:MEM_TEST_ARRAY_SIZE])

 start_time = omp_get_wtime();

  for(size_t i=0;i<iters;i++)
    {
#pragma omp target teams distribute parallel for 
      for (size_t j=0; j<MEM_TEST_ARRAY_SIZE; j++) {
        a[j] = a[j]+scalar*b[j];
      }
    }

  time = omp_get_wtime()-start_time;

#pragma omp target update from(a[0:MEM_TEST_ARRAY_SIZE])

  printf("Time: %lf\n", time);

  // error checking
  for (size_t j=0; j<MEM_TEST_ARRAY_SIZE; j++) {
      if( fabs(a[j] - (double)j*iters*scalar) > 0.000001  ) {
	  num_errors++;
	}
    }

  assert(num_errors == 0);

  return;
}

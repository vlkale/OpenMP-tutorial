#include <stdio.h>
#include <omp.h>

int main( int argv, char** argc ) {
  // in CUDA <<< numBlocks, blockSize>>>
#pragma omp target teams distribute parallel for simd num_teams(2) thread_limit(2)
  for(int i=0;i<4;i++)
    {
      printf( "Thread %d out of %d threads in team %d out of %d teams is using index %d\n", 
	      omp_get_thread_num(), omp_get_num_threads(), 
	      omp_get_team_num(), omp_get_num_teams(), i );
    }

return 0;
}

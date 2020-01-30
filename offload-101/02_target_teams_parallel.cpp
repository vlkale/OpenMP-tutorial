#include <stdio.h>
#include <omp.h>
int main( int argv, char** argc ) {
#pragma omp target teams 
#pragma parallel
  {
    int team = omp_get_team_num();
    int nteams = omp_get_num_teams();
    int tid = omp_get_thread_num();
    int nthreads = omp_get_num_threads(); 

    printf( "Team %d out of %d teams\nThread %d of out %d threads in the team.\n",
	    team, nteams, tid, nthreads );
  }
  return 0;
}

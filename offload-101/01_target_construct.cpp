#include <stdio.h>
#include <omp.h>

int main( int argv, char** argc ) {

  printf( "Number of devices: %d\n", omp_get_num_devices() );
  printf( "Default device: %d\n", omp_get_default_device()  );
  printf( "We %s running on the initial device.\n", omp_is_initial_device() ? "are": "are not" );

  #pragma omp target
  {
    if( !omp_is_initial_device() )
      printf( "Hello world from accelerator.\n" );
    else
      printf( "Hello world from host.\n" );
  }
  return 0;
}

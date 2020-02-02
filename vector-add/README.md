
 # Vector Addition Example

 This is an example of an OpenMP CPU version of a vector add
 and a OpenMP offload GPU version of a vector add.

 This was run on Ascent, which has 2P9s and 6V100s per node.

 The goal is to run the CPU code on all 42 cores of 2P9s,
 then to run the GPU code on a V100, and then compare
 timings. Vector add is a memory bound code. We've chosen
 the memory footprint to be in main memory for both CPU and GPU.
 We expect the speedup of GPU to CPU code to be about 3x
 since a V100 has ~900 GB/s theoretical BW and 2 P9s have
 ~340 GB/s theoretical BW. 

 ## Run the CPU code

 ```
 bash-4.2$ make vector_add_cpu 
 xlc++ -O2 -qsmp=omp vector_add_cpu.cpp -o vector_add_cpu
 bash-4.2$ ./run_vector_add_cpu.sh 
 + OMP_PROC_BIND=spread
 + OMP_NUM_THREADS=42
 + jsrun -n 1 -a 1 -c 42 -r 1 --bind packed:42 ./vector_add_cpu
 The total memory allocated is 8192.000 MB.
 Time (s): 17.649502
 Success!
 ```

 ## Run the GPU code

 ```
 bash-4.2$ make vector_add_gpu 
 xlc++ -O2 -qsmp=omp -qoffload vector_add_gpu.cpp -o vector_add_gpu
 bash-4.2$ ./run_vector_add_gpu.sh
 + jsrun -n 1 -a 1 -c 1 -g 1 ./vector_add_gpu
 The total memory allocated is 8192.000 MB.
 Time (s): 5.333160
 Success!
 ```
  The CPU timing was 17.649502 s, and the GPU timing was 5.333160 s.
  This is a 3.3x speedup, close to what we expect.
  
  However, note that we didn't include any overheads from data transfer in the timing.
  If you want, try changing the timing in the GPU code and see how it 
  affects the speedup.

 


# OpenMP Offload 101

 This covers the three basic offloading concepts:
 transferring execution control, expressing parallelism, and 
 mapping data.

 There are three sections:

 1. Offloading code to the device and getting device info
 2. Expressing parallelism
 3. Mapping data

 ## Offloading code to the device and getting device info

 make 01_target_construct
 jsrun -n 1 -a 1 -c 1 -g 1 ./01_target_construct
 jsrun -n 1 -a 1 -c 1 -g 6 ./01_target_construct
 module load cuda
 jsrun -n 1 -a 1 -c 1 -g 1 nvprof ./01_target_construct

 ## Expressing parallelism 

 Artificial example showing a loop parallelized with
 `target teams distribute parallel for`, but the
 only thing in the loop is a printf statement
 to show that the iterations of the loop are split
 up over the threads.

 make 02_target_teams_parallel
 jsrun -n 1 -a 1 -c 1 -g 1 ./02_target_teams_parallel
 # modify to num_teams() thread_limit()
 jsrun -n 1 -a 1 -c 1 -g 1 ./02_target_teams_parallel

 ## Mapping data

 make 03_map
 # initially just `parallel for`, but then want to run on device,
 # so change to `target teams distribute parallel for`
 # here we actually want to do something on the device
 # so we need to give data to the device to compute on.
 # this is where the map clause comes in.
 # we want to map arrays a and b to the device, compute on the
 # device, and then map the arrays back.
 jsrun -n 1 -a 1 -c 1 -g 1 ./03_map
 module load cuda 
 jsrun -n 1 -a 1 -c 1 -g 1 nvprof --print-gpu-trace ./03_map
 # do we need tofrom? try other mappings

 # slightly more complicated. we have multiple arrays, and
 # want to call daxpy on them. like good programmers, we
 # pull the code into a routine for reuse.
 make 03_map_function
 jsrun -n 1 -a 1 -c 1 -g 1 ./03_map_function
 jsrun -n 1 -a 1 -c 1 -g 1 nvprof --print-gpu-trace ./03_map_function
 # lots of data transfer. do we need this much?

 # unstructured data mapping
 make 03_map_unstructured_function
 jsrun -n 1 -a 1 -c 1 -g 1 ./03_map_unstructured_function
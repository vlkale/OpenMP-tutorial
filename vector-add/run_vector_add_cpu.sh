#!/bin/bash

set -x
OMP_PROC_BIND=spread OMP_NUM_THREADS=42 jsrun --nrs 1 --tasks_per_rs 1 --cpu_per_rs 42 --rs_per_host 1 --bind packed:42 ./vector_add_cpu

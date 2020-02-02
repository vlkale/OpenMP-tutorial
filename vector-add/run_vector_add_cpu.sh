#!/bin/bash

set -x
OMP_PROC_BIND=spread OMP_NUM_THREADS=42 jsrun -n 1 -a 1 -c 42 -r 1 --bind packed:42 ./vector_add_cpu

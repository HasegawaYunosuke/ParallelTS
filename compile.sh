#!/bin/bash

mpicc -DMPIMODE src/main.c mpi/mpi.c src/init.c src/check.c src/read_data.c src/file_manage.c src/error.c src/memory.c src/finalize.c src/math.c src/pthread.c src/init_path.c src/timer.c src/search.c src/tabu.c src/result.c -I include -g -pthread -lm -o b.out

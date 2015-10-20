#!/bin/bash

#SBATCH -N 1 -n 8 -t 0-00:00:45
#SBATCH -o ArrayHello-run-log.o%j

cd $SLURM_SUBMIT_DIR
./charmrun +p8 ./arrayHello
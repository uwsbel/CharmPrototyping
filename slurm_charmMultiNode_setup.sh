#!/bin/bash

#SBATCH -N 1 -n 4 -t 0-00:15:00
#SBATCH -o charm-build-log.o%j

cd $SLURM_SUBMIT_DIR/..

wget http://charm.cs.illinois.edu/distrib/charm-6.6.1.tar.gz
tar -zxvf charm-6.6.1.tar.gz
cd charm

./build charm++ mpi-linux-x86_64 mpicxx smp  gfortran  -j4  --with-production --enable-tracing

echo \
export CHARMDIR=$SLURM_SUBMIT_DIR/../charm \
 >> $HOME/.bashrc


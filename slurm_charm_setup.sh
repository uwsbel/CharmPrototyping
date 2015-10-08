#!/bin/bash

#SBATCH -N 1 -n 4 -t 0-00:15:00
#SBATCH -o charm-build-log.o%j
#SBATCH -p slurm_me759

cd $SLURM_SUBMIT_DIR/..

wget http://charm.cs.illinois.edu/distrib/charm-6.6.1.tar.gz
tar -zxvf charm-6.6.1.tar.gz
cd charm

./build charm++ multicore-linux64 gcc gfortran --with-production --enable-tracing -j4

echo \
export CHARMDIR=$SLURM_SUBMIT_DIR/../charm \
 >> $HOME/.bashrc


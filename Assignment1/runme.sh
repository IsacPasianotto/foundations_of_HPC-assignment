#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="Conway's game"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=02:00:00


# To know each slurm.out file belongs to which job
date
hostname
whoami
pwd


# TODO: change the module load commands
#       according to the architecture you are using
module purge
module load architecture/Intel
module load openMPI/4.1.4/gnu/12.2.1


# Remove old files if any exist and then compile
make clean
make image
make

# TODO: set environment variables
#       according to your needs

export OMP_PLACES=cores
export OMP_PROC_BIND=close
export OMP_NUM_THREADS=8

a=r         # action: i=init, r=run
k=25000     # size of the grid (to be used with -i)
e=1         # evolution: 0=ordered, 1=static (to be used with -r)
s=1         # every how many steps save a snapshot (to be used with -r)
n=500       # number of steps to evolve (to be used with -r)
f=fileToLoad.pbm  # use -f $f to load a initial state from a file or write in the case of -i

# TODO: set the --map-by and --bind-to options
#       according to your needs

mpirun -np 1 --map-by node --bind-to socket ./main.x -r -n 10 -e $e >> $resultdir/OMP-scalability_ordered-ev_size-$k.csv

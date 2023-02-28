#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-AMD"
#SBATCH --get-user-env
#SBATCH --partition=EPYC
#SBATCH --nodes=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --time=01:00:00

cd ..

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp


export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH
export OMP_PLACES=core
export OMP_PROC_BIND=spread
export OMP_NUM_THREADS=64

./gemm_oblas.x

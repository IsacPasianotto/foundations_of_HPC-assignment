#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-AMD"
#SBATCH --get-user-env
#SBATCH --partition=EPYC
#SBATCH --nodes=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --time=01:00:00
#SBATCH --nodelist=epyc[007]

cd ..

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread
export OMP_NUM_THREADS=64


echo m,k,n,time,GFLOPS > ./results/oblas-float-epyc-cores-spread.csv


for size in {2000..20000..1000}
do
	for i in {1..15}
	do
		numactl --interleave=0-7 ./gemm_oblas.x $size $size $size >> ./results/oblas-float-epyc-cores-spread.csv
	done
done

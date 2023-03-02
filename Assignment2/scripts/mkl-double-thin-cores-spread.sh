#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-INTEl"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --cpus-per-task=12
#SBATCH --exclusive
#SBATCH --time=01:00:00

cd ..

module load architecture/Intel
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblisintel/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread
export OMP_NUM_THREADS=12


echo m,k,n,time,GFLOPS > ./results/mkl-double-epyc-cores-spread.csv


for size in {2000..20000..1000}
do
	for i in {1..15}
	do
		./gemm_mkl.x $size $size $size >> ./results/mkl-double-intel-cores-spread.csv
	done
done

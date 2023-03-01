#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-AMD"
#SBATCH --get-user-env
#SBATCH --partition=EPYC
#SBATCH --nodes=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --nodelist=epyc[006]

cd ..

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread


echo cores,m,k,n,time,GFLOPS > ./results/mkl-double-epyc-size-spread.csv

size=12000

for i in {1..64}
do
	export OMP_NUM_THREADS=$i
	for j in {1..10}
	do
		echo -n $i, >> ./results/mkl-double-epyc-size-spread.csv
		./gemm_oblas.x $size $size $size >> ./results/mkl-double-epyc-size-spread.csv
	done
done

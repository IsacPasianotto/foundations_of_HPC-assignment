#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-AMD"
#SBATCH --get-user-env
#SBATCH --partition=EPYC
#SBATCH --nodes=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --time=01:00:00
#SBATCH --nodelist=epyc[005]
cd ..

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=close
#export OMP_NUM_THREADS=64
export BLIS_NUM_THREADS=64

echo m,k,n,time,GFLOPS > ./results/blis-double-epyc-cores-close.csv


for size in {2000..20000..1000}
do
	for i in {1..15}
	do
		numactl --interleave=0-3 ./gemm_blis.x $size $size $size >> ./results/blis-double-epyc-cores-close.csv
	done
done

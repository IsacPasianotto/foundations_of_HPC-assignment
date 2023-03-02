#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-INTEL"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --cpus-per-task=12
#SBATCH --exclusive
#SBATCH --time=02:00:00

cd ..

module load architecture/Intel
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblisintel/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread


echo cores,m,k,n,time,GFLOPS > ./results/oblas-float-intel-size-spread.csv
echo cores,m,k,n,time,GFLOPS > ./results/mkl-float-intel-size-spread.csv
echo cores,m,k,n,time,GFLOPS > ./results/blis-float-intel-size-spread.csv

size=12000

for i in {1..12}
do
	for j in {1..10}
	do
        export OMP_NUM_THREADS=$i
		echo -n $i, >> ./results/oblas-float-intel-size-spread.csv
		./gemm_oblas.x $size $size $size >> ./results/oblas-float-intel-size-spread.csv
        echo -n $i, >> ./results/mkl-float-intel-size-spread.csv
        ./gemm_mkl.x $size $size $size >> ./results/mkl-float-intel-size-spread.csv
        export BLIS_NUM_THREADS=$i
        echo -n $i, >> ./results/blis-float-intel-size-spread.csv
        ./gemm_blis.x $size $size $size >> ./results/blis-float-intel-size-spread.csv
	done
done

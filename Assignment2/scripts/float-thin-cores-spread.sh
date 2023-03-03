#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-INTEL"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --cpus-per-task=12
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --nodelist=thin[008]

cd ..

module load architecture/Intel
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblisintel/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread


echo m,k,n,time,GFLOPS > ./results/blis-float-intel-cores-spread.csv
echo m,k,n,time,GFLOPS > ./results/mkl-float-intel-cores-spread.csv
echo m,k,n,time,GFLOPS > ./results/oblas-float-intel-cores-spread.csv

for size in {2000..20000..1000}
do
	for i in {1..10}
	do
        export OMP_NUM_THREADS=12
        ./gemm_oblas.x $size $size $size >> ./results/oblas-float-intel-cores-spread.csv
        ./gemm_mkl.x $size $size $size >> ./results/mkl-float-intel-cores-spread.csv
        export BLIS_NUM_THREADS=12
		./gemm_blis.x $size $size $size >> ./results/blis-float-intel-cores-spread.csv
	done
done

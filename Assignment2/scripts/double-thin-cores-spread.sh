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


# echo m,k,n,time,GFLOPS > ./results/blis-double-intel-cores-spread.csv
# echo m,k,n,time,GFLOPS > ./results/mkl-double-intel-cores-spread.csv
# echo m,k,n,time,GFLOPS > ./results/oblas-double-intel-cores-spread.csv

# for size in {2000..20000..1000}
# do
#	for i in {1..10}
#	do
#        export OMP_NUM_THREADS=12
#        ./gemm_oblas.x $size $size $size >> ./results/oblas-double-intel-cores-spread.csv
#        ./gemm_mkl.x $size $size $size >> ./results/mkl-double-intel-cores-spread.csv
#        export BLIS_NUM_THREADS=12
#        ./gemm_blis.x $size $size $size >> ./results/blis-double-intel-cores-spread.csv
# 	done
# done


# The previous lines of  code were executed, but
# the execution was not complete because the time was up before completing the procedure.


# for size in {13000..20000..1000}
# do
# 	for i in {1..10}
#	do
#        export OMP_NUM_THREADS=12
#        ./gemm_oblas.x $size $size $size >> ./results/oblas-double-intel-cores-spread.csv
#        ./gemm_mkl.x $size $size $size >> ./results/mkl-double-intel-cores-spread.csv
#        export BLIS_NUM_THREADS=12
#	./gemm_blis.x $size $size $size >> ./results/blis-double-intel-cores-spread.csv
#	done
# done

#  For some reason, the data about mkl where not consistent with the others, I runned it again to check if 
#  there are some issues or was an accidental case (the problems are only in [10000-12000] values)

echo m,k,n,time,GFLOPS > ./results/mkl-double-intel-cores-spread.csv
export OMP_NUM_THREADS=12

for size in {2000..20000..1000}
do
	for i in {1..10}
	do
		./gemm_mkl.x $size $size $size >> ./results/mkl-double-intel-cores-spread.csv
	done
done

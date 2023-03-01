#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2-AMD"
#SBATCH --get-user-env
#SBATCH --partition=EPYC
#SBATCH --nodes=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --nodelist=epyc[007]

cd ..

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp

# Needed for the BLIS library
export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH

export OMP_PLACES=cores
export OMP_PROC_BIND=spread


fileout=./results/oblas-double-epyc-size-close.csv

echo cores,m,k,n,time,GFLOPS > $fileout

size=12000

# limits to change the the numactl memory interleave policy
n0=16
n1=32
n2=48

for i in {1..64}
do
	export OMP_NUM_THREADS=$i
	for j in {1..10}
	do
		if [ $i -le $n0 ]
		then
			echo -n $i, >> $fileout
                	numactl --interleave=0 ./gemm_oblas.x $size $size $size >> $fileout
		elif [ $i -le $n1 ]
		then
			echo -n $i, >> $fileout
             		numactl --interleave=0-1 ./gemm_oblas.x $size $size $size >> $fileout
		elif [ $i -le $n2 ]
		then
			echo -n $i, >> $fileout
                	numactl --interleave=0-2 ./gemm_oblas.x $size $size $size >> $fileout
		else 
			echo -n $i, >> $fileout
			numactl --interleave=0-3 ./gemm_oblas.x $size $size $size >> $fileout
		fi
	done
done

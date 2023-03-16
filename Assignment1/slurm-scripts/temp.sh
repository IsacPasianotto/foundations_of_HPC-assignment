#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="OMP_scalability"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --nodelist=thin[008]

module load architecture/Intel
module load openMPI/4.1.4/gnu/12.2.1

cd ../

# remove old files if any
make clean
make image
make

export OMP_PLACES=cores
export OMP_PROC_BIND=close


k=17500
evolution=0

mpirun -np 2 ./main.x -i -k $k
resultdir=time_measurements

echo size,OMP-threads,time > $resultdir/OMP-scalability_ordered-ev_size_TWO-SOCKET-$k.csv

for i in {1..12}
do
	export OMP_NUM_THREADS=$i
	for j in {1..5}
	do
		echo -n $k,$i >> $resultdir/OMP-scalability_ordered-ev_size_TWO-SOCKET-$k.csv
	        mpirun -np 2 --map-by node --bind-to socket ./main.x -r -n 10 -e $evolution -t >> $resultdir/OMP-scalability_ordered-ev_size_TWO-SOCKET-$k.csv
	done
done

make clean
make image

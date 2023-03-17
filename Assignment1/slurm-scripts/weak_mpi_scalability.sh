#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="MPI-W_scalability"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --nodelist=thin[010]


module load architecture/Intel
module load openMPI/4.1.4/gnu/12.2.1

cd ../

# remove old files if any
make clean
make image
make

export OMP_PLACES=cores
export OMP_PROC_BIND=close
export OMP_NUM_THREADS=16


evolution=1

resultdir=time_measurements

sizes=(10000 10000 14142 17321 20000 22361)

echo size,cores,time > $resultdir/MPI_W-scalability_static-ev_16omp-threds.csv

for i in {1..5}
do
    for j in {1..5}
    do
        echo -n ${sizes[i]},$i >> $resultdir/MPI_W-scalability_static-ev_16omp-threds.csv
	mpirun -np $i ./main.x -i ${sizes[i]}
        mpirun -np $i --map-by core ./main.x -r -n 10 -e $evolution -t >> $resultdir/MPI_W-scalability_static-ev_16omp-threds.csv
    done
done

make clean
make image

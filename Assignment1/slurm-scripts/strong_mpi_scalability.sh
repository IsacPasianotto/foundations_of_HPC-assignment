#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="MPI-s_scalability"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=2
#SBATCH --exclusive
#SBATCH --time=02:00:00

module load architecture/Intel
module load openMPI/4.1.4/gnu/12.2.1

cd ../

# remove old files if any
make clean
make image
make

export OMP_PLACES=cores
export OMP_PROC_BIND=close
export OMP_NUM_THREADS=1


k=17500
evolution=1

./main.x -i -k $k
resultdir=time_measurements

echo size,cores,time > $resultdir/MPI_S-scalability_static-ev_size-$k.csv

for i in {1..48}
do
    for j in {1..5}
    do
        echo -n $k,$i >> $resultdir/MPI_S-scalability_static-ev_size-$k.csv
        mpirun -np $i --map-by core ./main.x -r -n 10 -e $evolution -t >> $resultdir/MPI_S-scalability_static-ev_size-$k.csv
    done
done

make clean
make image

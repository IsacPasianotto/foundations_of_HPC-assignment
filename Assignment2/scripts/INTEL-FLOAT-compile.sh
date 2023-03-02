#!/bin/bash
#SBATCH --no-requeue
#SBATCH --job-name="ex2_comp"
#SBATCH --get-user-env
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --cpus-per-task=12
#SBATCH --exclusive
#SBATCH --time=00:10:00

cd ..

# clean any executable files left over from previous runs 
# The two makefiles will produce executables with the same name, then 
# it doesn't matter which make file's clean is called, it will works anyway
make -f Makefile_DOUBLE clean 

module load architecture/Intel
module load mkl
module load openBLAS/0.3.21-omp

export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblisintel/lib:$LD_LIBRARY_PATH

make -f Makefile_FLOAT_intel cpu

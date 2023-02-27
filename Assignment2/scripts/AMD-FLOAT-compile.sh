cd ..

# clean any executable files left over from previous runs 
# The two makefiles will produce executables with the same name, then 
# it doesn't matter which make file's clean is called, it will works anyway
make -f Makefile_DOUBLE clean 

module load architecture/AMD
module load mkl
module load openBLAS/0.3.21-omp

export LD_LIBRARY_PATH=/u/dssc/ipasia00/myblis/lib:$LD_LIBRARY_PATH

srun -n1 -p EPYC make -f Makefile_FLOAT cpu

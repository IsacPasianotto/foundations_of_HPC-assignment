# Results

In this folder are stored the results of the benchmark done in order to compare the three libraries. \
All the results are named as:

`lib - precision - architecture - fixed - proc_bind .csv`

Where: 

- `lib`: stands for libraryes, it could be:
    - `oblas` for OpenBLAS
    - `mkl` 
    - `blis`
- `precision` indicates the precision for the floating point operations:
    - `double`
    - `float`
- `architecture` indicates the CPU type of the node where the benchmarks are runned: 
    - `epyc` if it's performed in a epyc nodes (AMD CPUs)
    - `intel` if it's performed in a thin node  (INTEL CPUs)
- `fixed`: how we measure the scalability of the `gemm.c` code. It can be: 
    - `cores`: it means that the number of cores is fixed (64 for epyc, 12 for thin nodes). In this case the size of the square matrices is increased form 2k to 20k in steps of 1000
    - `size`: it means that the size of the three matrices is fixed at 12k. The scalability is measured encreasing the number of cores used to run the code (from 1 to 64/12 in epyc/thin nodes)
- `proc_bind`: The binding policy used:
    - `close` if the code is executed after `export OMP_PROC_BIND=close`
    - `spread` if th ecode is executed after `export OMP_PROC_BIND=spread`
 

# Exercise 2

### Description

In this folder there are all the file needed to do the second exercise of the assignment: check how the 3 math libraries `openBLAS`, `MKL` and `BLIS` perform on a level 3 BLAS routine in the given code [`dgemm.c`](dgemm.c).


## - File in this directory

- `README.md`: this file
- `Makefile`s: Makefile to compile the code. Since the compilation was done multiple times (for different precision of floating point operations and on different architectures), exists multiple make file (whose name should be self-explanatory): 
    - `Makefile_DOUBLE`: for `DOUBLE` precision, on **Epyc** nodes
    - `Makefile_FLOAT`: for `FLOAT` precision, on **Epyc** nodes
    - `Makefile_DOUBLE_intel`: for `DOUBLE` precision, on **Thin** nodes
    - `Makefile_FLOAT_intel`: for `FLOAT` precision, on **Thin** nodes

- [`dgemm.c`](dgemm.c): the code given by the professor in the assignment. 
- [`mygemm.c`](mygemm.c): the code that I used to do the exercise. It is a copy of the code given by the professor, with some modifications in the printing format of the results (to make it easier work with the results).

## - [`Scripts` directory](scripts)

- `README.md`: A summary of the scripts I used to perform the code
- `###.sh`: scripts to perform the code. The name of the scripts inside should be self-explanatory. In particular there are scripts to:
    - compile the code (with the different Makefile-s)
    - run the code
    
All that `.sh` file are scripts executed by the `sbatch` command.

## - `Results` [directory](results)

- `README.md`: A summary of the results of the code and the codification adopted for the names of the files
- `###.csv`: all the file that stores the results I got

# Exercise 2

### Description

In this folder there are all the file needed to do the exercise second exercise of the assignment(check the scalability of the [given code](dgemm.c) using `OpenBlas`, `MKL` and `Blis` libraries).

## - File in this directory

- `README.md`: this file
- `Makefile`s: makefile to compile the code. Since The compilation was done multiple times (for different precision and different libraries), exixsts multiple make file (whose name shoulf be self explanatory): 
    - `Makefile_DOUBLE`: for `DOUBLE` precision, on **EPYC** nodes
    - `Makefile_FLOAT`: for `FLOAT` precision, on **EPYC** nodes
    - `Makefile_DOUBLE_intel`: for `DOUBLE` precision, on **THIN** nodes
    - `Makefile_FLOAT_intel`: for `FLOAT` precision, on **THIN** nodes

- `dgemm.c`: the code [given by the professor](dgemm.c) in the assignment. 
- `mygemm.c`: the [code that I used](mygemm.c) to do the exercise. It is a copy of the code given by the professor, with some modifications in the printing format of the results (to make it easier work with the results).

## - `Scripts` [directory](scripts)

- `README.md`: A summary of the scripts I used to perform the code
- `<--->.sh`: scripts to perform the code. The name of the scripts inside should be self explanatory. In particular there are scripts to:
    - compile the code (with the different makefiles)
    - run the code
    
All that `.sh` file are scripts executed by the `sbatch` command.

## - `Results` [directory](results)

- `README.md`: A summary of the results of the code and the codification adopted for the names of the files
- `<--->.csv`: all the file that stores the results I got

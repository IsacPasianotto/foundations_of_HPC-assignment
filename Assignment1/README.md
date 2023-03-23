# Exercise 1

## How to compile the code

The compilation of the code is done using the `Makefile` and the command `make`. It uses the flags `-O3 -march=native` to try to optimize the code, and the `-fopenmp` to enable the `#pragma openmp` directives. 

**Note**: To compile the file *it's required to have installed `Open MPI`* (as well as the [GNU compiler](https://gcc.gnu.org/) of course).

#### Compiling on the Orfeo cluster

To compile the code on the Orfeo cluster, you will need to load the module which contains the `Open MPI` library (and the GNU compiler). 

Depending on which node you want to perform the compilation (Epyc nodes mount AMD CPUs, while Thin nodes mount Intel CPUs), you can run one of the following set of commands: 

```bash
module load architecture/AMD
module load openMPI/4.1.4/gnu/12.2.1
srun -N1 -p EPYC make
```
```bash
module load architecture/Intel
module load openMPI/4.1.4/gnu/12.2.1
srun -N1 -p THIN make
```

This will produce an executable named `main.x` in the current directory.

The `Makefile` can also accept the following options (in this case no module loading or `srun` command are required):

- `make clean`: removes the `main.x` executable and all the `.o` object files in the `obj/` directory.
- `make image`: deletes eventual `.pbm` files in the current directory and in the `snaps/` directory. 

## How to run the code

To run the code, you can do both of the following:

-  Ask to *slurm* scheduler the desired resources and run the executable with the `salloc` and `srun` commands. 
- (Suggested) modify according to your needs the **slurm script** [`runme.sh`](./runme.sh) and run it with the `sbatch` command: 

```bash
sbatch runme.sh
```

Essentially, the `runme.sh` script will run the executable `main.x` with the arguments that it could receive:

- `-i`: if it must randomly generate an initial configuration of the game.
- `-r`: if it must read the initial configuration from a `.pbm` file and perform the actual game.
- `-k <int ∈ {1, ..., 32,767}>`: The size of the square matrix (number of rows/columns) the playground will have (if the `-i` option is used).
- `-n <int>`: The number of generations the game will run for (if the `-r` option is used).
- `-s <int>`: Every `<int>` generations, the program will store a snapshot of the playground in the `snaps/` directory. If it is not used, or set to 0, no snapshots will be stored.
- `-e <0/1>`: Evolution method to use. If set to 0, the program will use the ordered evolution method, otherwise it will use the static evolution method.
- `-f <*char>`: The name of the `.pbm` the program will read from (if the `-r` option is used) or write to (if the `-i` option is used).
- `-t`: If used, the program will print the time (in seconds) it took to run. 



## Content of the directory

In this directory you can find the following files and directories:

- `README.md`: this file, containing the description of the assignment and the instructions to compile and run the code.
- [`main.c`](main.c): the file containing the `main` method of the program. It regards the possible arguments and calls the appropriate functions.
- [Makefile](Makefile): file used to compile the code.
- [`obj/`](obj/): directory containing the object files created during the compilation.
- [`include/`](include/): directory containing the header files. Each header file contains the declaration of the functions defined in the corresponding source file with the same name. 
- [`src/`](src/): directory containing the source files: 
    - [`initialize.c`](src/initialize.c): code executed if the program is called with the `-i` option.
    - [`read_write.c`](src/read_write.c): code that contains functions to deal with the input and output `.pbm` files.
    - [`run.c`](src/run.c): code executed if the program is called with the `-r` option.
    - [`should_live.c`](src/should_live.c): code containing the function that decides if a cell should live or die in the next generation according to the rules of the game.
    - [`static_evolution.c`](src/static_evolution.c): code executed if the program is called with the `-e 1` option.
    - [`ordered_evolution.c`](src/ordered_evolution.c): code executed if the program is called with the `-e 0` option.
- [`snaps`](snaps): directory where the program will store the snapshots of the evolution of the game if the `-s` option is used.
- [`runme.sh`](runme.sh): slurm script usable to run the code. User can modify it according to his needs.
- [`slurm-scripts`](slurm-scripts): directory containing a sample of scripts I used to assess the performance of the code on the Orfeo cluster. These scripts are not necessary to run the code, and they were modified several times to produce the results stored in the results directory.
- [`time_measurements`](time_measurements): directory which is not necessary to run the code. It contains the results of the time measurements I performed on the Orfeo cluster to assess the scalability of the code and used to produce the plots in the [report](../report.pdf).

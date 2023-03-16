The scripts in this folder are aimed to: 

- perform the `mygemm.c` code using: 
    - `OpenBlas`
    - `MKL`
    - `Blis` (This one was not available in the nodes, so I had to compile it from source)

- Checking the *scalability*:
    - at a fixed number of cores (64 for EPYC, 12 for THIN)
    - over the cores, at a fixed size (medium size matrices)

- Mapping by cores (`OMP_PLACES=cores`), check the scalability with different *binding policies*:
    - `OMP_PROC_BIND=spread`
    - `OMP_PROC_BIND=close`
    - I omitted the `OMP_PROC_BIND=master` due to time constraints of the assignment. 

For both: `DOUBLE` and `FLOAT` precision, and for both **EPYC** and **THIN** nodes.

## Results

All the results are stored in [the folder](https://github.com/IsacPasianotto/foundations_of_HPC-assignment/tree/main/Assignment2/results) `results`.\
In that folder there is a `README.md` file that explains the codification adopted for the names of the files.

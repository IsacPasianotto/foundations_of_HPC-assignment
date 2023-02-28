# logbook and to-do list

- Now the compilation in EPYC nodes is working. 

Next steps are: 

- perform the `dgemm.c` code using: 
    - `OpenBlas`
    - `MKL`
    - `Blis`  (the one I compiled by myself)

- And checking the scalability:
    - at a fixed number of cores (64 for EPYC, 12 fot THIN)
    - over the cores, at a fixed size (medium size matrices)


for both: **DOUBLE** and **FLOAT** precision, and for both **EPYC** and **THIN** nodes.




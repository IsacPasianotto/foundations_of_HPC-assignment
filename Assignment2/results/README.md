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
 

## Possible combinations

The following table summarizes all the combinations of the parameters that I have to test.
| | Library  | Precision | Node | Scalability | binding |
| --- | --------- | ---- | ----------- | ------- | ------- |
| [1](oblas-double-epyc-cores-spread.csv)| OpenBlas | Double    | EPYC | Fixed cores | spread  |
| [2](mkl-double-epyc-cores-spread.csv)  | MKL      | Double    | EPYC | Fixed cores | spread  |
| [3](blis-double-epyc-cores-spread.csv) | Blis     | Double    | EPYC | Fixed cores | spread  |
| [4](oblas-double-epyc-size-spread.csv) | OpenBlas | Double    | EPYC | Fixed size  | spread  |
| [5](mkl-double-epyc-size-spread.csv)   | MKL      | Double    | EPYC | Fixed size  | spread  |
| [6](blis-double-epyc-size-spread.csv)  | Blis     | Double    | EPYC | Fixed size  | spread  |
| [7](oblas-float-epyc-cores-spread.csv) | OpenBlas | Float     | EPYC | Fixed cores | spread  |
| [8](mkl-float-epyc-cores-spread.csv)   | MKL      | Float     | EPYC | Fixed cores | spread  |
| [9](blis-float-epyc-cores-spread.csv)  | Blis     | Float     | EPYC | Fixed cores | spread  |
| [10](oblas-float-epyc-size-spread.csv) | OpenBlas | Float     | EPYC | Fixed size  | spread  |
| [11](mkl-float-epyc-size-spread.csv)   | MKL      | Float     | EPYC | Fixed size  | spread  |
| [12](blis-float-epyc-size-spread.csv)  | Blis     | Float     | EPYC | Fixed size  | spread  |
| [13](oblas-double-epyc-cores-close.csv)| OpenBlas | Double    | EPYC | Fixed cores | close   |
| [14](mkl-double-epyc-cores-close.csv)  | MKL      | Double    | EPYC | Fixed cores | close   |
| [15](blis-double-epyc-cores-close.csv) | Blis     | Double    | EPYC | Fixed cores | close   |
| [16](oblas-double-epyc-size-close.csv) | OpenBlas | Double    | EPYC | Fixed size  | close   |
| [17](mkl-double-epyc-size-close.csv)   | MKL      | Double    | EPYC | Fixed size  | close   |
| [18](blis-double-epyc-size-close.csv)  | Blis     | Double    | EPYC | Fixed size  | close   |
| [19](oblas-float-epyc-cores-close.csv) | OpenBlas | Float     | EPYC | Fixed cores | close   |
| [20](mkl-float-epyc-cores-close.csv)   | MKL      | Float     | EPYC | Fixed cores | close   |
| [21](blis-float-epyc-cores-close.csv)  | Blis     | Float     | EPYC | Fixed cores | close   |
| [22](oblas-float-epyc-size-close.csv)  | OpenBlas | Float     | EPYC | Fixed size  | close   |
| [23](mkl-float-epyc-size-close.csv)    | MKL      | Float     | EPYC | Fixed size  | close   |
| [24](blis-float-epyc-size-close.csv)   | Blis     | Float     | EPYC | Fixed size  | close   |
| [25](oblas-double-intel-cores-spread.csv) | OpenBlas | Double    | THIN | Fixed cores | spread  |
| [26](mkl-double-intel-cores-spread.csv)   | MKL      | Double    | THIN | Fixed cores | spread  |
| [27](blis-double-intel-cores-spread.csv)  | Blis     | Double    | THIN | Fixed cores | spread  |
| [28](oblas-double-intel-size-spread.csv)  | OpenBlas | Double    | THIN | Fixed size  | spread  |
| [29](mkl-double-intel-size-spread.csv)    | MKL      | Double    | THIN | Fixed size  | spread  |
| [30](blis-double-intel-size-spread.csv)   | Blis     | Double    | THIN | Fixed size  | spread  |
| [31](oblas-float-intel-cores-spread.csv)  | OpenBlas | Float     | THIN | Fixed cores | spread  |
| [32](mkl-float-intel-cores-spread.csv)    | MKL      | Float     | THIN | Fixed cores | spread  |
| [33](blis-float-intel-cores-spread.csv)   | Blis     | Float     | THIN | Fixed cores | spread  |
| [34](oblas-float-intel-size-spread.csv)   | OpenBlas | Float     | THIN | Fixed size  | spread  |
| [35](mkl-float-intel-size-spread.csv)     | MKL      | Float     | THIN | Fixed size  | spread  |
| [36](blis-double-epyc-cores-close.csv)    | Blis     | Float     | THIN | Fixed size  | spread  |
| [37](oblas-double-intel-cores-close.csv)  | OpenBlas | Double    | THIN | Fixed cores | close   |
| [38](mkl-double-intel-cores-close.csv)    | MKL      | Double    | THIN | Fixed cores | close   |
| [39](blis-double-intel-cores-close.csv)   | Blis     | Double    | THIN | Fixed cores | close   |
| [40](oblas-double-intel-size-close.csv)   | OpenBlas | Double    | THIN | Fixed size  | close   |
| [41](mkl-double-intel-size-close.csv)     | MKL      | Double    | THIN | Fixed size  | close   |
| [42](blis-double-intel-size-close.csv)    | Blis     | Double    | THIN | Fixed size  | close   |
| [43](oblas-float-intel-cores-close.csv)   | OpenBlas | Float     | THIN | Fixed cores | close   |
| [44](mkl-float-intel-cores-close.csv)     | MKL      | Float     | THIN | Fixed cores | close   |
| [45](blis-float-intel-cores-close.csv)    | Blis     | Float     | THIN | Fixed cores | close   |
| [46](oblas-float-intel-size-close.csv)    | OpenBlas | Float     | THIN | Fixed size  | close   |
| [47](mkl-float-intel-size-close.csv)      | MKL      | Float     | THIN | Fixed size  | close   |
| [48](blis-float-intel-size-close.csv)     | Blis     | Float     | THIN | Fixed size  | close   |

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


The following table summarises what I have done so far:

| Library | Precision | Node | Scalability | Status |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Double    | EPYC | Fixed cores | **NOT** done |
| MLK     | Double    | EPYC | Fixed cores | **NOT** done |
| Blis    | Double    | EPYC | Fixed cores | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Double    | EPYC | Fixed size  | **NOT** done |
| MLK     | Double    | EPYC | Fixed size  | **NOT** done |
| Blis    | Double    | EPYC | Fixed size  | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Float     | EPYC | Fixed cores | **NOT** done |
| MLK     | Float     | EPYC | Fixed cores | **NOT** done |
| Blis    | Float     | EPYC | Fixed cores | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Float     | EPYC | Fixed size  | **NOT** done |
| MLK     | Float     | EPYC | Fixed size  | **NOT** done |
| Blis    | Float     | EPYC | Fixed size  | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Double    | THIN | Fixed cores | **NOT** done |
| MLK     | Double    | THIN | Fixed cores | **NOT** done |
| Blis    | Double    | THIN | Fixed cores | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Double    | THIN | Fixed size  | **NOT** done |
| MLK     | Double    | THIN | Fixed size  | **NOT** done |
| Blis    | Double    | THIN | Fixed size  | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Float     | THIN | Fixed cores | **NOT** done |
| MLK     | Float     | THIN | Fixed cores | **NOT** done |
| Blis    | Float     | THIN | Fixed cores | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|
| OpenBlas| Float     | THIN | Fixed size  | **NOT** done |
| MLK     | Float     | THIN | Fixed size  | **NOT** done |
| Blis    | Float     | THIN | Fixed size  | **NOT** done |

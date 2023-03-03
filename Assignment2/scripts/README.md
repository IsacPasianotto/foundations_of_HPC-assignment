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

- For the binding polycy:
    - `OMP_PLACES=cores`,  `OMP_PROC_BIND=spread`
    - `OMP_PLACES=cores`,  `OMP_PROC_BIND=close`
    - 
for both: **DOUBLE** and **FLOAT** precision, and for both **EPYC** and **THIN** nodes.

***CURRENT EXECUTABLE STATUS***: `FLOAT`+`AMD`


The following table summarises what I have done so far:

| Library | Precision | Node | Scalability | binding  | Status |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed cores | spread   | *done* |
| MKL     | Double    | EPYC | Fixed cores | spread   | *done* |
| Blis    | Double    | EPYC | Fixed cores | spread   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed size  | spread   | *done* |
| MKL     | Double    | EPYC | Fixed size  | spread   | *done* |
| Blis    | Double    | EPYC | Fixed size  | spread   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed cores | spread   | *done* |
| MKL     | Float     | EPYC | Fixed cores | spread   | *done* |
| Blis    | Float     | EPYC | Fixed cores | spread   | *done *|
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed size  | spread   | *done* |
| MKL     | Float     | EPYC | Fixed size  | spread   | *done* |
| Blis    | Float     | EPYC | Fixed size  | spread   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed cores | close   | *done* |
| MKL     | Double    | EPYC | Fixed cores | close   | *done* |
| Blis    | Double    | EPYC | Fixed cores | close   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed size  | close   | *done* |
| MKL     | Double    | EPYC | Fixed size  | close   | *done* |
| Blis    | Double    | EPYC | Fixed size  | close   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed cores | close    | *done* |
| MKL     | Float     | EPYC | Fixed cores | close    | *done* |
| Blis    | Float     | EPYC | Fixed cores | close    | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed size  | close    | *done* |
| MKL     | Float     | EPYC | Fixed size  | close    | *done* |
| Blis    | Float     | EPYC | Fixed size  | close    | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|

| OpenBlas| Double    | THIN | Fixed cores | spread   | *done* |
| MKL     | Double    | THIN | Fixed cores | spread   | *done* |
| Blis    | Double    | THIN | Fixed cores | spread   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed size  | spread   | *done* |
| MKL     | Double    | THIN | Fixed size  | spread   | *done* |
| Blis    | Double    | THIN | Fixed size  | spread   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed cores | spread   | **NOT** done / script ready |
| MKL     | Float     | THIN | Fixed cores | spread   | **NOT** done / script ready |
| Blis    | Float     | THIN | Fixed cores | spread   | **NOT** done / script ready |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed size  | spread   | **NOT** done / script ready |
| MKL     | Float     | THIN | Fixed size  | spread   | **NOT** done / script ready |
| Blis    | Float     | THIN | Fixed size  | spread   | **NOT** done / script ready |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed cores | close   | *done* |
| MKL     | Double    | THIN | Fixed cores | close   | *done* |
| Blis    | Double    | THIN | Fixed cores | close   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed size  | close   | *done* |
| MKL     | Double    | THIN | Fixed size  | close   | *done* |
| Blis    | Double    | THIN | Fixed size  | close   | *done* |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed cores | close    | **NOT** done / script ready |
| MKL     | Float     | THIN | Fixed cores | close    | **NOT** done / script ready |
| Blis    | Float     | THIN | Fixed cores | close    | **NOT** done / script ready |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed size  | close    | **NOT** done / script ready |
| MKL     | Float     | THIN | Fixed size  | close    | **NOT** done / script ready |
| Blis    | Float     | THIN | Fixed size  | close    | **NOT** done / script ready |

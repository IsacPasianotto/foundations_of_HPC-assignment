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


The following table summarises what I have done so far:

| Library | Precision | Node | Scalability | binding  | Status |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed cores | spread   | partiallydone**not** done |
| MLK     | Double    | EPYC | Fixed cores | spread   | **NOT** done |
| Blis    | Double    | EPYC | Fixed cores | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed size  | spread   | **NOT** done |
| MLK     | Double    | EPYC | Fixed size  | spread   | **NOT** done |
| Blis    | Double    | EPYC | Fixed size  | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed cores | spread   | **NOT** done |
| MLK     | Float     | EPYC | Fixed cores | spread   |**NOT** done |
| Blis    | Float     | EPYC | Fixed cores | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed size  | spread   | **NOT** done |
| MLK     | Float     | EPYC | Fixed size  | spread   | **NOT** done |
| Blis    | Float     | EPYC | Fixed size  | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed cores | close   | **NOT** done |
| MLK     | Double    | EPYC | Fixed cores | close   | **NOT** done |
| Blis    | Double    | EPYC | Fixed cores | close   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | EPYC | Fixed size  | close   | **NOT** done |
| MLK     | Double    | EPYC | Fixed size  | close   | **NOT** done |
| Blis    | Double    | EPYC | Fixed size  | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed cores | close    | **NOT** done |
| MLK     | Float     | EPYC | Fixed cores | close    |**NOT** done |
| Blis    | Float     | EPYC | Fixed cores | close    | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | EPYC | Fixed size  | close    | **NOT** done |
| MLK     | Float     | EPYC | Fixed size  | close    | **NOT** done |
| Blis    | Float     | EPYC | Fixed size  | close    | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed cores | spread   | **NOT** done |
| MLK     | Double    | THIN | Fixed cores | spread   | **NOT** done |
| Blis    | Double    | THIN | Fixed cores | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed size  | spread   | **NOT** done |
| MLK     | Double    | THIN | Fixed size  | spread   | **NOT** done |
| Blis    | Double    | THIN | Fixed size  | spread   |**NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed cores | spread   | **NOT** done |
| MLK     | Float     | THIN | Fixed cores | spread   |**NOT** done |
| Blis    | Float     | THIN | Fixed cores | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed size  | spread   | **NOT** done |
| MLK     | Float     | THIN | Fixed size  | spread   | **NOT** done |
| Blis    | Float     | THIN | Fixed size  | spread   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed cores | close   | **NOT** done |
| MLK     | Double    | THIN | Fixed cores | close   | **NOT** done |
| Blis    | Double    | THIN | Fixed cores | close   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Double    | THIN | Fixed size  | close   | **NOT** done |
| MLK     | Double    | THIN | Fixed size  | close   | **NOT** done |
| Blis    | Double    | THIN | Fixed size  | close   | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed cores | close    | **NOT** done |
| MLK     | Float     | THIN | Fixed cores | close    | **NOT** done |
| Blis    | Float     | THIN | Fixed cores | close    | **NOT** done |
|:-------:|:---------:|:----:|:-----------:|:------:|:------:|
| OpenBlas| Float     | THIN | Fixed size  | close    | **NOT** done |
| MLK     | Float     | THIN | Fixed size  | close    | **NOT** done |
| Blis    | Float     | THIN | Fixed size  | close    | **NOT** done |

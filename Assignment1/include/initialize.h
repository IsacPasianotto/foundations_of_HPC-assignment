#ifndef INITIALIZE_H
    #define INITIALIZE_H
        void initialize(char *fname, int k);
        void initialize_serial(char *fname, int k);
        void initialize_parallel(char *fname, int k, int rank, int size);
#endif // !INITIALIZE_H
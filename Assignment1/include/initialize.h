#ifndef INITIALIZE_H
#define INITIALIZE_H
    void initialize(const char *fname, unsigned const int k);
#endif

#ifndef INITIALIZE_SERIAL
#define INITIALIZE_SERIAL
    void initialize_serial(const char *fname, unsigned const int k);
#endif

#ifndef INITIALIZE_PARALLEL
#define INITIALIZE_PARALLEL
    void initialize_parallel(const char *fname, unsigned const int k, int rank, int size);
#endif

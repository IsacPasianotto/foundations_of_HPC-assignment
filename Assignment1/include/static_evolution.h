#ifndef STATIC_EVOLUTION_H
#define STATIC_EVOLUTION_H
    void run_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size);
#endif

#ifndef SERIAL_STATIC_H
#define SERIAL_STATIC_H
    void serial_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s);
#endif

#ifndef PARALLEL_STATIC_H
#define PARALLEL_STATIC_H
    void parallel_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size);
#endif
#ifndef STATIC_EVOLUTION_H
#define STATIC_EVOLUTION_H
    void run_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size);
#endif

#ifndef SERIAL_STATIC_H
#define SERIAL_STATIC_H
    void serial_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s);
#endif

#ifndef SHOLUD_ALIVE_STATIC_H
#define SHOLUD_ALIVE_STATIC_H
    char should_live_static(unsigned int k, unsigned const int i, unsigned const char *world, unsigned const int *maxVal, int rank, int size);
#endif

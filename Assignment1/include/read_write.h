#ifndef READWRITE_H
    #define READWRITE_H
       void write_pgm_serial(char *fname, int k, char* world);
       void write_pgm_parallel(char *fname, int std_size, int k, char* world, int rank, int size);
#endif // !INITIALIZE_H


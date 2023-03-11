#ifndef WRITE_H
#define WRITE_H
    void write_pbm(const void *image, const unsigned int maxval, const unsigned int xsize, const unsigned int ysize, const char *image_name);
#endif

#ifndef READ_H
#define READ_H
    void read_pbm(void **image, unsigned int *maxval, unsigned int *xsize, unsigned int *ysize, const char *image_name);
#endif
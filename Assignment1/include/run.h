#ifndef RUN_H
    #define RUN_H
        void run(char* fname, int k, int e, int n, int s);
        void run_ordered(char* fname, int k, int n, int s);
        void run_static(char* fname, int k, int n, int s, int rank, int size);
        void run_static_serial(char* fname, int k, int n, int s);
        void run_static_parallel(char* fname, int k, int n, int s, int rank, int size);
#endif // RUN_H
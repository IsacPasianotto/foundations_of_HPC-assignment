#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<mpi.h>

#include"run.h"
#include"ordered_evolution.h"
#include"static_evolution.h"
#include"read_write.h" 


// For measuring time

#if defined(_OPENMP)
    #define CPU_TIME ({struct  timespec ts; clock_gettime( CLOCK_REALTIME, &ts ),\
	    (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;})
    #define CPU_TIME_th ({struct  timespec myts; clock_gettime( CLOCK_THREAD_CPUTIME_ID, &myts ),\
	    (double)myts.tv_sec + (double)myts.tv_nsec * 1e-9;})
#else
#define CPU_TIME ({struct  timespec ts; clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ),\
    (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;})
#endif


/*
    run(): check what kind of evolution is required (-e option)
        and consequently calls the correct function.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    e:      0: ordered
            1: static evolution
    t:      should print the time taken by the function

*/
void run(const char *fname, unsigned const int k, unsigned const int n, unsigned const int s, const char e, const int t)
{
    int mpi_provided_thread_level;
    MPI_Init_thread(NULL, NULL, MPI_THREAD_FUNNELED, &mpi_provided_thread_level);
    if ( mpi_provided_thread_level < MPI_THREAD_FUNNELED )
    {
        printf("Error: MPI thread support is lower than the demanded\n");
        MPI_Finalize();
        exit(1);
    }
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (e==0)
    {   
        if (t == 0)
        {
            MPI_Finalize();
            run_ordered(fname, k, n, s);
            return;
        }
        else // t==1
        {
            double start = CPU_TIME;
            MPI_Finalize();
            run_ordered(fname, k, n, s);
            double end = CPU_TIME;
            if (rank == 0)
                printf(",%f\n", end-start);
            return;
        }
    }
    else // e==1
    {
        run_static(fname, k, n, s, rank, size, t);
        return;
    }
    return;
}


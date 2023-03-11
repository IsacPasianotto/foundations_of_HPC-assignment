#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<mpi.h>

#include"run.h"
#include"ordered_evolution.h"
#include"static_evolution.h"
#include"read_write.h" 

/*
    run(): check what kind of evolution is required and
        consequently calls the correct function.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    e:      0: ordered
            1: static evolution

*/
void run(const char *fname, unsigned const int k, unsigned const int n, unsigned const int s, const char e)
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
        MPI_Finalize();
        run_ordered(fname, k, n, s);
        return;
    }
    else
    {
        run_static(fname, k, n, s, rank, size);
        return;

    }
    return;
}


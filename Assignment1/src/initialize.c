#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<mpi.h>

#include "initialize.h"
#include "read_write.h"

/*
    initialize():   checks if the executable is runned on
        one or more processes, then consequently calls the 
        correct function to initialize the playground.
    @param
    fname:  name of the file that's going to be written 
            to initialize the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
*/
void initialize(const char *fname, unsigned const int k)
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
    if (size == 1)
    {
        MPI_Finalize();
        initialize_serial(fname, k);
        return; 
    }
    else
    {
        initialize_parallel(fname, k, rank, size);
        MPI_Finalize();
        return;
    }
}


/*
    initialize_serial():   initializes the playground
        with a random configuration of cells and writes
        the result to a file.
        The probability of a cell to be alive is 15%.
    @param
    fname:  name of the file that's going to be written 
            to initialize the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
*/
void initialize_serial(const char *fname, unsigned const int k)
{
    char *world; 
    #pragma omp parallel shared(world, k, fname)
    {
        world = (char *)malloc(k*k*sizeof(char));
        int seed = time(NULL);
        // int seed = 42;  // for testing purposes
        srand(seed);
        #pragma omp parallel for schedule(static) shared(world, k)
            for (int i = 0; i < k*k; i++)
                world[i] = rand() % 100 < 15 ? 255 : 0;
        write_pbm(world, 255, k, k, fname);
    }
    free(world);
    return; 
}


/*
    initialize_parallel():   initializes the playground
        with a random configuration of cells and writes
        the result to a file. The procedure is done in 
        parallel.
        The probability of a cell to be alive is 15%.
    @param
    fname:  name of the file that's going to be written 
            to initialize the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    rank:   rank of the process
    size:   number of processes
*/
void initialize_parallel(const char *fname, unsigned const int k, int rank, int size)
{
    int seed = time(NULL);
    // int seed = 42;  // for testing purposes
    srand(seed);
    unsigned int std_chunk, chunk;
    std_chunk = (k*k)/size;
    chunk = (rank != 0) ? std_chunk : std_chunk + (k*k)%size;
    char *world; 
    char *local_world = (char *)malloc(chunk*sizeof(char));
    #pragma omp parallel
    {
        #pragma omp parallel for schedule(static) shared(local_world, chunk)
            for (int i = 0; i < chunk; i++)
                local_world[i] = rand() % 100 < 15 ? 255 : 0;
        if (rank == 0)
            world = (char *)malloc(k*k*sizeof(char));
    MPI_Barrier(MPI_COMM_WORLD);
// needed because the read_pbn requires a pointer to an int
    MPI_Gather(local_world, chunk, MPI_CHAR, world, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
        if (rank == 0)
            write_pbm(world, 255, k, k, fname);
    } // #pragma omp parallel
    free(local_world);
    if (rank == 0)
        free(world);
    return;
} // void initialze_parallel()
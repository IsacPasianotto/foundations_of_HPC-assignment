#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<omp.h>
#include<mpi.h>

#include"initialize.h"
#include"read_write.h"


char* world; 

/*
    initialize_serial(): fill an array of char with random values
        and call the write_pgm() function to write it into the 
        desidered file. The probability than a cell starts as alive
         (value = 255) is the 25%
    @param:
    fname:  name of the file where to write the results
    k:     The size of the square-matrix the playground should be 
*/

void initialize_serial(char* fname, int k)
{
   world = (char*)malloc(k*sizeof(char));
   #pragma omp parallel
   {
        int seed = time(NULL);
        //int seed = 42;   // for debugging
        srand(seed);

        #pragma omp for
            for (int i = 1; i < k*k; i++)
                world[i] = (rand()%100<25) ? 0 : 255; 
    }
    write_pgm_serial(fname, k, world); 
}

/*
    initialize_parallel(): fill an array of char with random values
        and call the write_pgm() function to write it into the 
        desidered file
    
    @param:
    fname:  name of the file where to write the results
    k:      the size of the square-matrix the playground should be 
    rank:   the rank of the process that is executing the function
    size:   the total number of mpi-processes involved 
*/

void initialize_parallel(char* fname, int k, int rank, int size)
{
    int seed = time(NULL);
    //int seed = 42;   // for debugging
    srand(seed);

    int localRows_lenght; 
    int std_size = k*k/size;
    localRows_lenght = (rank!=size-1) ? std_size: std_size + k*k%size;
    char* localWorld = (char*)malloc(localRows_lenght*sizeof(char));

    MPI_Barrier(MPI_COMM_WORLD);
    #pragma omp parallel
    {
        #pragma omp for schedule(static, 1)
            for (int i = 0; i < localRows_lenght; i++)
                localWorld[i] = (rand()%100<25) ? 0 : 255;
    } 
    write_pgm_parallel(fname, std_size, localRows_lenght, localWorld, rank, size);
}

/*
    initialize(): check if the executable is running on 
        one or more mpi-tasks, and consequently invoke the 
        right function initizlize_parallel() or initialize_serial()
    
    @param:
    fname:  name of the file that's need to be initialized, which
            will rappresent the playground
    k:      The size of the square-matrix the playground should be 
*/

void initialize(char* fname, int k)
{
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size > 1)
    {
        initialize_parallel(fname, k, rank, size);
    }
    else
    {
        MPI_Finalize();
        initialize_serial(fname, k);
        return;
    }
    MPI_Finalize();
}
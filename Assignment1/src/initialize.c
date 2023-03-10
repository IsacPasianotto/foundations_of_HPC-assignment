#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<omp.h>
#include<mpi.h>

#include"initialize.h"
#include"read_write_pgn.h"
char* world; 

/*
    initialize_serial(): fill an array of char with random values
        and call the write_pgm() function to write it into the 
        desidered file. The probability than a cell starts as alive
         (value = 255) is the 20%
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
            for (int i = 0; i < k*k; i++)
                world[i] = (rand()%100<5) ? 255 : 0; 
    }
    write_pgm_image(world, 255, k, k, fname); 
}

/*
    initialize_parallel(): fill an array of char with random values
        and call the write_pgm() function to write it into the 
        desidered file.  The probability than a cell starts as alive
        (value = 255) is the 20%
    
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
    localRows_lenght = (rank!=0) ? std_size: std_size + k*k%size;
    char* localWorld = (char*)malloc(std_size*std_size*sizeof(char));

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 1)
            for (int i = 0; i < localRows_lenght; i++)
                localWorld[i] = (rand()%100<5) ? 255 : 0;
    }
    char* world; 
    if (rank == 0)
        world = (char*)malloc(k*k*sizeof(char));
    MPI_Barrier(MPI_COMM_WORLD);
    // MPI_Gather(localWorld, localRows_lenght, MPI_CHAR, world, localRows_lenght, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Gather(localWorld, localRows_lenght, MPI_CHAR, world, localRows_lenght, MPI_CHAR, 0, MPI_COMM_WORLD);
    // char* world = (char*)malloc(k*k*sizeof(char));
    // char* remaing = (char*)malloc(k*k%size*sizeof(char));
    // the last process will have to take care of the remaining cells
    
    if (rank == 0)
        write_pgm_image(world, 255, k, k, fname);
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
        printf("finito di inizializzare il mondo\n");
        MPI_Finalize();
        return; 
    }
    else
    {
        MPI_Finalize();
        initialize_serial(fname, k);
        printf("finito di inizializzare il mondo\n");
        return;
    }
}
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<mpi.h>

#include"static_evolution.h"
#include"ordered_evolution.h"
#include"read_write.h"

// needed because the read_pbn requires a pointer to an int
unsigned int smval;                   
unsigned int *smaxVal = &smval;

/*
    run_static():   performs the static evolution of the playground
        and saves the result to a file.
        Static evolution means that the evolution of the playground
        is computed in a parallel way, so that the evolution of
        the playground is computed by all the processes at the same time.
        note: the static evolution can be performed only in parallel.
        For this reason, a check is needed to verify if the program is
        executed in parallel or not.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    rank:   rank of the process
*/
void run_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size)
{
    if (size > 1) 
    {
        parallel_static(fname, k, n, s, rank, size);
        MPI_Finalize();
        return;
    } else
    {
        MPI_Finalize();
        serial_static(fname, k, n, s);
        return;
    }
}


/*
    serial_static():   performs the static evolution of the playground
        and saves the result to a file.
        This function is called only if the program is executed in serial.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
*/
void serial_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s)
{
    /*
        read the initial state of the playground from the file
    */
    unsigned char *yesterday; 
    unsigned char *today;
    #pragma omp parallel 
    {
        yesterday = malloc(k*k*sizeof(char));
        read_pbm((void**)&yesterday, smaxVal, &k, &k, fname);
    }
    #pragma omp barrier
    #pragma omp for
    for (unsigned int day = 0; day < n; day++)
    {
        #pragma omp parallel
        {
            today = malloc(k*k*sizeof(char));
        }
        /*
            compute the evolution of the playground and 
            decide if a cell should alive or dead
        */
        #pragma omp parallel for schedule(static) firstprivate(k, smaxVal)
        for (unsigned int i = 0; i < k*k; i++)
            today[i] = should_live_serial(k, i, yesterday, smaxVal);
        unsigned char *tmp = yesterday;
        yesterday = today;
        today = tmp;
        free(today);
        /*
            check if it's time to save a snapshot of the playground
            and do it if it's needed
        */
        if (s==0)
            continue;
        if (day%s == 0)
        {
            char *snapname = malloc(24*sizeof(char)); // 24 = length of "snaps/snapshot_%06d.pbm"
            sprintf(snapname, "snaps/snapshot_%06d.pbm", day);
            #pragma omp parallel
            {
                write_pbm((void*)yesterday, smval, k, k, snapname);
            }
            free(snapname);
        }
        
    }
    char *filename = malloc (21*sizeof(char));
    sprintf(filename, "game_of_life_END.pbm");
    #pragma omp parallel
    {
        write_pbm((void*)yesterday, smval, k, k, filename);
    }
    free(filename);
    free(yesterday);
    return;
} // void run_static()


/*
    parallel_static():   performs the static evolution of the playground
        and saves the result to a file.
        This function is called only if the program is executed in parallel.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    rank:   rank of the process
    size:   number of processes
*/
void parallel_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size)
{
    // int prev, next;
    // prev = rank==0 ? size-1 : rank-1;
    // next = rank==size-1 ? 0 : rank+1;

    // Root reads the initial state of the playground amd sends it to the other processes

    unsigned char *world; 
    world = malloc(k*k*sizeof(char));
    if (rank ==0)
    {
        read_pbm((void**)&world, smaxVal, &k, &k, fname);
        // need to pass world to all the processes
        MPI_Bcast(world, k*k*sizeof(char), MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Calculate the size each process must handle
    unsigned int local_len = k*k/size;
    // equally distribute the remaining cells to the first processes
    if (local_len*size < k*k && rank < k*k-local_len*size)
        local_len++;
    
    
    unsigned int *offset = malloc(size*sizeof(unsigned int));
    int *lenghts = malloc(size*sizeof(int));
    
    for (int j = 0; j < size; j++) //temporary needed in the nex loop
        {
            lenghts[j] = k*k/size;
            if (lenghts[j]*size < k*k && j < k*k-lenghts[j]*size)
                lenghts[j]++;
        }
    for (int i = 0; i < size; i++) 
    {   
        offset[i] = i*lenghts[i];  
    }

    unsigned char *local_world_next;
    unsigned char *world_next;
    /*
        Start the actual game of life
    */
    for (unsigned int day = 0; day < n; day++)
    {
        local_world_next = malloc(local_len*sizeof(char));
        for (unsigned int i = 0; i < local_len; i++)
            local_world_next[i] = should_live_parallel(world, k, i, smaxVal, offset, rank);
    
    
    // all processes send their world_next to the root
    // and the root collects them in the world_next array
    if (rank == 0)
        world_next = malloc(k*k*sizeof(char)); 
    
    // to use MPI_Gatherv I need to know the lenght of each process
    // and the offset of each process in the world_next array
    MPI_Gatherv(local_world_next, local_len, MPI_UNSIGNED_CHAR, world_next, lenghts, (int*)offset, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    // check if it's time to save a snapshot of the playground
    // and do it if it's needed
    if (rank == 0)
    {
        if (s != 0 && day%s == 0)
        {
            char *snapname = malloc(24*sizeof(char)); // 24 = length of "snaps/snapshot_%06d.pbm"
            sprintf(snapname, "snaps/snapshot_%06d.pbm", day);
            write_pbm((void*)world_next, smval, k, k, snapname);
            free(snapname);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    // swap the two arrays
    unsigned char *tmp = world;
    world = world_next;
    world_next = tmp;
    }
    // write the final state of the playground to a file
    if (rank == 0)
    {
        char *filename = malloc (21*sizeof(char));
        sprintf(filename, "game_of_life_END.pbm");
        write_pbm((void*)world, smval, k, k, filename);
        free(filename);
        free(world);
    }
}


unsigned char should_live_parallel(unsigned const char* world, unsigned int k, unsigned int j, unsigned int *smaxVal, unsigned int* offset, int rank)
{
    // same logic as in serial version but I need to 
    // "adjust" the index of the cells

    unsigned int i = j + rank*offset[rank];  //adjustement of the index
    

    int result = 0;   // char is not enough to store the first sum
    register unsigned const int row = i/k;
    register unsigned const int col = i%k;
    result  = world[(k+row-1)%k*k + (k+col-1)%k]  // top left
            + world[(k+row+0)%k*k + (k+col-1)%k]  // top middle
            + world[(k+row+1)%k*k + (k+col-1)%k]  // top right
            + world[(k+row-1)%k*k + (k+col+0)%k]  // middle left
            + world[(k+row+1)%k*k + (k+col+0)%k]  // middle right
            + world[(k+row-1)%k*k + (k+col+1)%k]  // bottom left
            + world[(k+row+0)%k*k + (k+col+1)%k]  // bottom middle
            + world[(k+row+1)%k*k + (k+col+1)%k]; // bottom right
    result /= (*smaxVal);
    result = ((result == 2) || (result == 3)) ? *smaxVal : 0;
    return (char)result;

}
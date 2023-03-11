#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<mpi.h>

#include"ordered_evolution.h"
#include"read_write.h"

// needed because the read_pbn requires a pointer to an int
unsigned int omval;                   
unsigned int *omaxVal = &omval;

/*
    run_ordered():  performs the ordered evolution of the playground
        and saves the result to a file.
        Ordered evolution means that the evolution of the playground
        is computed in a sequential way, so that the evolution of
        the playground is computed by one process at a time and the
        next process can start to compute the evolution only when
        the previous one has finished.
        note: the ordered evolution can be performed only in serial
        for the point of view of MPI.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    rank:   rank of the process
    size:   number of processes
*/
void run_ordered(const char *fname, unsigned int k, unsigned const int n, unsigned const int s) 
{
    /*
        read the initial state of the playground from the file
    */
    unsigned char *world; 
    #pragma omp parallel 
    {
        world = malloc(k*k*sizeof(char));
        read_pbm((void**)&world, omaxVal, &k, &k, fname);
    }
    #pragma omp barrier   
    #pragma omp for schedule(static) 
    for(unsigned int day = 0; day < n; day++)
    {
        /*
            compute the evolution of the playground and 
            decide if a cell should alive or dead
        */
        #pragma omp parallel for schedule(static) firstprivate(k, omaxVal)
        for (unsigned int i = 0; i < k*k; i++)
            world[i] = should_live_serial(k, i, world, omaxVal);
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
                write_pbm((void*)world, omval, k, k, snapname);
            }
            free(snapname);
        }
    } // for (int day)
    char *filename = malloc (21*sizeof(char));
    sprintf(filename, "game_of_life_END.pbm");
    #pragma omp parallel
    {
        write_pbm((void*)world, omval, k, k, filename);
    }
    free(filename);
    free(world);
    return;
} // void run_ordered()


/*
    should_live_serial():  check if a cell should live or die in the 
        next generation of the playground. 
        This is the serial implementation of the function.
    @param
    k:      size of the squre matrix that's going to rapresent
            the playground
    i:      index of the cell to check
    world:  pointer to the playground
    maxVal: pointer to the maximum value of the playground
    @return
    &maxVal: the cell should live
    0:       the cell should die
*/

char should_live_serial(unsigned const int k, unsigned const int i, unsigned const char *world, unsigned const int *maxVal)
{
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
    result /= (*maxVal);
    result = ((result == 2) || (result == 3)) ? *maxVal : 0;
    return (char)result;
} // char should_live_serial()
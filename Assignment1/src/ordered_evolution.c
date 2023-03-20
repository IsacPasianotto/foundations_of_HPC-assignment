#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<mpi.h>

#include"ordered_evolution.h"
#include"should_live.h"
#include"read_write.h"

// needed because the read_pbn requires a pointer to an int
unsigned int omval;                   
unsigned int *omaxVal = &omval;

/*
    run_ordered():  performs the ordered evolution of the playground
        and saves the result to a file.
        Ordered evolution means that the evolution of the playground
        is computed evaluating the next state of a cell and updating 
        it before moving to the next cell.
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
    
    world = malloc(k*k*sizeof(char));
    read_pbm((void**)&world, omaxVal, &k, &k, fname);
    for(unsigned int day = 0; day < n; day++)
    {
        /*
            compute the evolution of the playground and 
            decide if a cell should alive or dead
        */
        #pragma omp parallel for schedule(static)
        for (unsigned long i = 0; i < k*k; i++)
            world[i] = should_live(k, i, world, omaxVal);
        /*
            check if it's time to save a snapshot of the playground
            and do it if it's needed
        */
        if (s==0)
            continue;
        if (day%s == 0)
        {
            
            char *snapname = malloc(31*sizeof(char)); // 31 = length of "snaps/snapshot_%06d.pbm"
            sprintf(snapname, "snaps/snapshot_%06d.pbm", day); 
            write_pbm((void*)world, omval, k, k, snapname);
            free(snapname);
        }
    } // for (int day)
    char *filename = malloc (21*sizeof(char));
    sprintf(filename, "game_of_life_END.pbm");
    write_pbm((void*)world, omval, k, k, filename);
    free(filename);
    free(world);
    return;
} // void run_ordered()


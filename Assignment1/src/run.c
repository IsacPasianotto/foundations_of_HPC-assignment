#include<stdio.h>
#include<stdlib.h>

#include<omp.h>
#include<mpi.h>

#include"run.h"
#include"read_write_pgn.h"












    /*
    
        COUNTING THE NEIGHBOURS

        Remeber that the playground is a torus...

        0   1    2    ....  k-1
        k   k+1  k+2  ....  2k-1
        2k  2k+1 2k+2 ....  3k-1
        ... ...  ... ...   ...
        (k-1)k (k-1)k+1 ... k^2-1

        top row:  [0, n-1]
        bottom row: [n*(n-1), n^2-1]
        left column:  [k%n == 0]
        right column: [k%(n-1) == 0]
    
    */

/*  
    count_neighbours(): count the number of neighbours of a cell
        in a given world. The playground is a torus. 
    @param:
    world:  the world where to count the neighbours
    k:      the size of the square-matrix the playground should be
    i:      the index of the cell to count the neighbours
*/
char count_neighbours_allWorld(char* world, int k, int i)
{
    char total = 0;
        // top
        total += (i < k) ? world[k*(k-1) + i] : world[i-k];
        // bottom
        total += (i >= k*(k-1)) ? world[i-k*(k-1)] : world[i+k];
        // left
        total += (i%k == 0) ? world[i+k-1] : world[i-1];
        // right
        total += (i%k == k-1) ? world[i-k+1] : world[i+1];
        // top-left
        if (i < k)
            total += (i%k == 0) ? world[k*k-1] : world[k*(k-1) + i-1];
        else
            total += (i%k == 0) ? world[i-1] : world[i-k-1];
        //  top-right
        if (i < k)
            total += (i==k-1) ? world[k*(k-1)] : world[k*(k-1) + i+1];
        else
            total += (i%k == k-1) ? world[i-2*k + 1] : world[i-k+1];
        // bottom-left
        if (i >= k*(k-1))
            total += (i==k*(k-1)) ? world[k-1] : world[i-k*(k-1)-1];
        else
            total += (i%k == 0) ? world[i+2*k-1] : world[i+k-1];
        // bottom-right
        if (i >= k*(k-1))
            total += (i==k*k-1) ? world[0] : world[i-k*(k-1)+1];
        else
            total += world[i+k+1];
    return total;
} 
























/*
    run_ordered(): perform the ordered evolution of the game of life
        and write the results into the desidered file
        Ordered evoluttion menas that the evolution is performed
        in a sequential way, so that the next step is computed
        only after the previous one has been completed. 
        Note:  this kind of evolution is not parallelizable
    @param:
    fname:  name of the file where to write the results
    k:      the size of the square-matrix the playground should be
    n:      the number of steps to be performed
    s:      every how many steps the program should write a snapshot of the playground
*/
void run_ordered(char* fname, int k, int n, int s)
{
    printf("Ordered evolution\n");
    
    char* world = (char*)malloc(k*k*sizeof(char));
//    void* world2 = (void*)malloc(k*k*sizeof(char));
    int mval=255;
    int* maxVal = &mval;

    // Just because read_pgm_image() needs pointers...
    read_pgm_image((void**)&world  ,maxVal,  &k, &k, fname);

    for (int day = 0; day < n; day++)
    {
        // each cell has 8 neighbours and they are updated progressively 
        
        for (int i = 0; i < k*k; i++)
        {
            // count the number of alive neighbours
            char alive_neighbours;
            alive_neighbours = count_neighbours_allWorld(world, k, i);
        
            // decide if a cell will be alive or dead in the next step
             world[i] = ((alive_neighbours == -3) || (alive_neighbours == -2)) ? 255: 0;
       }

        if (s==0) // s = 0 means we don't want to write any snapshot
            continue;

       if (day%s == 0)
       {
            char* filename = (char*)malloc(k*k*sizeof(char));
            sprintf(filename, "day%d.pbm", day);
            write_pgm_image(world, 255, k, k, filename);
            free(filename);
       }  // end if
    } // end for day
} // end run_ordered

/*
    run_static(): perform the static evolution of the game of life
        and write the results into the desidered file
        Static evoluttion menas that first the programm computes for
        each cell the number of alive neighbours and decides if the
        cell will be alive or dead in the next step. Only after that
        the playground is updated. 
    @param:
    fname:  name of the file where to write the results
    k:      the size of the square-matrix the playground should be
    n:      the number of steps to be performed
    s:      every how many steps the program should write a snapshot of the playground
    rank:   the rank of the process
    size:   the number of processes
*/

void run_static(char* fname, int k, int n, int s, int rank, int size)
{
    // two differet functions depending on the number of mpi processes
    if (size == 1)
        run_static_serial(fname, k, n, s);
    else
        run_static_parallel(fname, k, n, s, rank, size);       
}

void run_static_serial(char* fname, int k, int n, int s)
{
    printf("run_static_serial\n");
    char* world = (char*)malloc(k*k*sizeof(char));
    char* should_live = (char*)malloc(k*k*sizeof(char));
    int mval=255;
    int* maxVal = &mval; 
    read_pgm_image((void**)&world  , maxVal,  &k, &k, fname);
    
    for (int day = 0; day < n; day++)
    {
        for (int i = 0; i < k*k; i++)
        {
            char alive_neighbours = count_neighbours_allWorld(world, k, i);
            should_live[i] = (alive_neighbours == -3 || alive_neighbours == -2) ? 255 : 0;
            printf("at i = %d, world is: %c\n", i, world[i]);
            printf("at i = %d, should live is: %c\n" , i, should_live[i]);
        }
        for (int i = 0; i < k*k; i++)
            world[i] = should_live[i];
        if (s==0) // s = 0 means we don't want to write any snapshot
            continue;
        if (day%s == 0)
        {
            char* filename = (char*)malloc(k*k*sizeof(char));
            sprintf(filename, "day%d.pbm", day);
            write_pgm_image(world, 255, k, k, filename);
            free(filename);
        }  // end if    
    }    
    free(should_live);
    free(world);
}

void run_static_parallel(char* fname, int k, int n, int s, int rank, int size)
{
    printf("run_static_parallel\n");
}



/*
    run(): Check if the evolution is ordered or static and call the 
        corresponding function
    @param:
    fname:  name of the file where to write the results
    k:      the size of the square-matrix the playground should be
    e:      the number of evolution to perform: 
            0: "ordered" evolution
            1: "static" evolution
    n:      the number of steps to be performed
    s:      every how many steps the program should write a snapshot of the playground
*/
void run (char* fname, int k, int e, int n, int s)
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);    
    if (e == 0)
        run_ordered(fname, k, n, s);
    else if (e == 1)
        run_static(fname, k, n, s, rank, size);
    
    MPI_Finalize();
    return;
}
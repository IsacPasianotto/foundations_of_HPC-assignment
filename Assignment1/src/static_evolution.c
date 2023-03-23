#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<mpi.h>

#include"static_evolution.h"
#include"should_live.h"
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



// needed because the read_pbn requires a pointer to an int
unsigned int smval;                   
unsigned int *smaxVal = &smval;

/*
    run_static():   performs the static evolution of the playground
        and saves the result to a file.
        Static evolution means that the evolution of the playground
        is done "freezing" the playground in the current state and
        and computing for each cell if it should be alive or dead.
        The update of the playground is done at the end of the computation.
    @param
    fname:  name of the file containing the initial state of the playground
    k:      size of the squre matrix that's going to rapresent
            the playground
    n:      number of generations must be computed
    s:      every how many generations save a snapshot
    rank:   rank of the process
    size:   number of processes
    t:      should print the time of the computation
*/
void run_static(const char *fname, unsigned int k, unsigned const int n, unsigned int s, int rank, int size, const int t)
{
    if (size > 1) 
    {   
        if (t == 0)
        {
            parallel_static(fname, k, n, s, rank, size);
            MPI_Finalize();
            return;
        } else // t == 1
        {
            double start = CPU_TIME;
            parallel_static(fname, k, n, s, rank, size);
            double end = CPU_TIME;
            if (rank == 0)
                printf(",%f\n", end-start);
            MPI_Finalize();
            return;
        }
    } else // size == 1
    {
        if (t ==0)
        {
            MPI_Finalize();
            serial_static(fname, k, n, s);
            return;
        }
        else // t == 1
        {
            double start = CPU_TIME;
            MPI_Finalize();
            serial_static(fname, k, n, s);
            double end = CPU_TIME;
            printf(",%f\n", end-start);
            return;
        }
    }
}


/*
    serial_static():   performs the static evolution of the playground
        and saves the result to a file.
        This function is called only if the program is executed on a 
        single process.
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
    yesterday = malloc(k*k*sizeof(char));
    read_pbm((void**)&yesterday, smaxVal, &k, &k, fname);
    
    for (unsigned int day = 0; day < n; day++)
    {
        today = malloc(k*k*sizeof(char));
        /*
            compute the evolution of the playground and 
            decide if a cell should alive or dead
        */
        #pragma omp parallel for schedule(static)
        for (unsigned long i = 0; i < k*k; i++)
            today[i] = should_live(k, i, yesterday, smaxVal);
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
            char *snapname = malloc(31*sizeof(char)); // 25 = length of "snaps/snapshot_%06d.pbm"
            sprintf(snapname, "snaps/snapshot_%06d.pbm", day);
            write_pbm((void*)yesterday, smval, k, k, snapname);
            free(snapname);
        }
        
    } // for (unsigned int day = 0; day < n; day+)
    char *filename = malloc (21*sizeof(char));
    sprintf(filename, "game_of_life_END.pbm");
    write_pbm((void*)yesterday, smval, k, k, filename);
    free(filename);
    free(yesterday);
    return;
} // void run_static()


/*
    parallel_static():   performs the static evolution of the playground
        and saves the result to a file.
        This function is called only if the program is executed on more
        than one process.
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
    /*
        Every process reads the initial configuration
        of the playground from the file autonomously 
    */
    unsigned char *world;
    
    world =malloc(k*k*sizeof(unsigned char));
    read_pbm((void **)&world, smaxVal, &k, &k, fname); 

    /*
        Some needed variables to organize the parallel
        computation. 
        local_len:  number of cells that each process is going to compute
        offset:     offset of the local playground w.r.t. the global one
    */
    unsigned long local_len = k*k/size;
    if (local_len*size < k*k && rank < k*k-local_len*size) 
        local_len++;                                        
    
    unsigned int *offset = malloc(size*sizeof(unsigned long));
    unsigned int *lengths = malloc(size*sizeof(unsigned int));
    for (unsigned long i = 0; i < size; i++)
    {                               
        lengths[i] = k*k/size;
        if (lengths[i]*size < k*k && i < k*k-lengths[i]*size)
            lengths[i]++;
        offset[i] = i == 0 ? 0 : offset[i-1]+lengths[i-1]; 
    }

    unsigned char *my_partial_result = malloc(lengths[rank]*sizeof(unsigned char));


    for (unsigned int day = 0; day < n; day++)
    {

        MPI_Barrier(MPI_COMM_WORLD); // wait for everyone to be ready 
        /*
            Each process computes the evolution of its
            local fragment of the playground. 
            Then every process sends its result to all the others
        */
        #pragma omp parallel for schedule(static)
        for (unsigned long i = 0; i < lengths[rank]; i++)
            my_partial_result[i] = should_live(k, i+offset[rank], world, smaxVal);

       MPI_Allgatherv((void *)my_partial_result, lengths[rank], MPI_UNSIGNED_CHAR, (void *)world, (int *)lengths, (int *)offset, MPI_UNSIGNED_CHAR, MPI_COMM_WORLD);

       
        /*
            check if it's time to save a snapshot of the playground
            and do it if it's needed
        */
        if (rank == 0)
        {
            if ((s!=0) && ( day%s == 0))
            {
                char *snapname = malloc(31*sizeof(char));
                sprintf(snapname, "snaps/snapshot_%06d.pbm", day);
                write_pbm((void*)world, smval, k, k, snapname);
                free(snapname);
            }
        } // if (rank == 0)
    } // for (day = 0; day < n; day++)

    /*
        The master process saves the final state of the playground
        into a file
    */
    if (rank == 0)
    {
        char *filename = malloc (21*sizeof(char));
        sprintf(filename, "game_of_life_END.pbm");
        write_pbm((void*)world, smval, k, k, filename);
        free(filename);
    }
    free(world);
    free(my_partial_result);
    free(offset);
    free(lengths);
    return; 
} // void parallel_static()

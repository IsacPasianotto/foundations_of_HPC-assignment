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
        printf("Error: static evolution is not implemented for parallel execution YET\n");
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
    if(omp_get_num_threads() > 1) 
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
    } // if(omp_get_num_threads() > 1) 
    else  
    {
        unsigned char *yesterday; 
        unsigned char *today;
        yesterday = malloc(k*k*sizeof(char));
        read_pbm((void**)&yesterday, smaxVal, &k, &k, fname);
        for (unsigned int day = 0; day < n; day++)
        {
            today = malloc(k*k*sizeof(char));
            for (unsigned int i = 0; i < k*k; i++)
                today[i] = should_live_serial(k, i, yesterday, smaxVal);
            unsigned char *tmp = yesterday;
            yesterday = today;
            today = tmp;
            free(today);
            if (s==0)
                continue;
            if (day%s == 0)
            {
                char *snapname = malloc(24*sizeof(char)); 
                sprintf(snapname, "snaps/snapshot_%06d.pbm", day);
                write_pbm((void*)yesterday, smval, k, k, snapname);
                free(snapname);
            }
            
        }
        char *filename = malloc (21*sizeof(char));
        sprintf(filename, "game_of_life_END.pbm");
        write_pbm((void*)yesterday, smval, k, k, filename);
        free(filename);
        free(yesterday);
        return;
    }// if(omp_get_num_threads() = 1)
} // void run_static()
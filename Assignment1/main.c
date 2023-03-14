#include<stdio.h>
#include<stdlib.h>
#include<getopt.h> 
#include<time.h>
#include<omp.h>
#include<mpi.h>


#include "initialize.h"
#include "run.h"


#define INITIALIZE 1                    // for -i / -r : initialize or run
#define RUN 2
#define ORDERED 0                       // for -e : ordered or static evolution
#define STATIC 1
#define K_DEFAULT 100                   // for -k : plyaground size
#define N_DEFAULT 10                    // for -n : number of generations
#define S_DEFAULT 0                     // for -s : every how many generations save a snapshot
#define TIME_DEFAULT 0                  // for -t : should measure time or not
#define F_DEFAULT "game_of_life.pbm"    // for -f : file name



// variables for command line arguments:

char action, e; 
unsigned int k = K_DEFAULT;
unsigned int n = N_DEFAULT;
unsigned int s = S_DEFAULT;
char *fname = NULL;
int t = TIME_DEFAULT;


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

/*
    The structure of the main method is based on the code given 
    by the professor in the assignment description. 
    Original code can be found here:
    https://github.com/Foundations-of-HPC/Foundations_of_HPC_2022/blob/main/Assignment/exercise1/get_args.c
*/
int main(int argc, char *argv[])
{
    char* optstring = "irk:e:f:n:s:t";    
    int c; 
    while ((c = getopt(argc, argv, optstring)) != -1)
    {
        switch (c)
        {
            case 'i':
                action = INITIALIZE;
                break;
            case 'r':
                action = RUN;
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 'e':
                e = atoi(optarg);
                break;
            case 'f':
                fname = (char*)malloc(25*sizeof(char)); //should be enough
                sprintf(fname, "%s", optarg);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 't':
                t = 1; 
                break;
            default :
                printf("argument -%c not known\n", c );
                break;  
        } // switch
    } // while getop


    // check about the parameters:

    if (action != INITIALIZE && action != RUN)
    {
        printf("To run the program, the user must specify either -i or -r  option\n");
        return 0;
    }
    if (fname == NULL)
    {
        fname = (char*)malloc( sizeof(char)*17 );     
        sprintf(fname, "%s", F_DEFAULT);
    }
    if (e != ORDERED && e != STATIC)
    {
        printf("The user must specify either -e 0 or -e 1\n");
        printf("-e 0 means ordered evolution, -e 1 means static evolution\n");
        return 0;
    }

    // do what the user asked for:

    if (t == 1)
    {
         if (action == INITIALIZE)
        {
            double start = CPU_TIME;
            initialize(fname, k); 
            double end = CPU_TIME;
            printf("Time for initialization: %f\n", end-start);
        }
        if (action == RUN)
        {
            double start = CPU_TIME;
            run(fname, k, n, s, e);
            double end = CPU_TIME;
            printf("Time for evolution: %f\n", end-start);
        }
    }
    else
    {
        if (action == INITIALIZE)
            initialize(fname, k);
        if (action == RUN)
            run(fname, k, n, s, e);
    }
    free(fname);
    return 0;

}// main 
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>  //for getopt() 

// for parallelism
#include<omp.h>
#include<mpi.h>

// my header files 
#include "initialize.h"
#include "read_write_pgn.h"
#include "run.h"

/*

        directives pasted from the prof's code: 

*/

// for the action of the program
#define INITIALIZE 1
#define RUN 2

// for the -e option (evolution type)
#define ORDERED 0
#define STATIC 1

// for the -k option (playground size)
#define K_DEFAULT 100

// for the -t options (time): 
#define TIME_DEFAULT 0  


// for the -f option (file name of the file that has to be read/written)
char fname_default[] = "game_of_life.pbm";

// variables I need
int action = 0;
int k = K_DEFAULT;
int e = ORDERED;
int n = 10000;
int s = -1;
char *fname = NULL;
int t = TIME_DEFAULT;

/*

        MAIN METHOD

        fatto più o meno copia incolla del codice get_args.c del prof

*/

int main(int argc, char *argv[])
{
    int action = 0; // I don't know if I need this here, but I'll leave it here for now
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
                fname = (char*)malloc( 25*sizeof(char) );     
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
                printf("Time option selected\n");
                break;
            default :
                printf("argument -%c not known\n", c );
                break;  
        } // switch
    } // while 

    // DO WHAT IT'S ASKED TO DO NOW: 

    
    // check if the user specified either -i or -r
    
    if (action != INITIALIZE && action != RUN)
    {
        printf("To run the program, the user must specify either -i or -r  option\n");
        return 0;
    }
    // check if the user specified -f
    if (fname == NULL)
    {
        fname = (char*)malloc( sizeof(fname_default)+1 );     
        sprintf(fname, "%s", fname_default);
    }

    // INITIALIZATION     
    if (action == INITIALIZE)
    {
       initialize(fname, k); 
    }

    // RUN
    if (action == RUN)
    {
        // check if the user specified -e
        if (e != ORDERED && e != STATIC)
        {
            printf("The user must specify either -e 0 or -e 1\n");
            printf("-e 0 means ordered evolution, -e 1 means static evolution\n");
            return 1;
        }
        printf("Running the game of life ...\n");
        run(fname, k, e, n, s);
    }


    free(fname);
    return 0;

} // main 
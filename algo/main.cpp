#include "set.h"
#include "lib.h"
#define  MAX_ARGS 10

Set input;              //* Input subset    
int IDEAL_SET;          //* Element's sum of ideal partitioned subset
int ARGS[MAX_ARGS];     //* Command line arguments
int GC,IC;              //* Generation counter, Iteration counter
extern Individual BEST_IND;

int main(int argc, char* argv[]){

    Generation generation;
    int ELEMENTS_TOTAL  = 0;
    int *el             = NULL;
    long long total_sum = 0;
    
    parse_args(argv, argc);

    /* Parsing file with initial set */
    el = load_from_file("input.txt", &ELEMENTS_TOTAL);

    /* Initial set creation */
    Set initial_set(el,ELEMENTS_TOTAL);
    input = initial_set;

    /* Counting params for evaluation function */
    total_sum = initial_set.sum();
    IDEAL_SET = total_sum / ARGS[SUBSETS];

    /* MAIN LOOP */
    for(IC=0; IC<ARGS[ITER] ; IC++){
        generation = random_generation(initial_set);            //*Generate initial generation
        
        for(GC=0; GC<ARGS[MAX_GEN]; GC++){
            generation = evolve(generation);                    //*Create n+1 generation from n generation
            if( generation == NULL )                            
                goto end;
        }

    }

    end: {
        free(el);
        save_to_file("output.txt",BEST_IND);
        return 0;
    }
}

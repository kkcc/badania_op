#include "set.h"
#include "lib.h"
#define  MAX_ARGS 10

Set input;  //input subset    
int IDEAL_SET;
int ARGS[MAX_ARGS];
int GC,IC;

int main(int argc, char* argv[]){

    Generation generation;
    int ELEMENTS_TOTAL = 0;
    int *el;
    long long total_sum = 0;
    
    parse_args(argv, argc);

    /* wczytywanie z pliku */
    el = load_from_file("input.txt", &ELEMENTS_TOTAL);

    /* tworzenie zbioru */
    Set initial_set(el,ELEMENTS_TOTAL);
    input = initial_set;

    free(el);

    total_sum = initial_set.sum();
    IDEAL_SET = total_sum / ARGS[SUBSETS];

    std::cout<<"Total sum    : "<<total_sum<<"\n";
    std::cout<<"Ideal subset : "<<total_sum/ARGS[SUBSETS]<<"\n";

    /* MAIN LOOP */
    for(IC=0; IC<ARGS[ITER] ; IC++){
    std::cout<<"//////////////////// GENERATION "<<IC+1<<"."<<"0"<<" \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";

        generation = random_generation(initial_set);            //*Generate initial generation
            //* 
            for(GC=0; GC<ARGS[MAX_GEN]; GC++){
                std::cout<<"//////////////////// GENERATION "<<IC+1<<"."<<GC+1<<" \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
                    printf("CURRENT BEST :\n");
                    print_ind(generation[0]);
                    printf("\n\n");
                generation = evolve(generation);
                if( generation == NULL )
                    goto end;
            }

    }

    end: return 0;
}

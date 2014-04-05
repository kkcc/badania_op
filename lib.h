#ifndef MY_AWSOME_LIB_H
    #define MY_AWSOME_LIB_H
        
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <fstream>
    
    #include "set.h"

    #define ELEMENTS_TOTAL 15
    #define MAX_GENERATIONS 50         //depth of generation tree to be derived from initial generation
    #define SUBSETS 6                  //number of subsets to which main set will be partitioned
    #define ITERATIONS 20              //maximal number of iterations = number of initial generations
    #define INDIVIDUALS 15             //number of individuals in each generation
    #define SURVIVORS 0.10

extern int IDEAL_SET;


typedef Set** Generation;
typedef Set* Individual;

Generation evolve(Generation old_gen);
Generation random_generation(Set s);

void crossover(Generation);
void mutation(Generation);
int rate_set(Set s, long long goal);
int rate_individual(Individual);
int compare(const void* a, const void* b);

void deallocate(Generation gen);

#endif

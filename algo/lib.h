#ifndef MY_AWSOME_LIB_H
    #define MY_AWSOME_LIB_H
        
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <fstream>
    #include <cmath>
    #include <new>
    #include <iostream>

    #include "set.h"

 //   #define ITERATIONS 20              //maximal number of iterations = number of initial generations
    #define ITER 0              //maximal number of iterations = number of initial generations
 //   #define MAX_GENERATIONS 200         //depth of generation tree to be derived from initial generation
    #define MAX_GEN 1         //depth of generation tree to be derived from initial generation
 //   #define INDIVIDUALS 500             //number of individuals in each generation
    #define NIND 2             //number of individuals in each generation
 //   #define SUBSETS 6                  //number of subsets to which main set will be partitioned
    #define SUBSETS 3                  //number of subsets to which main set will be partitioned
    #define EPSILON 4                  //number of subsets to which main set will be partitioned
 //   #define SURVIVORS 0.10
    #define SURVIVORS 5
   

   using namespace std;
/* 
  GENERATION
 
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 0 | GENERATION + 0
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 1 | GENERATION + 1
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 2  .. .. . . . .. .
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 3
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 4 
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 5 
  [set0][set1][set2][set3]...[setn] INDIVIDUAL 6
  .
  .
  .
  [set0][set1][set2][set3]...[setn] INDIVIDUAL n
 
 */
extern int IDEAL_SET;
extern int ARGS[];

typedef Set** Generation;
typedef Set* Individual;

Generation evolve(Generation old_gen);
Generation random_generation(Set s);

void print_ind(Individual);
Individual copy_ind(Individual oldind);
Individual crossover(Individual,Individual);
void mutation(Individual);
long int  rate_set(Set s, const long int goal);
long int  rate_individual(Individual);
long int absolute(long int);
bool del(int el);
int  compare(const void* a, const void* b);

int*     load_from_file(const char* filename ,int* counter);
void     parse_args(char** argv, int argc);
bool     save_to_file(const char* filename, Individual ind);


#endif

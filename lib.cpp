#include "lib.h"

int abs(int a){ return a<0 ? -a : a; }

int rate_individual(Individual in){
    int diff_total = 0;
    for(int i=0; i<SUBSETS; i++){
        diff_total += abs( rate_set(in[i],IDEAL_SET) );
    }

return diff_total;
}

int rate_set(Set s, long long goal ){
    return s.sum()-goal;
}

int compare(const void* a, const void* b){

    
    return rate_individual(*(Individual*)a) - rate_individual(*(Individual*)b);
}


/* This function creates population of sets from basic set 
 * - allocate INDIVIDUALS X NUMBER_OF_SUBSETS ARRAY
 * - for each INDIVIDUAL GET RANDOM PARTITION OF MAIN SET TO NUMBER_OF_SUBSETS SUBSETS
 *   each SUBSET of random size and elements from basic subset
 */
Generation random_generation(Set s){

    Generation gen = new Individual[INDIVIDUALS]; //array of partitions
    Set copy       = s;
    int size       = 0;
    
    srand(time(NULL));
    

    for(int i=0; i<INDIVIDUALS; i++,s=copy){ //Random individuals (Set partitions)
    std::cout<<"++++++++++++ NEXT INDIVIDUAL +++++++++++++++++\n";
        gen[i]=new Set[ SUBSETS ];

        for(int sub_n=0; sub_n<SUBSETS; sub_n++){ 
         
            if(sub_n == SUBSETS-1)   //for last set assign all the rest of elements
                size=s.size();
            else
                size = rand() % (s.size() - SUBSETS + sub_n ) + 1;

            for(int counter=0; counter<size; counter++){
                gen[i][sub_n].add( s.pop_rand() );
            }

        std::cout<<"["<<sub_n+1<<"] ";
        (gen[i][sub_n]).to_stream(std::cout);
        std::cout<<"\n";
        }
        
    }
    
    return gen;
}




void deallocate(Generation gen){
    if(gen != NULL)
    for(int g=0; g<INDIVIDUALS; g++){
        delete [] gen[g];
    }
    delete [] gen;
}

Generation evolve(Generation old_gen){
    Generation new_gen = new Individual[ INDIVIDUALS ]; //each generation has equal number of individuals


    qsort(old_gen, INDIVIDUALS ,sizeof(Set*),compare); //sort to get best individuals on the beginnig

    crossover(old_gen);
    
    mutation(old_gen);                //mutations with random chanse bigger if big error
   
   /////////////
    for(int i=0; i<INDIVIDUALS; i++){ //rate old generation
        std::cout<<"R"<<i+1<<": "<<rate_individual(old_gen[i])<<"\n";  //choos best individuals for further generations
        new_gen[i] = old_gen[i];
    }
///////////

    for(int i=0; i<SURVIVORS * INDIVIDUALS; i++){ //rate old generation
        new_gen[i] = old_gen[i];
    }

    deallocate(old_gen);              //clean up
    return new_gen;                   //return new_generation (size equal to old one
}

void crossover(Generation){
  
};

void mutation(Generation){

};

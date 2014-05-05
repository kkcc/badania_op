#include "lib.h"


extern long int best;
extern Set input;  //input subset    

int abs(int a){ return a<0 ? -a : a; }

int rate_individual(const Individual in){
    int diff_total = 0;
    for(int i=0; i<SUBSETS; i++){
        diff_total += pow(rate_set(in[i],IDEAL_SET),2);
    }

return pow(diff_total,2);
}

int rate_set(const Set s,const long long goal ){
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


int* choose_parents(const long int fitnesses[], long int total_fitness, int pairs_needed){
    double map[ INDIVIDUALS ];
    double total = 0;
    int* parents = new int[ pairs_needed*2 ]; // [ Parent1a,Parent1b,Parent2a,Parent2b...] 

    for(int i=0; i< INDIVIDUALS; i++){                    //count probability for each ind to be parent
        map[i] = total;
        total += double(fitnesses[i])/(double)total_fitness;
    }

    for(int i=0; i< INDIVIDUALS ; i++){
        std::cout<<i+1<<" : "<<map[i]<<"\n";
    }
    

    for(int i = 0; i<pairs_needed; i++){                
        double prob_p1 = (double) rand() / RAND_MAX;       //parents for the current mutation
       
        int pind1 = 1, pind2 = 1;
        while( prob_p1 > map[ pind1 ] ) pind1++;
        parents[i] = pind1-1;
        
      //  std::cout<<"P1:"<<parents[i];
        
        do{
            double prob_p2 = (double) rand() / RAND_MAX;
            pind2 = 1;
            while( prob_p2 > map[ pind2 ] ) pind2++;
            parents[i+1] = pind2-1;
        }while(pind1==pind2); //reject Px + Px 

   //     std::cout<<"P2:"<<parents[i+1]<<endl;
    }
return parents;
}

//TODO
Generation evolve(Generation old_gen){
    Generation  new_gen     = new Individual[ INDIVIDUALS ]; //each generation has equal number of individuals
    long int* fitnesses     = new long int[ INDIVIDUALS ];
    long int  total_fitness = 0; 
    int*      parents       = 0;
    int survived = SURVIVORS * INDIVIDUALS;

    qsort(old_gen, INDIVIDUALS ,sizeof(Set*),compare); //sort to get best individuals on the beginnig
    long int highest_error = rate_individual( old_gen[ INDIVIDUALS-1] );
     
    long int err = 0;
    if( rate_individual( old_gen[0]) < best )
       best = rate_individual( old_gen[0]);

    if(best == 0) exit(1);

    /////////////
    
    for(int i=0; i<INDIVIDUALS; i++){ //rate old generation
        fitnesses[i] = highest_error + 1 - rate_individual(old_gen[i]);
        total_fitness += fitnesses[i];
        
 //       std::cout<<"OCENA: "<<rate_individual( old_gen[i] )<<"\n";
 //       std::cout<<"R"<<i+1<<": "<<fitnesses[i]<<"\n";  //choos beste individuals for further generations

    }
    ///////////

    parents = choose_parents(fitnesses,  total_fitness, INDIVIDUALS-survived );
    int i,anc=0;
    for(i=0; i<survived; i++){ //save best individuals
        new_gen[i] = copy_ind( old_gen[i] );
    }

    
    for(; i<INDIVIDUALS; i++){ //produce remaining them with crossover between best parents
        new_gen[i] = crossover( old_gen[ parents[anc] ],old_gen[ parents[anc+1] ]  ) ;
        anc += 2;
    } 

    
    //TODO mutacja zgodnie z zaleznioscia w pdfie
    mutation(  old_gen[0] );                //mutations with random chanse bigger if big error
    //
    //
    
    /* clean up */
    for(int i=0; i<INDIVIDUALS; i++ ) delete [] old_gen[i];
    delete [] old_gen;             //clean up
    delete [] parents;
    delete [] fitnesses;

    return new_gen;                   //return new_generation (size equal to old one
}

Individual copy_ind(Individual oldind){
    Individual newind = new Set[ SUBSETS ];
    for(int i=0; i<SUBSETS; i++)
        newind[i] = oldind[i];
    
    return newind;
}

//Copy sets with least error to new child from both parents
//Values that were not copied deliver according to error
//Values that appear twice delete according to error
//TODO wartosci ktore pojawiaja sie podwojnie ( skopiowane z rodzica 1 i rodzica 2)
//trzeba wykasowac -> usuwamy wartosc zgodnie z błędem zbioru
//TODO wartosci ktore nie zostaly odziedziczone po zadnym z rodzicow, trzeba rozrzucic po podzbiorach dziecka
//zgodnie z bledem -> wieksze wartosci wrzucamy to zbiorow ktore maja za mala sume w stosunku do idealnej
//mniej do tych ktorym brakuje mniej
Individual crossover(Individual par1, Individual par2){
    Individual newind = new Set[SUBSETS];
    Set copy = input;
    int p1diff, p2diff;
 
    for(int i=0; i<SUBSETS; i++){
        
        p1diff = abs( rate_set(par1[i], IDEAL_SET) );
        p2diff = abs( rate_set(par2[i], IDEAL_SET) );

        if(p1diff>p2diff){
            newind[i] = par2[i];
        }else if(p1diff<p2diff) { 
            newind[i] = par1[i];
         }
        else{
            if( rand()%1)
                newind[i] = par2[i];
            else
                newind[i] = par1[i];
        }

   }

    return newind;
};




void mutation(Individual ind){
//one random value from random subset moved to random subset :D

    int n_subset = rand() % SUBSETS;
    
    Set* set    = &ind[n_subset];
    int el      = set->pop_rand();
    n_subset    = rand() % SUBSETS;
    set         = &ind[n_subset];
    set->add(el);

};


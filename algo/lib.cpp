#include "lib.h"
#include <map>
#include <climits>
#define MAX_ELEMENTS 2048

extern Set input;  //input subset    
extern int IC;
extern int GC;

bool save_to_file(const char* filename, Individual ind){
   
   ofstream fs(filename);

   ind[0].to_stream(std::cout);

   if( !fs.is_open() )
        return false;

   for(int i=0; i<ARGS[SUBSETS]; i++ ){
      ind[i].to_stream(fs);
      fs<<"\n";
   }
   fs<<"\n"<<IC+1<<" "<<GC+1;
   fs.close();

   return true;
}

void parse_args(char** argv, int argc){
    for(int i=1; i<argc; i++){
        ARGS[i-1] = atoi( argv[i] );

        std::cout<<"ARG "<<i<<" - "<<ARGS[i]<<"\n";
    }
}

int* load_from_file(const char* filename ,int* counter){
   fstream fs;
   int *tab = new int[MAX_ELEMENTS];
   int x;
   int pos = 0;
   *counter = 0;

   fs.open(filename);

   while(!fs.eof()){
        fs>>x;
        tab[pos++]=x;
        (*counter)++;
    std::cout<<x<<",";
    }

    return tab;
}


long int absolute(long int a){ return a<0 ? -a : a; }

long int rate_individual(const Individual in){
    long long int diff_total = 0;
    for(int i=0; i<ARGS[SUBSETS]; i++){
        diff_total += pow(rate_set(in[i],IDEAL_SET),2);
    }

return pow(diff_total,2);
}

long int rate_set(const Set s,const long int goal ){
    return s.sum()-goal;
}

int compare(const void* a, const void* b){
    return int(rate_individual(*(Individual*)a) > rate_individual(*(Individual*)b));
}


/* This function creates population of sets from basic set 
 * - allocate INDIVIDUALS X NUMBER_OF_SUBSETS ARRAY
 * - for each INDIVIDUAL GET RANDOM PARTITION OF MAIN SET TO NUMBER_OF_SUBSETS SUBSETS
 *   each SUBSET of random size and elements from basic subset
 */
Generation random_generation(Set s){

    Generation gen = new Individual[ ARGS[NIND] ]; //array of partitions
    Set copy       = s;
    int size       = 0;
    
    srand(time(NULL)+GC*IC);
    
    for(int i=0; i<ARGS[NIND]; i++,s=copy){ //Random individuals (Set partitions)
        gen[i]=new Set[ ARGS[SUBSETS] ];

        for(int sub_n=0; sub_n<ARGS[SUBSETS]; sub_n++){ 
         
            if(sub_n == ARGS[SUBSETS]-1)   //for last set assign all the rest of elements
                size=s.size();
            else
                size = rand() % (s.size() - ARGS[SUBSETS] + sub_n ) + 1;

            for(int counter=0; counter<size; counter++){
                gen[i][sub_n].add( s.pop_rand() );
            }
        }
    }
    
    return gen;
}


int* choose_parents(const long int fitnesses[], long int total_fitness, int pairs_needed){
    double map[ ARGS[NIND] ];
    double total = 0;
    int* parents = new int[ pairs_needed*2 ]; // [ Parent1a,Parent1b,Parent2a,Parent2b...] 

    for(int i=0; i< ARGS[NIND]; i++){                    //count probability for each ind to be parent
        total += double(fitnesses[i])/(double)total_fitness;
        map[i] = total;
    }


    for(int i = 0; i<pairs_needed*2; i+=2){                
        double prob_p1 = (double) rand() / RAND_MAX;       //parents for the current mutation
       
        int pind1 = 1, pind2 = 1;
        while( prob_p1 > map[ pind1 ] ) pind1++;
        parents[i] = pind1-1;
        
        do {
            double prob_p2 = (double) rand() / RAND_MAX;
            pind2 = 1;
            while( prob_p2 > map[ pind2 ] ) pind2++;
            parents[i+1] = pind2-1;
        } while ( pind1 == pind2 ); //reject Px + Px 

    }

return parents;
}

Generation evolve(Generation old_gen){
    Generation  new_gen     = new Individual[ ARGS[NIND] ]; //each generation has equal number of individuals
    long int* fitnesses     = new long int[ ARGS[NIND] ];
    long int  total_fitness = 0; 
    int*      parents       = NULL;
    int survived = (ARGS[SURVIVORS] * ARGS[NIND])/100;

    qsort(old_gen, ARGS[NIND] ,sizeof(Set*),compare); //sort to get best individuals on the beginnig
    long int highest_error = rate_individual( old_gen[ ARGS[NIND]-1] );
    long int lowest_error  = rate_individual( old_gen[0]); 

    std::cout<<"ERROR: "<<lowest_error<<"\n";
    if(lowest_error <= ARGS[EPSILON] ) {
        save_to_file("output.txt",old_gen[0]);
        return NULL;
    }

    for(int i=0; i<ARGS[NIND]; i++){ //rate old generation
    long int tmp;
        fitnesses[i]  = highest_error + 1 - (tmp=rate_individual(old_gen[i]));
        total_fitness += fitnesses[i];

    }

    parents = choose_parents(fitnesses,  total_fitness, ARGS[NIND]-survived+2 );
    int i,anc=0;
    for(i=0; i<survived; i++){ //save best individuals
        new_gen[i] = copy_ind( old_gen[i] );
    }

    /* CROSSOVER */ 
    for(; i<ARGS[NIND]; i++){ //produce remaining them with crossover between best parents
        new_gen[i] = crossover( old_gen[ parents[anc] ],old_gen[ parents[anc+1] ]  ) ;
        anc += 2;
    } 
    
    /* MUTATION */
    int nmut;
    qsort(old_gen, ARGS[NIND] ,sizeof(Set*),compare); //sort to get best individuals on the beginnig
    
    for(i=0; i<ARGS[NIND]; i++){
     
        if(i<survived) {//10% best individuals
            for(nmut=1; nmut>0; nmut--)  if(!(rand() % 10) ) mutation(new_gen[i]);
        }else if( i<int(ARGS[NIND]*0.50) ){ //10-50 best individuals
            for(nmut=4; nmut>0; nmut--)  if( rand() % 2   )  mutation(new_gen[i]);
        }else if( i<int(ARGS[NIND]*0.70) ){//50-70 best individuals
            for(nmut=10; nmut>0; nmut--) if( rand() % 2   )  mutation(new_gen[i]);
        }else  //70-100 best individuals
            for(nmut=20; nmut>0; nmut--) if( rand() % 2  )   mutation(new_gen[i]);
    }

    /* clean up */
    for(int i=0; i<ARGS[NIND]; i++ ) delete [] old_gen[i];
    delete [] old_gen;             //clean up
    delete [] parents; parents = NULL;
    delete [] fitnesses;

    return new_gen;                   //return new_generation (size equal to old one
}

Individual copy_ind(Individual oldind){
    Individual newind = new Set[ ARGS[SUBSETS] ];
    for(int i=0; i<ARGS[SUBSETS]; i++)
        newind[i] = oldind[i];
    
    return newind;
}

//Copy sets with least error to new child from both parents
//Values that were not copied deliver according to error
//Values that appear twice delete according to error
//mniej do tych ktorym brakuje mniej
Individual crossover(Individual par1, Individual par2){
    Individual newind = new Set[ARGS[SUBSETS]];
    Set tmp,copy = input;
    int p1diff, p2diff;
    map<int,int> where_is;

    for(int i=0,p1=0,p2=0; i< ARGS[SUBSETS]; i++){
        
        p1diff = absolute( rate_set(par1[p1], IDEAL_SET) );
        p2diff = absolute( rate_set(par2[p2], IDEAL_SET) );

        if(p1diff>p2diff) { //TODO refactoring
            newind[i] = p2<ARGS[SUBSETS] ? par2[p2++] : par1[p1++];
        } else if(p1diff<p2diff) { 
            newind[i] = p1<ARGS[SUBSETS] ? par1[p1++] : par2[p2++];
        } else {
            if( p1!=ARGS[SUBSETS] && p2!=ARGS[SUBSETS] ) {
                if( rand()%2 )
                    newind[i] = par2[p2++];
                else
                    newind[i] = par1[p1++];
            }else
                newind[i] = p1<ARGS[SUBSETS] ? par1[p1++] : par2[p2++];
        }

        tmp = newind[i];  //to avoid the iterators mess used by get_next
        for(int el=0; el<newind[i].size(); el++ ){
            int val = tmp.get_next();

            copy.del( val );
            if( where_is.find( val ) == where_is.end() ){ //wasn't previously assigned
                where_is[val] = i;
            }
            else{
                //attempt to copy the same value twice, one will be deleted to cause less error
                p1diff = absolute(IDEAL_SET - newind[where_is[val]].sum() + val ) ;
                p2diff = absolute(IDEAL_SET - newind[i].sum() + val ) ;

                if(p1diff < p2diff)
                    newind[where_is[val]].del(val);
                else if(p1diff > p2diff ) {
                    newind[i].del(val);
                }
                else{
                    if( rand()%2 )
                        newind[where_is[val]].del(val);
                    else
                        newind[i].del(val);

                }

            }
        }
    }
    //distribute remaining values between sets 
    tmp = copy;  
    for(int i=copy.size(); i>0; i--){
        int  min_ind = -1;
        long min_err = LONG_MAX;
        int  err     = 0;

        int val = tmp.get_next();
        for(int s=0; s<ARGS[SUBSETS]; s++){
            if(min_err > ( err = absolute( IDEAL_SET - newind[s].sum() - val ) ) ) {
                min_err = err;
                min_ind = s;
            }
        }

        newind[ min_ind ].add(val);
        copy.del(val);
    }

    return newind;
};


void print_ind(Individual ind){

    for(int i=0; i<ARGS[SUBSETS]; i++){
        ind[i].to_stream(std::cout);
        std::cout<<"\n";
    }
}

void mutation(Individual ind){
    //one random value from random subset moved to random subset :D
    int el=0,n_subset;
    Set *set;
    while(el==0){
        n_subset = rand() % ARGS[SUBSETS];
        set      = &ind[n_subset];
        el       = set->pop_rand();
    }; 
    n_subset = rand() % ARGS[SUBSETS];
    set      = &ind[n_subset];
    set->add(el);

};


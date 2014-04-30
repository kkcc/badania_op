

#include "set.h"
#include "lib.h"

int IDEAL_SET;

int* load_from_file(const char* filename ){
   fstream fs;
   int *tab = new int[ELEMENTS_TOTAL];
   int x;
   int pos = 0;
   fs.open(filename);
  

   while(!fs.eof()){
        fs>>x;
        tab[pos++]=x;
    std::cout<<x<<",";
    }

    return tab;
}

bool save_to_file(const char* filename, Individual ind){
   
   ofstream fs(filename);

   ind[0].to_stream(std::cout);

   if( fs.is_open() ){
        //for(Set* s=ind; s<&ind[SUBSETS-1]; s++ ){
        for(int i=0; i<SUBSETS; i++ ){
            printf("*****\n");
            ind[i].to_stream(fs);
            fs<<"\n";
        }
    
   fs.close();
   }
   else return false;

   return true;
}


int* spawn_random_elements(){
    
    int* tab = new int[ELEMENTS_TOTAL];
    
    for(int i=0; i<ELEMENTS_TOTAL; i++){
        tab[i] = rand()%200 + 1 ;
    }
    return tab;
}



int main(int argc, char* argv[]){

/* wczytywanie z pliku */


//int el[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
Generation generation;
//int* el = spawn_random_elements();
    int *el = load_from_file("set.txt");
long long total_sum = 0;

/* tworzenie zbioru */
Set s1(el,ELEMENTS_TOTAL);
free(el);

total_sum = s1.sum();
IDEAL_SET = total_sum / SUBSETS;


std::cout<<"Total sum    : "<<total_sum<<"\n";
std::cout<<"Ideal subset : "<<total_sum/SUBSETS<<"\n";


/* MAIN LOOP */
for(int i=0; i<ITERATIONS ; i++){
std::cout<<"//////////////////// GENERATION "<<i+1<<"."<<"0"<<" \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";

    generation = random_generation(s1);            //*Generate initial generation
        //* 
        for(int g_depth=0; g_depth<MAX_GENERATIONS; g_depth++){
            std::cout<<"//////////////////// GENERATION "<<i+1<<"."<<g_depth+1<<" \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
            generation = evolve(generation);
            
            bool x = save_to_file("out.txt",generation[0]);
            //int i = x == true ? EXIT_SUCCESS : EXIT_FAILURE;
      exit(i) ;
        }

}
/*zapis do pliku */
save_to_file("out.txt",generation[0]);
s1.to_stream(std::cout);


}

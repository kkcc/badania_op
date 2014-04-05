

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


for(int i=0; i<s1.size(); i++){
    total_sum += s1[i];
}
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
      exit(1) ;
        }

}
/*zapis do pliku */
s1.to_stream(std::cout);


}

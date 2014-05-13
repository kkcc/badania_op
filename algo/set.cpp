#include "set.h"
#include <cstdlib>

int Set::pop_rand(){
    int set_size  = size();
    
    if(set_size == 0 ) return 0; //to handle the exception of rand()%0
    
    int index  = rand() % set_size;
    int tmp;
    int i=0;
    std::set<int>::iterator it;
    for( it=elements.begin(); i!=index; i++, it++ );

    tmp = *it;
    elements.erase(it);
    return tmp;
    
}

long int Set::sum() const {
    long int tmp  = 0;
    for(std::set<int>::iterator i=elements.begin(); i!=elements.end(); i++)
        tmp += *i;
    

    return tmp;
}

Set::Set(int * nums, int size){
    for(int i=0; i<size; i++)
        elements.insert(nums[i]);
}

ostream& Set::to_stream(ostream& os, string sep){

    for(set<int>::iterator it = elements.begin(); it!= elements.end() ; it++ ){
        os<<*it<<sep;
    }

    return os;
}

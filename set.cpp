#include "set.h"
#include <cstdlib>

int Set::pop_rand(){
    int index  = rand() % size();
    int tmp    = elements.at(index);
    elements.at(index) = *(elements.end()-1);
    elements.erase(elements.end()-1);
    return tmp;
}

long int Set::sum(){
    long int tmp  = 0;
    for(int i=0; i<this->size(); i++){
        tmp += (*this)[i];
    }

    return tmp;
}

Set::Set(int * nums, int size){
    for(int i=0; i<size; i++)
        elements.push_back(nums[i]);
}

ostream& Set::to_stream(ostream& os, string sep){

    for(vector<int>::iterator it = elements.begin(); it!= elements.end() ; it++ ){
        os<<*it<<sep;
    }

    return os;
}

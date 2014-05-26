#ifndef SET_H
    #define SET_H
    #include <vector>
    #include <iostream>
    #include <string>
    #include <set>

using namespace std;

class Set  {
private:

set<int> elements;
set<int>::iterator it;

public:

Set()  { elements = set<int>(); it=elements.begin(); }
Set(int* numbers, int size);
~Set() { this->clear(); }
Set(Set& cpy) { this->elements = cpy.elements; this->it=this->elements.begin(); }

Set& operator=(Set pat){
    this->elements = pat.elements;
    this->it       = this->elements.begin();
return *(this);
}

int      get_next() {  
    int val = *it; it++;
    if(it==elements.end()) 
        it=elements.begin();
    return val; 
    
}

long int sum() const;
int      pop_rand();
bool     del(int el){ return (bool)elements.erase(el); }
void     add(int el) { elements.insert(el); }
int      clear(void) { elements.clear(); }
ostream& to_stream(ostream& os, string sep=" ");
int      size() { return elements.size(); }

};


#endif

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

public:

Set()  { elements = set<int>(); }
Set(int* numbers, int size);
~Set() { this->clear(); }

long int sum() const;
int      pop_rand();
bool     del(int el){ return (bool)elements.erase(el); }
void     add(int el) { elements.insert(el); }
int      clear(void) { elements.clear(); }
ostream& to_stream(ostream& os, string sep=" ");
int      size() { return elements.size(); }

};


#endif

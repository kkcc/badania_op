#ifndef SET_H
    #define SET_H
    #include <vector>
    #include <iostream>
    #include <string>
using namespace std;

class Set {
private:


vector<int> elements;



public:

Set()  {}
Set(int* numbers, int size);
~Set() { this->clear(); }

long int sum();
int pop_rand();
void add(int el){ elements.push_back(el); }
int clear(void) { elements.clear(); }
int& operator[](int ind){ return elements.at(ind); }
ostream& to_stream(ostream& os, string sep=" ");
int size() { return elements.size(); }

};


#endif

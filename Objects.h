//
// Created by nr1sl on 12/1/2022.
//
#include <iostream>
#include <vector>
#ifndef NCP_OBJECTS_H
#define NCP_OBJECTS_H
using namespace::std;

class Objects {
private:
    bool terminal;
    string Naam;
    vector<vector<Objects*>> products;
public:
    Objects();
    Objects(bool t,string N);

    void SetProducts(vector<Objects*> O);
    const vector<vector<Objects*>> &getProducts() const;
    string getnaam();
    bool getterminal();

    bool HelperSearch(string str);
    bool FunctionHelper(string str);
    bool VarHelper(string str);
    bool Alhphabet(string str);
    bool Nummer(string str);


};


#endif //NCP_OBJECTS_H

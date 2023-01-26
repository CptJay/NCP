//
// Created by nr1sl on 1/26/2023.
//

#ifndef NCP_CALCULATOR_H
#define NCP_CALCULATOR_H
#include <map>
#include <iostream>
#include <string>
#include "UniversalTuringMachine.h"
#include "Track.h"
#include "Computing.h"
#include "EarleyParser.h"

using namespace::std;

class Calculator {

    UniversalTuringMachine t;
    Computing tm;
    map<string,int> Map;
public:
    Calculator(map<vector<string>,vector<string>>);
    void Haakjes(int i, vector<string>Vector);
    void Oefeningen(map<vector<string>,vector<string>>);
    void Een_Oef(string,vector<string>);
    void Bereken();

};


#endif //NCP_CALCULATOR_H

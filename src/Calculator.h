//
// Created by nr1sl on 1/26/2023.
//

#ifndef NCP_CALCULATOR_H
#define NCP_CALCULATOR_H
#include <map>
#include <iostream>
#include <string>
#include <stack>
#include "UniversalTuringMachine.h"
#include "Track.h"
#include "Computing.h"
#include "EarleyParser.h"

using namespace::std;

class Calculator {

    UniversalTuringMachine t;
    Computing tm;
    map<string,pair<vector<string>,string>> Map_Vriable; // variabel naam, <vector van wat er in zit, type element>


public:
    bool sign_check(vector<string>v);
    Calculator(vector<pair<vector<string>,vector<string>>>);
    pair<int,string> Haakjes(int i, vector<string>Vector,string type);
    void Oefeningen(vector<pair<vector<string>,vector<string>>>);
    vector<string> Double_Oefening(string type, vector<string>V);
    void Bereken();
    vector<string> evaluateMatrixExpression(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2,char op);
    int evaluate(vector<string> expression);
    int evaluateExpression(int val1, int val2, char op);
    vector<vector<double>> helper_vecString_to_Matrix(vector<string> temp);
    vector<string> helper_Matrix_to_vecString(vector<std::vector<double>> temp);
    vector<string> helper_poly_to_vecString(vector<double> temp);
    vector<double> helper_vecString_to_poly(vector<string> temp);

    vector<string> helper_vecString_to_Vector(vector<double> temp);
    vector<double> helper_Vector_to_String(vector<string> temp);
    vector<string> EvaluateVectorExpression(const std::vector<double> vec1, const std::vector<double> vec2,char op);


};


#endif //NCP_CALCULATOR_H

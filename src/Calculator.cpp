//
// Created by nr1sl on 1/26/2023.
//

#include "Calculator.h"



void Calculator::Bereken() {

}



void Calculator::Haakjes(int index, vector<string>Vector){
    vector<string> temp = {};
    for(int i = 0; i< index;i++){
        temp.emplace_back(Vector[i]);
    }
    vector<string> tem = {};
    for(int i = index+1; i < Vector.size();i++){
        if(Vector[i] == ")"){

        }
        tem.emplace_back(Vector[i]);
    }
}

string Calculator::Een_Oef(string type, vector<string>V) {
    int n = 1;

    while(V.size() != n){
        bool Einde_bereikt = false;
        int index = 0;
        while(!Einde_bereikt){
            if(V[index] =="*" or V[index] == "/"){
                string Before = V[index-1];
                string After = V[index+1];
                int x;
                int y;
                if(Map.contains(Before)){
                    x = Map[Before];
                }
                else if(Before != ")" or Before != "]"){
                    x = stoi(Before);
                }
                if(Map.contains(After)){
                    y = Map[After];
                }
                else if(Before != "(" or Before != "["){
                    y = stoi(Before);
                }
            }
        }
        Einde_bereikt = false;
        while(!Einde_bereikt){

        }
    }
}

void Calculator::Oefeningen(map<vector<string>, vector<string>>Map) {
    for(const auto &i:Map){
        Een_Oef(i.first[0],i.second);
    }
}

Calculator::Calculator(map<vector<string>, vector<string>> m) {
    for(auto i: m){
        if(i.second.size() == 1){
            map[i.first[1]] = stoi(i.second[0]);
        }
    }
}


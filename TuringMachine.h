//
// Created by youssef on 27/11/22.
//

#ifndef NCP_TURINGMACHINE_H
#define NCP_TURINGMACHINE_H

#include "json.hpp"
#include <vector>
#include <string>
class Transition;
using namespace std;
using json = nlohmann::json;

class TuringMachine {
private:
    int head, track;
    string Start;
    vector<pair<vector<string>,vector<string>>> tracks;
    vector<string>* currentTrack;
    vector<string> states, finalStates, variables;
    vector<Transition> transitions;

public:
    TuringMachine(string);

    bool accepts(vector<string>);

    ~TuringMachine();
};


#endif //NCP_TURINGMACHINE_H

//
// Created by youssef on 27/11/22.
//

#include "TuringMachine.h"
#include "Transition.h"
#include <fstream>
#include <iostream>


TuringMachine::TuringMachine(string fileName) : head(0), track(0),
                                                    tracks({pair<vector<string>,vector<string>> ({},{})}),
                                                    currentTrack(&tracks[0].first)  {
    ifstream input(fileName);
    json j;
    input >> j;
    for (const auto& state:j["States"]) {
        states.push_back(state);
    }
    for (const auto& variable:j["Variables"]) {
        variables.push_back(variable);
    }
    for (const auto& finalState:j["Final"]) {
        finalStates.push_back(finalState);
    }
    for (const auto& transition:j["Transitions"]) {
        string direction = transition["direction"];
        Transition t(transition["from"],transition["to"],transition["symbol"],direction[0]);
        transitions.push_back(t);
    }
    Start = j["Start"];
}

bool TuringMachine::accepts(vector<string>) {
    return false;
}

TuringMachine::~TuringMachine() {

}

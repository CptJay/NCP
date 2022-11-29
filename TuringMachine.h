//
// Created by youssef on 27/11/22.
//

#ifndef NCP_TURINGMACHINE_H
#define NCP_TURINGMACHINE_H

#include "json.hpp"
#include <vector>
#include <memory>
#include <string>
struct State;
struct Transition;
using namespace std;
using Track = pair<vector<string>,vector<string>>;
using json = nlohmann::json;

class TuringMachine {
private:
//    trackCorrection bestaat zodat de head value stijgt terwijl hij naar
//    links gaat als hij op de -inf track staat
    int head, track, trackCorrection;
    string start;
    vector<Track> tracks;
    vector<string>* currentTrack;
    vector<string> finalStates, variables;
    vector<shared_ptr<State>> states;

public:
    TuringMachine(string);

    bool accepts(vector<string>);

    ~TuringMachine();
};


#endif //NCP_TURINGMACHINE_H

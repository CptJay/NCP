//
// Created by youssef on 27/11/22.
//

#ifndef NCP_UNIVERSALTURINGMACHINE_H
#define NCP_UNIVERSALTURINGMACHINE_H

#include "json.hpp"
#include <vector>
#include <memory>
#include <string>
struct State;
struct Transition;
using namespace std;
using Track = pair<vector<string>,vector<string>>;
using json = nlohmann::json;

class UniversalTuringMachine {
private:
//    trackCorrection bestaat zodat de head value stijgt terwijl hij naar
//    links gaat als hij op de -inf track staat
    int head{}, track{}, trackCorrection{};
    vector<Track> tracks;
    vector<string> instructions, currentState;
    vector<string>* currentTrack{};

public:
    UniversalTuringMachine(vector<string>&);

    UniversalTuringMachine(const string&);

    vector<string> jsonToInstruction(const string&);

    tuple<string, char, bool, bool> readInstruction(const string&);

    bool start(vector<string>);

    ~UniversalTuringMachine();
};


#endif //NCP_UNIVERSALTURINGMACHINE_H

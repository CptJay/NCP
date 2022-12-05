//
// Created by youssef on 27/11/22.
//

#ifndef NCP_UNIVERSALTURINGMACHINE_H
#define NCP_UNIVERSALTURINGMACHINE_H

#include "json.hpp"
#include <vector>
#include <memory>
#include <string>
class Track;
struct State;
struct Transition;
using namespace std;
using json = nlohmann::json;

class UniversalTuringMachine {
private:
//    trackCorrection bestaat zodat de head value stijgt terwijl hij naar
//    links gaat als hij op de -inf track staat
    int track;
    vector<Track> tracks;
    vector<string> instructions, currentState;
    Track* currentTrack;

public:
    UniversalTuringMachine();

    void jsonToInstruction(const string&);

    tuple<string, char, bool, bool> readInstruction(const string&);

    pair<vector<string>, bool> start(const vector<string>&, const string&);

    vector<string> calculate(const vector<string>& input, const string&);

    bool accepts(const vector<string>& input, const string&);

    void reset();

    ~UniversalTuringMachine();
};


#endif //NCP_UNIVERSALTURINGMACHINE_H

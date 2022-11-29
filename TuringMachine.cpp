//
// Created by youssef on 27/11/22.
//

#include "TuringMachine.h"
//#include "Transition.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <memory>
struct Transition;

struct State {
    string name;
    vector<Transition> transitions;
};

struct Transition {
    string symbol, write;
    shared_ptr<State> to;
    char direction;
    Transition(shared_ptr<State> to, string symbol, string write,char direction) : to(to), symbol(std::move(symbol)),
                                                                        write(write),direction(direction) {}
};

TuringMachine::TuringMachine(string fileName) : head(0), track(0), trackCorrection(1),
                                                    tracks({pair<vector<string>,vector<string>> ({},{})}),
                                                    currentTrack(&tracks[0].first)  {
    ifstream input(fileName);
    json j;
    input >> j;
    vector<string> transitionsCopy{};
    for (const auto& state:j["States"]) {
        shared_ptr<State> s (new State);
        s->name = state;
        states.push_back(s);
    }
    for (const auto& variable:j["Variables"]) {
        variables.push_back(variable);
    }
    for (const auto& finalState:j["Final"]) {
        finalStates.push_back(finalState);
    }
    for (const auto& transition:j["Transitions"]) {
        string direction = transition["direction"];
        shared_ptr<State> to {};
        for (auto& state:states) {
            if (state->name == transition["to"]) {
                to = state;
                break;
            }
        }
        Transition t(to,transition["symbol"],transition["write"],direction[0]);
        for (auto& state:states) {
            if (state->name == transition["from"]) {
                state->transitions.push_back(t);
                break;
            }
        }
    }
    start = j["Start"];
}

bool TuringMachine::accepts(vector<string> input) {
    shared_ptr<State> currentState {};
    for (auto state:states) {
        if (state->name == start) {
            currentState = state;
            break;
        }
    }
    *currentTrack = std::move(input);
    bool move = true;
    while (move) {
        move = false;
        if ((*currentTrack).size() <= head) {
            (*currentTrack).emplace_back("#");
        }
        for (auto transition:currentState->transitions) {
            if (transition.symbol == (*currentTrack)[head]) {
                (*currentTrack)[head] = transition.write;
                currentState = transition.to;
                if (transition.direction == 'L') {
                    head -= trackCorrection;
                    if (head < 0) {
                        trackCorrection *= -1;
                        if (trackCorrection == 1)
                            currentTrack = &tracks[track].first;
                        if (trackCorrection == -1)
                            currentTrack = &tracks[track].second;
                    }
                    move = true;
                }
                else if (transition.direction == 'R') {
                    head += trackCorrection;
                    if (head < 0) {
                        trackCorrection *= -1;
                        if (trackCorrection == 1)
                            currentTrack = &tracks[track].first;
                        if (trackCorrection == -1)
                            currentTrack = &tracks[track].second;
                    }
                    move = true;
                }
//                Gaat wel naar het begin van de nieuwe/bestaande track
                else if (transition.direction == 'U') {
                    if (track - 1 < 0) {
                        return false;
                    }
                    track--;
                    head = 0;
                    currentTrack = &tracks[track].first;
                    move = true;
                }
                else if (transition.direction == 'D') {
                    track++;
                    head = 0;
                    if (track == tracks.size()) {
                        tracks.push_back(Track ({},{}));
                    }
                    currentTrack = &tracks[track].first;
                    move = true;
                }
            }
            if (move) {
                break;
            }
        }
    }
    for (auto final:finalStates) {
        if (currentState->name == final) {
            return true;
        }
    }
    return false;
}

TuringMachine::~TuringMachine() {

}

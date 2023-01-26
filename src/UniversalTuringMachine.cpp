//
// Created by youssef on 27/11/22.
//

#include <fstream>
#include <iostream>
#include "Track.h"
#include "UniversalTuringMachine.h"


UniversalTuringMachine::UniversalTuringMachine() : currentState({}), instructions({}), track(0) {
    Track t;
    tracks = {t};
    currentTrack = &tracks[0];
}

void UniversalTuringMachine::jsonToInstruction(const string& fileName) {
    instructions.clear();
    instructions.emplace_back("start");
    vector<tuple<string,string,bool>> states {};
    vector<string> finalStates {};
    int stateNameCounter {1};
    ifstream input(fileName);
    json j;
    input >> j;
    for (const auto& finalState:j["Final"]) {
        finalStates.push_back(finalState);
    }
    for (const auto& state:j["States"]) {
        bool final = false;
        string stateName {};
        for (int i = 0; i < stateNameCounter; ++i) {
            stateName += "A";
        }
        stateNameCounter++;
        if (find(finalStates.begin(),finalStates.end(),state) != finalStates.end()) {
            final = true;
        }
        states.emplace_back(state,stateName,final);
    }
    for (const auto& transition:j["Transitions"]) {
        instructions.emplace_back("@");
        string from {};
        string to {};
        bool toFinal = false;
        bool fromStart = false;
        for (auto state:states) {
            if (get<0>(state) == transition["from"]) {
                from = get<1>(state);

                if (get<0>(state) == j["Start"]) {
                    fromStart = true;
                }
            }
            if (get<0>(state) == transition["to"]) {
                to = get<1>(state);
                toFinal = get<2>(state);
            }
        }
        instructions.emplace_back("from");
        for (auto symbol:from) {
            instructions.emplace_back(1,symbol);
            if (currentState.empty()) {
                currentState.emplace_back(1,symbol);
            }
        }
//        if x -> currentState
        if (fromStart) {
            instructions.emplace_back("x");
        }
        else {
            instructions.emplace_back(".");
        }
        instructions.emplace_back("read");
        vector<string> instructionPart {transition["symbol"],"write",transition["write"],"direction",transition["direction"],"to"};
        for (const auto& i:instructionPart) {
            instructions.emplace_back(i);
        }
        for (auto symbol:to) {
            instructions.emplace_back(1,symbol);
        }
//        if f -> final state
        if (toFinal)
            instructions.emplace_back("f");
        else
            instructions.emplace_back("nf");
        instructions.emplace_back(";");
    }
    instructions.emplace_back("end");
}

pair<vector<string>, bool> UniversalTuringMachine::start(const vector<string>& input, const string& TM) {
    jsonToInstruction(TM);
    int trackLocation {};
    for (const auto& symbol:input) {
        currentTrack->write(symbol);
        currentTrack->moveRight();
        trackLocation++;
    }
    for (int i = 0; i < trackLocation; ++i) {
        currentTrack->moveLeft();
    }
    bool final = false;
    tuple<string, char, bool, bool> nextMove {};
    while (true) {
        nextMove = readInstruction(currentTrack->read());
        if (!get<2>(nextMove)) {
            break;
        }
        string write = get<0>(nextMove);
        char direction = get<1>(nextMove);
        final = get<3>(nextMove);
        currentTrack->write(write);
        if (direction == 'L') {
            currentTrack->moveLeft();
        }
        else if (direction == 'R') {
            currentTrack->moveRight();
        }
//                Gaat wel naar het begin van de nieuwe/bestaande track
        else if (direction == 'U') {
            if (track - 1 < 0) {
                reset();
                return {{},false};
            }
            track--;
            currentTrack = &tracks[track];
        }
        else if (direction == 'D') {
            track++;
            if (track == tracks.size()) {
//                tracks.emplace_back(Track ());
                tracks.emplace_back();
            }
            currentTrack = &tracks[track];
        }
    }
    vector<string> result {};
    currentTrack = &tracks[0];
    while (currentTrack->read() != "#") {
        result.emplace_back(currentTrack->read());
        currentTrack->moveRight();
    }
    reset();
    return {result, final};
}

vector<string> UniversalTuringMachine::calculate(const vector<string> &input, const string& TMfile) {
    vector<string> result = start(input, TMfile).first;
    reset();
    return result;
}

bool UniversalTuringMachine::accepts(const vector<string> &input, const string& TMfile) {
    bool final = start(input, TMfile).second;
    reset();
    return final;
}

tuple<string, char, bool, bool> UniversalTuringMachine::readInstruction(const string& symbol) {
    string write;
    char instructionDirection {};
    bool transitionExists = false;
    bool toFinalState = false;
//    get info
    for (int instructionCount = 0; instructionCount < instructions.size(); ++instructionCount) {
        if (instructions[instructionCount] == "x") {
            int instructionCountCopy = instructionCount;
            while (instructions[instructionCountCopy] != "read") {
                instructionCountCopy++;
            }
            instructionCountCopy++;
            if (symbol != instructions[instructionCountCopy]) {
                continue;
            }
            transitionExists = true;
            while (instructions[instructionCountCopy] != "write") {
                instructionCountCopy++;
            }
            instructionCountCopy++;
            write = instructions[instructionCountCopy];
            while (instructions[instructionCountCopy] != "direction") {
                instructionCountCopy++;
            }
            instructionCountCopy++;
            instructionDirection = instructions[instructionCountCopy][0];
            while (instructions[instructionCountCopy] != "to") {
                instructionCountCopy++;
            }
            instructionCountCopy++;
            currentState.clear();
            while (instructions[instructionCountCopy] == "A") {
                currentState.emplace_back(instructions[instructionCountCopy]);
                instructionCountCopy++;
            }
            if (instructions[instructionCountCopy] == "f") {
                toFinalState = true;
            }
            break;
        }
    }
    if (!transitionExists) {
        return {",", 'e', false, false};
    }
//    remove previous x's on the tape
    for (auto & instruction : instructions) {
        if (instruction == "x") {
            instruction = ".";
        }
    }
//    find transitions with next state
    for (int instructionCount = 0; instructionCount < instructions.size(); ++instructionCount) {
        if (instructions[instructionCount] == "from") {
            int instructionCountCopy = instructionCount+1;
            int instructionStateSize {};
            bool correctState = false;
            while (instructions[instructionCountCopy] != ".") {
                instructionCountCopy++;
                instructionStateSize++;
            }
            if (instructionStateSize == currentState.size()) {
                correctState = true;
            }
            if (correctState) {
                instructions[instructionCountCopy] = "x";
            }
        }
    }
    return {write, instructionDirection, true, toFinalState};
}

void UniversalTuringMachine::reset() {
    currentState.clear();
    track = 0;
    tracks = {Track ()};
    instructions.clear();
    currentTrack = &tracks[0];
}

int UniversalTuringMachine::multiply(int x, int y) {
    vector<string> input {};
    for (int i = 0; i < abs(x); ++i) {
        input.emplace_back("1");
    }
    input.emplace_back("C");
    for (int i = 0; i < abs(y); ++i) {
        input.emplace_back("1");
    }
    vector<string> result = start(input, "../basic_ops/MultiplicationTM.json").first;
    reset();
    return result.size();
}

int UniversalTuringMachine::divide(int x, int y) {
    vector<string> result {};
    for (int i = 0; i < abs(y); ++i) {
        result.emplace_back("1");
    }
    result.emplace_back("0");
    for (int i = 0; i < abs(x); ++i) {
        result.emplace_back("1");
    }
    result.emplace_back("0");
    result = start(result, "../basic_ops/DivisionTM.json").first;
    reset();
    return result.size();
}

//    Input:  0 0 0 c 0 0 0 0  // (3 - 4) or (4 - 3)
//    Output:  0              // (1)

int UniversalTuringMachine::add(int x, int y) {
    vector<string> input {};
    for (int i = 0; i < abs(x); ++i) {
        input.emplace_back("1");
    }
    input.emplace_back("C");
    for (int i = 0; i < abs(y); ++i) {
        input.emplace_back("1");
    }
    vector<string> result = start(input, "../basic_ops/AdditionTM.json").first;
    reset();
    return result.size();
}

int UniversalTuringMachine::subtract(int x, int y) {

    // Biggest number should be the first

    vector<string> input {};
    for (int i = 0; i < abs(y); ++i) {
        input.emplace_back("1");
    }
    input.emplace_back("C");
    for (int i = 0; i < abs(x); ++i) {
        input.emplace_back("1");
    }
    vector<string> result = start(input, "../basic_ops/SubtractionTM.json").first;
    reset();
    return result.size();
}

UniversalTuringMachine::~UniversalTuringMachine() = default;
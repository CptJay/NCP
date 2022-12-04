//
// Created by youssef on 27/11/22.
//

#include <fstream>
#include "UniversalTuringMachine.h"


UniversalTuringMachine::UniversalTuringMachine(vector<string>& instructionsInput) : head(0), track(0), trackCorrection(1),
                                                   tracks({pair<vector<string>,vector<string>> ({},{})}),
                                                   currentTrack(&tracks[0].first), currentState({}),
                                                   instructions(instructionsInput) {}

UniversalTuringMachine::UniversalTuringMachine(const string& fileName) : head(0), track(0), trackCorrection(1),
                                                   tracks({pair<vector<string>,vector<string>> ({},{})}),
                                                   currentTrack(&tracks[0].first), currentState({}) {jsonToInstruction(fileName);}

UniversalTuringMachine::~UniversalTuringMachine() = default;


vector<string> UniversalTuringMachine::jsonToInstruction(const string& fileName) {
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
    return instructions;
}



bool UniversalTuringMachine::start(vector<string> input) {
    *currentTrack = std::move(input);
    bool final = false;
    tuple<string, char, bool, bool> nextMove {};
    do {
        if ((*currentTrack).size() <= head) {
            (*currentTrack).emplace_back("#");
        }
        nextMove = readInstruction((*currentTrack)[head]);
        string write = get<0>(nextMove);
        char direction = get<1>(nextMove);
        if (get<2>(nextMove)) {
            final = get<3>(nextMove);
        }
        (*currentTrack)[head] = write;
        if (direction == 'L') {
            head -= trackCorrection;
            if (head < 0) {
                trackCorrection *= -1;
                if (trackCorrection == 1)
                    currentTrack = &tracks[track].first;
                if (trackCorrection == -1)
                    currentTrack = &tracks[track].second;
            }
        }
        else if (direction == 'R') {
            head += trackCorrection;
            if (head < 0) {
                trackCorrection *= -1;
                if (trackCorrection == 1)
                    currentTrack = &tracks[track].first;
                if (trackCorrection == -1)
                    currentTrack = &tracks[track].second;
            }
        }
//                Gaat wel naar het begin van de nieuwe/bestaande track
        else if (direction == 'U') {
            if (track - 1 < 0) {
                return false;
            }
            track--;
            head = 0;
            currentTrack = &tracks[track].first;
        }
        else if (direction == 'D') {
            track++;
            head = 0;
            if (track == tracks.size()) {
                tracks.push_back(Track ({},{}));
            }
            currentTrack = &tracks[track].first;
        }

    }
    while (get<2>(nextMove));
    if (final) {
        return true;
    }
    return false;
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
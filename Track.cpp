//
// Created by youssef on 5/12/22.
//

#include "Track.h"

Track::Track() : leftSide({"#"}),rightSide({"#"}), head(0) {

}

string Track::read() const {
    if (head >= 0) {
        return rightSide[head];
    }
    return leftSide[-(head+1)];
}

void Track::write(const string& input) {
    if (head >= 0) {
        rightSide[head] = input;
        return;
    }
    leftSide[-(head+1)] = input;
}

void Track::moveLeft() {
    head--;
    if (head < 0 and leftSide.size() <= -(head+1)) {
        leftSide.emplace_back("#");
    }
}

void Track::moveRight() {
    head++;
    if (head >= 0 and rightSide.size() <= head) {
        rightSide.emplace_back("#");
    }
}

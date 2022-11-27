//
// Created by youssef on 27/11/22.
//

#ifndef NCP_TRANSITION_H
#define NCP_TRANSITION_H


#include <string>

class Transition {
public:
    std::string from, to, symbol;
    char direction;
    Transition(const string &from, const string &to, const string &symbol, char direction) : from(from), to(to),
                                                                                             symbol(symbol),
                                                                                             direction(direction) {}
};


#endif //NCP_TRANSITION_H

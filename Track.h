//
// Created by youssef on 5/12/22.
//

#ifndef NCP_TRACK_H
#define NCP_TRACK_H

#include <vector>
#include <string>
using namespace std;

class Track {
private:
    int head;
    vector<string> leftSide, rightSide;

public:

    Track();

    ~Track() = default;

    string read() const;

    void write(const string&);

    void moveLeft();

    void moveRight();

};


#endif //NCP_TRACK_H

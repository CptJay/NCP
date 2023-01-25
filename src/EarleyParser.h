//
// Created by nr1sl on 11/28/2022.
//
#ifndef NCP_EARLEYPARSER_H
#define NCP_EARLEYPARSER_H

#include <iostream>
#include <vector>
#include "json.hpp"
#include <map>
#include "Objects.h"
#include <sstream>
#include <string>

using namespace::std;

using json = nlohmann::json;

class EarleyParser {
private:
    map<pair<int,vector<Objects*>>,bool> Contains;
    bool Equal_sign;
    map<string,Objects*>V;
    map<string, bool> Bestaand_Variable;
    Objects* Variable_Object;
    Objects* S;

public:
    EarleyParser();
    EarleyParser(string str);

    bool Variable_check(string word);
    void accepting(EarleyParser& second, string str);
    void TabelVullenSecond(EarleyParser& second, Objects* ob,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,int& state, int& chart);
    bool Search(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart, map<string,bool>& twotime);
    void OneDotAhead(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart, map<string,bool>& twotime);
    bool LastChart(map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel, int chart);

    };


#endif //NCP_EARLEYPARSER_H
